#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import joblib
import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report, f1_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder


def load_intent_samples(complete_dataset_path: Path):
    data = json.loads(complete_dataset_path.read_text(encoding="utf-8"))
    x_text, y_intent = [], []
    for intent in data["intents"]:
        tag = intent["tag"]
        for pattern in intent["patterns"]:
            x_text.append(pattern)
            y_intent.append(tag)
    return x_text, y_intent


def main():
    parser = argparse.ArgumentParser(description="Train intent classifier on sentence embeddings")
    parser.add_argument("--dataset", type=Path, required=True)
    parser.add_argument("--outdir", type=Path, required=True)
    parser.add_argument("--embed-model", type=str, default="sentence-transformers/all-MiniLM-L6-v2")
    parser.add_argument("--test-size", type=float, default=0.15)
    parser.add_argument("--seed", type=int, default=42)
    args = parser.parse_args()

    args.outdir.mkdir(parents=True, exist_ok=True)
    x_text, y_intent = load_intent_samples(args.dataset)

    x_train, x_test, y_train, y_test = train_test_split(
        x_text,
        y_intent,
        test_size=args.test_size,
        random_state=args.seed,
        stratify=y_intent,
    )

    encoder = SentenceTransformer(args.embed_model)
    x_train_emb = encoder.encode(x_train, batch_size=64, show_progress_bar=True, convert_to_numpy=True, normalize_embeddings=True)
    x_test_emb = encoder.encode(x_test, batch_size=64, show_progress_bar=True, convert_to_numpy=True, normalize_embeddings=True)

    le = LabelEncoder()
    y_train_ids = le.fit_transform(y_train)
    y_test_ids = le.transform(y_test)

    clf = LogisticRegression(
        max_iter=2000,
        class_weight="balanced",
        solver="lbfgs",
        multi_class="auto",
        random_state=args.seed,
    )
    clf.fit(x_train_emb, y_train_ids)

    pred_ids = clf.predict(x_test_emb)
    pred_labels = le.inverse_transform(pred_ids)

    acc = accuracy_score(y_test, pred_labels)
    macro_f1 = f1_score(y_test, pred_labels, average="macro")
    report = classification_report(y_test, pred_labels, output_dict=True)

    joblib.dump(clf, args.outdir / "intent_embedding_classifier.joblib")
    joblib.dump(le, args.outdir / "intent_embedding_label_encoder.joblib")

    np.save(args.outdir / "intent_embedding_train_vectors.npy", x_train_emb)

    metrics = {
        "embed_model": args.embed_model,
        "test_accuracy": acc,
        "test_macro_f1": macro_f1,
        "num_samples": len(x_text),
        "num_intents": len(set(y_intent)),
        "classification_report": report,
    }
    (args.outdir / "intent_embedding_metrics.json").write_text(json.dumps(metrics, indent=2), encoding="utf-8")

    (args.outdir / "intent_embedding_config.json").write_text(
        json.dumps(
            {
                "embed_model": args.embed_model,
                "normalize_embeddings": True,
                "label_classes": le.classes_.tolist(),
            },
            indent=2,
        ),
        encoding="utf-8",
    )

    print(f"Saved embedding intent model to {args.outdir}")
    print(f"accuracy={acc:.4f}, macro_f1={macro_f1:.4f}")


if __name__ == "__main__":
    main()
