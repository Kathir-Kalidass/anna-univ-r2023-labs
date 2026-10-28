#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

import joblib
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report, f1_score
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.svm import LinearSVC


def load_intent_samples(complete_dataset_path: Path):
    data = json.loads(complete_dataset_path.read_text(encoding="utf-8"))
    x_text, y_intent = [], []
    for intent in data["intents"]:
        tag = intent["tag"]
        for pattern in intent["patterns"]:
            x_text.append(pattern)
            y_intent.append(tag)
    return x_text, y_intent


def build_candidates(seed: int):
    common_vec = TfidfVectorizer(lowercase=True, ngram_range=(1, 2), min_df=1)
    return {
        "logreg": Pipeline(
            [
                ("tfidf", common_vec),
                (
                    "clf",
                    LogisticRegression(
                        max_iter=2000,
                        class_weight="balanced",
                        n_jobs=None,
                        solver="lbfgs",
                        random_state=seed,
                        multi_class="auto",
                    ),
                ),
            ]
        ),
        "linear_svc": Pipeline(
            [
                ("tfidf", common_vec),
                ("clf", LinearSVC(class_weight="balanced", random_state=seed)),
            ]
        ),
    }


def main():
    parser = argparse.ArgumentParser(description="Train fast intent classifier (TF-IDF + linear model)")
    parser.add_argument("--dataset", type=Path, required=True, help="Path to austartify_complete_dataset.json")
    parser.add_argument("--outdir", type=Path, required=True, help="Output directory for model artifacts")
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

    candidates = build_candidates(args.seed)

    best_name = None
    best_model = None
    best_macro_f1 = -1.0
    benchmark = {}

    for name, model in candidates.items():
        model.fit(x_train, y_train)
        preds = model.predict(x_test)
        macro_f1 = f1_score(y_test, preds, average="macro")
        acc = accuracy_score(y_test, preds)
        benchmark[name] = {"accuracy": acc, "macro_f1": macro_f1}
        if macro_f1 > best_macro_f1:
            best_macro_f1 = macro_f1
            best_name = name
            best_model = model

    final_preds = best_model.predict(x_test)
    report = classification_report(y_test, final_preds, output_dict=True)

    model_path = args.outdir / "intent_fast_model.joblib"
    meta_path = args.outdir / "intent_fast_metrics.json"

    joblib.dump(best_model, model_path)

    payload = {
        "best_model": best_name,
        "test_size": args.test_size,
        "seed": args.seed,
        "num_samples": len(x_text),
        "num_intents": len(set(y_intent)),
        "benchmark": benchmark,
        "best_test_accuracy": accuracy_score(y_test, final_preds),
        "best_test_macro_f1": best_macro_f1,
        "classification_report": report,
    }

    meta_path.write_text(json.dumps(payload, indent=2), encoding="utf-8")

    print(f"Saved model: {model_path}")
    print(f"Saved metrics: {meta_path}")
    print(f"Best model: {best_name} | macro_f1={best_macro_f1:.4f}")


if __name__ == "__main__":
    main()
