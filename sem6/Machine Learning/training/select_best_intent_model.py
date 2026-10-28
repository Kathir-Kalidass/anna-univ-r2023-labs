#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


def read_json(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


def main():
    parser = argparse.ArgumentParser(description="Select best intent model from metrics files")
    parser.add_argument("--fast-metrics", type=Path, required=True)
    parser.add_argument("--embed-metrics", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()

    fast = read_json(args.fast_metrics)
    emb = read_json(args.embed_metrics)

    candidates = [
        {
            "name": "intent_fast",
            "macro_f1": fast.get("best_test_macro_f1", 0.0),
            "accuracy": fast.get("best_test_accuracy", 0.0),
            "model_path": "models/intent_fast/intent_fast_model.joblib",
        },
        {
            "name": "intent_embedding",
            "macro_f1": emb.get("test_macro_f1", 0.0),
            "accuracy": emb.get("test_accuracy", 0.0),
            "model_path": "models/intent_embedding/intent_embedding_classifier.joblib",
        },
    ]

    best = max(candidates, key=lambda x: (x["macro_f1"], x["accuracy"]))

    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps({"best": best, "all": candidates}, indent=2), encoding="utf-8")

    print(json.dumps({"best": best}, indent=2))


if __name__ == "__main__":
    main()
