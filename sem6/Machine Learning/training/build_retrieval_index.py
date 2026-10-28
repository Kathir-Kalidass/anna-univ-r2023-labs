#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import numpy as np
from sentence_transformers import SentenceTransformer


def read_jsonl(path: Path):
    rows = []
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                rows.append(json.loads(line))
    return rows


def build_corpus(qa_rows, knowledge_rows):
    texts = []
    meta = []

    for row in qa_rows:
        txt = f"Q: {row['question']}\nA: {row['answer']}"
        texts.append(txt)
        meta.append(
            {
                "type": "qa",
                "id": row.get("id"),
                "intent": row.get("intent"),
                "question": row.get("question"),
                "answer": row.get("answer"),
            }
        )

    for row in knowledge_rows:
        txt = f"Title: {row.get('title', '')}\nContent: {row.get('content', '')}"
        texts.append(txt)
        meta.append(
            {
                "type": "knowledge",
                "id": row.get("doc_id"),
                "section": row.get("section"),
                "title": row.get("title"),
                "content": row.get("content"),
            }
        )

    return texts, meta


def main():
    parser = argparse.ArgumentParser(description="Build dense retrieval index from QA + knowledge chunks")
    parser.add_argument("--qa", type=Path, required=True)
    parser.add_argument("--knowledge", type=Path, required=True)
    parser.add_argument("--outdir", type=Path, required=True)
    parser.add_argument("--embed-model", type=str, default="sentence-transformers/all-MiniLM-L6-v2")
    args = parser.parse_args()

    args.outdir.mkdir(parents=True, exist_ok=True)

    qa_rows = read_jsonl(args.qa)
    knowledge_rows = read_jsonl(args.knowledge)

    texts, meta = build_corpus(qa_rows, knowledge_rows)

    encoder = SentenceTransformer(args.embed_model)
    vecs = encoder.encode(texts, batch_size=64, show_progress_bar=True, convert_to_numpy=True, normalize_embeddings=True)

    np.save(args.outdir / "retrieval_vectors.npy", vecs)
    (args.outdir / "retrieval_metadata.json").write_text(json.dumps(meta, ensure_ascii=False, indent=2), encoding="utf-8")
    (args.outdir / "retrieval_config.json").write_text(
        json.dumps(
            {
                "embed_model": args.embed_model,
                "num_documents": len(meta),
                "vector_dim": int(vecs.shape[1]),
                "normalized": True,
                "source": {
                    "qa": str(args.qa),
                    "knowledge": str(args.knowledge),
                },
            },
            indent=2,
        ),
        encoding="utf-8",
    )

    print(f"Index built with {len(meta)} docs | dim={vecs.shape[1]}")
    print(f"Saved to {args.outdir}")


if __name__ == "__main__":
    main()
