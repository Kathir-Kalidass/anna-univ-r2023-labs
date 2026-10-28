# Austartify Chatbot Training Guide (English-Only)

This guide gives a full, optimized training flow for your datasets in `ml_data/datasets`.

## Tech Stack Used

- Language: `Python 3.11`
- ML Frameworks: `scikit-learn`, `sentence-transformers`
- Retrieval: `Dense vector search (cosine similarity on normalized embeddings)`
- Embedding Model: `all-MiniLM-L6-v2`
- Model Serialization: `joblib`, `NumPy .npy`
- Data Format: `JSON`, `JSONL`
- Orchestration: `Bash` (`run_all_training.sh`)
- Dataset Sources: `austartify_complete_dataset.json`, `austartify_qa_large.jsonl`, `austartify_knowledge_chunks.jsonl`, split files under `datasets/splits`

## 1) What You Get

Training scripts included:
- `train_intent_fast.py` → Fast TF-IDF + linear model intent classifier
- `train_intent_embedding.py` → Semantic embedding-based intent classifier (higher robustness)
- `build_retrieval_index.py` → Dense retrieval index over FAQ + knowledge chunks
- `evaluate_pipeline.py` → Measures intent quality + retrieval recall
- `select_best_intent_model.py` → Picks best intent model by macro-F1
- `hybrid_answer.py` → Hybrid answer inference (intent + retrieval fallback)
- `run_all_training.sh` → One-command full training + evaluation

## 2) Install Dependencies

From workspace root:

```bash
cd /home/kathir/Drone_Smart_City/ml_data
.venv/bin/pip install -r training/requirements.txt
```

## 3) Full Training (One Command)

```bash
cd /home/kathir/Drone_Smart_City/ml_data
bash training/run_all_training.sh
```

Outputs are created in:
- `models/intent_fast`
- `models/intent_embedding`
- `models/retrieval`
- `models/eval`

## 4) Pick Best Intent Model Automatically

```bash
cd /home/kathir/Drone_Smart_City/ml_data
.venv/bin/python training/select_best_intent_model.py \
  --fast-metrics models/intent_fast/intent_fast_metrics.json \
  --embed-metrics models/intent_embedding/intent_embedding_metrics.json \
  --out models/eval/best_intent_model.json
```

## 5) Test Hybrid Answering

Example query:

```bash
cd /home/kathir/Drone_Smart_City/ml_data
.venv/bin/python training/hybrid_answer.py \
  --query "What happens after zonal pitching if selected?" \
  --complete-dataset datasets/austartify_complete_dataset.json \
  --intent-model models/intent_fast/intent_fast_model.joblib \
  --retrieval-dir models/retrieval
```

If you want to use embedding intent model for inference, use:
- `models/intent_embedding/intent_embedding_classifier.joblib` only if your calling code also decodes label IDs with `intent_embedding_label_encoder.joblib`.
- For direct CLI use in `hybrid_answer.py`, keep using `intent_fast_model.joblib`.

## 6) Accuracy & Speed Optimization Notes

### Fastest runtime setup
- Use `intent_fast_model.joblib` for intent detection.
- Keep retrieval vectors pre-built in `models/retrieval/retrieval_vectors.npy`.
- Cache repeated query embeddings in serving layer.

### Better semantic robustness
- Keep `intent_embedding` model trained and compare metrics.
- Use retrieval fallback for low-confidence intent predictions.

### Threshold tuning
- In `hybrid_answer.py`, adjust:
  - `--intent-threshold 0.55` (default)
  - Try `0.50` for more intent usage, `0.65` for stricter fallback to retrieval.

## 7) Recommended Production Pipeline

1. Predict intent with `intent_fast_model`
2. If confidence high → intent response template
3. If confidence low → retrieval top-k answer
4. If no strong hit → fallback support message

## 8) Key Files Used for Training

- Complete schema: `datasets/austartify_complete_dataset.json`
- Large FAQ corpus: `datasets/austartify_qa_large.jsonl`
- Knowledge chunks: `datasets/austartify_knowledge_chunks.jsonl`
- Test split: `datasets/splits/qa_test.jsonl`

## 9) Expected Artifacts Checklist

After full run, verify:
- `models/intent_fast/intent_fast_model.joblib`
- `models/intent_fast/intent_fast_metrics.json`
- `models/intent_embedding/intent_embedding_classifier.joblib`
- `models/intent_embedding/intent_embedding_metrics.json`
- `models/retrieval/retrieval_vectors.npy`
- `models/retrieval/retrieval_metadata.json`
- `models/eval/pipeline_eval_fast.json`

## 10) Quick Troubleshooting

- If embedding model download is slow: retry once and keep internet stable.
- If memory pressure appears: reduce batch size in scripts from `64` to `16`.
- If intent classes are imbalanced in future data: keep `class_weight="balanced"` as already configured.
