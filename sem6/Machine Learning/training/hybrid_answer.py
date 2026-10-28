#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import joblib
import numpy as np
from sentence_transformers import SentenceTransformer


def softmax(arr):
    arr = np.asarray(arr, dtype=np.float64)
    arr = arr - np.max(arr)
    exp = np.exp(arr)
    return exp / np.sum(exp)


def cosine_search(query_vec, doc_vecs, top_k=5):
    scores = doc_vecs @ query_vec
    idx = np.argsort(-scores)[:top_k]
    return idx, scores[idx]


def load_intent_response_map(complete_dataset_path: Path):
    data = json.loads(complete_dataset_path.read_text(encoding="utf-8"))
    mapping = {}
    for intent in data["intents"]:
        mapping[intent["tag"]] = intent["responses"]
    return mapping


def main():
    parser = argparse.ArgumentParser(description="Hybrid answer engine: intent + dense retrieval")
    parser.add_argument("--query", type=str, required=True)
    parser.add_argument("--complete-dataset", type=Path, required=True)
    parser.add_argument("--intent-model", type=Path, required=True)
    parser.add_argument("--retrieval-dir", type=Path, required=True)
    parser.add_argument("--embed-model", type=str, default="sentence-transformers/all-MiniLM-L6-v2")
    parser.add_argument("--intent-threshold", type=float, default=0.55)
    parser.add_argument("--top-k", type=int, default=5)
    args = parser.parse_args()

    intent_responses = load_intent_response_map(args.complete_dataset)

    intent_model = joblib.load(args.intent_model)

    retrieval_meta = json.loads((args.retrieval_dir / "retrieval_metadata.json").read_text(encoding="utf-8"))
    retrieval_vecs = np.load(args.retrieval_dir / "retrieval_vectors.npy")

    embedder = SentenceTransformer(args.embed_model)
    query_vec = embedder.encode([args.query], normalize_embeddings=True, convert_to_numpy=True)[0]

    # Intent prediction
    pred_intent = intent_model.predict([args.query])[0]

    confidence = None
    if hasattr(intent_model, "predict_proba"):
        probs = intent_model.predict_proba([args.query])[0]
        confidence = float(np.max(probs))
    elif hasattr(intent_model, "decision_function"):
        logits = intent_model.decision_function([args.query])[0]
        if np.ndim(logits) == 0:
            confidence = 0.5
        else:
            confidence = float(np.max(softmax(logits)))
    else:
        confidence = 0.5

    # Retrieval fallback/context
    idxs, scores = cosine_search(query_vec, retrieval_vecs, top_k=args.top_k)
    top_docs = []
    for i, s in zip(idxs, scores):
        item = retrieval_meta[int(i)]
        item = {**item, "score": float(s)}
        top_docs.append(item)

    if confidence >= args.intent_threshold and pred_intent in intent_responses:
        answer = intent_responses[pred_intent][0]
        source = "intent"
    else:
        best = top_docs[0]
        if best.get("type") == "qa" and best.get("answer"):
            answer = best["answer"]
        else:
            answer = (
                "I could not find an exact policy line. Please check the latest dashboard updates "
                "or contact support with your team ID."
            )
        source = "retrieval"

    output = {
        "query": args.query,
        "answer": answer,
        "source": source,
        "predicted_intent": pred_intent,
        "intent_confidence": confidence,
        "top_docs": top_docs,
    }

    print(json.dumps(output, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
