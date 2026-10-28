# Austartify English Chatbot Dataset

Generated files:
- `austartify_intents_large.json`
- `austartify_qa_large.jsonl`
- `austartify_knowledge_chunks.jsonl`
- `austartify_dialogues_large.jsonl`
- `austartify_complete_dataset.json`

## Counts
- Intents: 31
- Patterns per intent: 120
- Total intent patterns: 3720
- QA pairs: 3720
- Knowledge chunks: 266
- Dialogues: 1800
- Complete dataset intents: 14
- Complete dataset QA records: 1965

## Suggested usage
1. Intent classification: train on `tag` + `patterns`.
2. RAG retrieval index: ingest `austartify_knowledge_chunks.jsonl` + `austartify_qa_large.jsonl`.
3. Supervised chat fine-tuning: use `austartify_dialogues_large.jsonl`.
4. Full rule-aware dataset: use `austartify_complete_dataset.json` for flow, decision logic, and compliance-aware responses.
5. Evaluation set: hold out 15% randomly from QA/dialogues.

## English-only policy
All records are generated in English to match deployment requirements.
