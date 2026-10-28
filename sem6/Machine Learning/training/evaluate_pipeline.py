#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import joblib
import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.metrics import accuracy_score, f1_score


def read_jsonl(path: Path):
    rows = []
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                rows.append(json.loads(line))
    return rows


def top_k_search(query_vecs, doc_vecs, k):
    scores = query_vecs @ doc_vecs.T
    idx = np.argsort(-scores, axis=1)[:, :k]
    return idx


def main():
    parser = argparse.ArgumentParser(description="Evaluate intent model + retrieval quality")
    parser.add_argument("--qa-test", type=Path, required=True)
    parser.add_argument("--intent-model", type=Path, required=True)
    parser.add_argument("--retrieval-dir", type=Path, required=True)
    parser.add_argument("--embed-model", type=str, default="sentence-transformers/all-MiniLM-L6-v2")
    parser.add_argument("--k", type=int, default=5)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()

    qa_test = read_jsonl(args.qa_test)
    x = [r["question"] for r in qa_test]
    y = [r.get("intent") for r in qa_test]

    intent_model = joblib.load(args.intent_model)
    pred = intent_model.predict(x)

    intent_acc = accuracy_score(y, pred)
    intent_macro_f1 = f1_score(y, pred, average="macro")

    meta = json.loads((args.retrieval_dir / "retrieval_metadata.json").read_text(encoding="utf-8"))
    vecs = np.load(args.retrieval_dir / "retrieval_vectors.npy")

    embedder = SentenceTransformer(args.embed_model)
    query_vecs = embedder.encode(x, batch_size=64, show_progress_bar=True, convert_to_numpy=True, normalize_embeddings=True)

    top_idx = top_k_search(query_vecs, vecs, args.k)

    hits = 0
    for i, row in enumerate(qa_test):
        target_intent = row.get("intent")
        found = False
        for j in top_idx[i]:
            m = meta[int(j)]
            if m.get("type") == "qa" and m.get("intent") == target_intent:
                found = True
                break
        if found:
            hits += 1

    retrieval_recall_k = hits / max(1, len(qa_test))

    report = {
        "intent_accuracy": intent_acc,
        "intent_macro_f1": intent_macro_f1,
        "retrieval_recall_at_k": retrieval_recall_k,
        "k": args.k,
        "num_eval_samples": len(qa_test),
    }

    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(report, indent=2), encoding="utf-8")

    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
