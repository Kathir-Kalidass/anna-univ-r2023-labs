#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="/home/kathir/Drone_Smart_City/ml_data"
PY="$ROOT_DIR/.venv/bin/python"

DATA_DIR="$ROOT_DIR/datasets"
SPLIT_DIR="$DATA_DIR/splits"
OUT_DIR="$ROOT_DIR/models"

mkdir -p "$OUT_DIR/intent_fast"
mkdir -p "$OUT_DIR/intent_embedding"
mkdir -p "$OUT_DIR/retrieval"
mkdir -p "$OUT_DIR/eval"

echo "[1/4] Training fast intent model..."
"$PY" "$ROOT_DIR/training/train_intent_fast.py" \
  --dataset "$DATA_DIR/austartify_complete_dataset.json" \
  --outdir "$OUT_DIR/intent_fast"

echo "[2/4] Training embedding intent model..."
"$PY" "$ROOT_DIR/training/train_intent_embedding.py" \
  --dataset "$DATA_DIR/austartify_complete_dataset.json" \
  --outdir "$OUT_DIR/intent_embedding"

echo "[3/4] Building retrieval index..."
"$PY" "$ROOT_DIR/training/build_retrieval_index.py" \
  --qa "$DATA_DIR/austartify_qa_large.jsonl" \
  --knowledge "$DATA_DIR/austartify_knowledge_chunks.jsonl" \
  --outdir "$OUT_DIR/retrieval"

echo "[4/4] Evaluating pipeline (intent_fast + retrieval)..."
"$PY" "$ROOT_DIR/training/evaluate_pipeline.py" \
  --qa-test "$SPLIT_DIR/qa_test.jsonl" \
  --intent-model "$OUT_DIR/intent_fast/intent_fast_model.joblib" \
  --retrieval-dir "$OUT_DIR/retrieval" \
  --out "$OUT_DIR/eval/pipeline_eval_fast.json"

echo "Training and evaluation completed."
