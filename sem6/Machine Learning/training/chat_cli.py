#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import joblib
import numpy as np
from sentence_transformers import SentenceTransformer


def patch_sklearn_compat(model):
    # Models trained with newer scikit-learn may deserialize on older versions
    # without attributes that predict_proba still expects.
    if hasattr(model, "named_steps"):
        for step in model.named_steps.values():
            patch_sklearn_compat(step)

    if model.__class__.__name__ == "LogisticRegression" and not hasattr(model, "multi_class"):
        model.multi_class = "auto"

    return model


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


def build_answer(query, intent_model, intent_responses, retrieval_meta, retrieval_vecs, embedder, intent_threshold, top_k):
    query_vec = embedder.encode([query], normalize_embeddings=True, convert_to_numpy=True)[0]

    pred_intent = intent_model.predict([query])[0]

    if hasattr(intent_model, "predict_proba"):
        probs = intent_model.predict_proba([query])[0]
        confidence = float(np.max(probs))
    elif hasattr(intent_model, "decision_function"):
        logits = intent_model.decision_function([query])[0]
        if np.ndim(logits) == 0:
            confidence = 0.5
        else:
            confidence = float(np.max(softmax(logits)))
    else:
        confidence = 0.5

    idxs, scores = cosine_search(query_vec, retrieval_vecs, top_k=top_k)
    top_docs = []
    for i, s in zip(idxs, scores):
        item = retrieval_meta[int(i)]
        top_docs.append({**item, "score": float(s)})

    if confidence >= intent_threshold and pred_intent in intent_responses:
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

    return {
        "query": query,
        "answer": answer,
        "source": source,
        "predicted_intent": pred_intent,
        "intent_confidence": confidence,
        "top_docs": top_docs,
    }


def main():
    parser = argparse.ArgumentParser(description="Terminal chatbot backed by the trained Austartify models")
    parser.add_argument("--complete-dataset", type=Path, default=Path("datasets/austartify_complete_dataset.json"))
    parser.add_argument("--intent-model", type=Path, default=Path("models/intent_fast/intent_fast_model.joblib"))
    parser.add_argument("--retrieval-dir", type=Path, default=Path("models/retrieval"))
    parser.add_argument("--embed-model", type=str, default="sentence-transformers/all-MiniLM-L6-v2")
    parser.add_argument("--intent-threshold", type=float, default=0.55)
    parser.add_argument("--top-k", type=int, default=5)
    parser.add_argument("--show-debug", action="store_true")
    args = parser.parse_args()

    intent_responses = load_intent_response_map(args.complete_dataset)
    intent_model = patch_sklearn_compat(joblib.load(args.intent_model))
    retrieval_meta = json.loads((args.retrieval_dir / "retrieval_metadata.json").read_text(encoding="utf-8"))
    retrieval_vecs = np.load(args.retrieval_dir / "retrieval_vectors.npy")
    embedder = SentenceTransformer(args.embed_model)

    print("Austartify terminal chatbot is ready.")
    print("Type a question and press Enter. Type 'exit' or 'quit' to stop.")

    while True:
        try:
            query = input("\nYou: ").strip()
        except EOFError:
            print("\nBye.")
            break
        except KeyboardInterrupt:
            print("\nBye.")
            break

        if not query:
            continue

        if query.lower() in {"exit", "quit"}:
            print("Bye.")
            break

        result = build_answer(
            query=query,
            intent_model=intent_model,
            intent_responses=intent_responses,
            retrieval_meta=retrieval_meta,
            retrieval_vecs=retrieval_vecs,
            embedder=embedder,
            intent_threshold=args.intent_threshold,
            top_k=args.top_k,
        )

        print(f"Bot: {result['answer']}")
        if args.show_debug:
            print(
                json.dumps(
                    {
                        "source": result["source"],
                        "predicted_intent": result["predicted_intent"],
                        "intent_confidence": result["intent_confidence"],
                        "top_doc": result["top_docs"][0] if result["top_docs"] else None,
                    },
                    ensure_ascii=False,
                    indent=2,
                )
            )


if __name__ == "__main__":
    main()
