# Austartify English-Only Chatbot: Detailed Execution Report

## 1) Objective
Build a production-ready, English-only chatbot dataset for Austartify event lifecycle support:
- Registration → Team Formation → Orientation → Bootcamp → Pitching
- Selection/Rejection branching
- Pre-Final → Final → Funding → Incubation

This report accompanies generated training datasets in this folder.

## 2) Delivered Dataset Artifacts
1. `austartify_intents_large.json`
   - Intent-classification corpus with tags, patterns, and response templates.
2. `austartify_qa_large.jsonl`
   - Large Q&A training/evaluation records for FAQ/RAG and supervised fine-tuning.
3. `austartify_knowledge_chunks.jsonl`
   - Retrieval corpus chunks for vector indexing (stage docs + policy chunks + intent guidance).
4. `austartify_dialogues_large.jsonl`
   - Multi-turn conversations for chatbot behavior and response style training.
5. `DATASET_SUMMARY.md`
   - File counts and usage guidance.
6. `austartify_complete_dataset.json`
   - Complete schema containing startup flow, advanced intents, funding structure, final stage, compliance, decision tree, and large Q&A block.

## 3) Current Dataset Size
- Intents: 31
- Intent patterns: 3,720
- Q&A records: 3,720
- Knowledge chunks: 266
- Multi-turn dialogues: 1,800
- Complete dataset intents: 14
- Complete dataset QA records: 1,965

## 3.1 Exact Coverage of Requested Sections
- Master Flow: Included as `startup_flow` with all stages and decision checkpoints.
- Full Intent Dataset: Included as `intents` (14 core tags with expanded patterns and responses).
- Funding Structure: Included as `funding_structure` with 1-4, 5-8, 9-12 month splits (50/30/20).
- Final Stage Details: Included as `final_stage`.
- Utilization & Compliance: Included as `post_funding` with required documents and next stage.
- Decision Logic: Included as `decision_tree` for Zonal, Pre-Final, and Final routing.
- Q&A Dataset: Included as `qa_dataset` with canonical examples + expanded training set.

## 4) Training Readiness
### A. Intent Classifier
- Input: `patterns`
- Label: `tag`
- Split: 80/10/10 (train/val/test)
- Suggested model: MiniLM or DistilBERT classifier

### B. RAG Retrieval
- Index files:
  - `austartify_knowledge_chunks.jsonl`
  - `austartify_qa_large.jsonl` (optionally question+answer concatenated)
- Suggested embedding model: `all-MiniLM-L6-v2`
- Top-k retrieval: 5 to 8

### C. Response Generation
- Runtime model: `phi3` via Ollama
- Prompt strategy: context-grounded instruction with fallback when confidence is low

## 5) Execution Plan (Action Procedure)
### Phase 1 — Data Ops (Day 1)
- Validate random sample of 200 records
- Remove duplicates (semantic similarity > threshold)
- Add strict source fields if required by compliance

### Phase 2 — Retrieval Setup (Day 2)
- Embed knowledge chunks
- Build Chroma/FAISS index
- Benchmark retrieval precision@5 on 100 eval questions

### Phase 3 — Chat Backend (Day 3)
- Build FastAPI endpoint `/chat`
- Add confidence score and fallback routing
- Add logging for unanswered questions

### Phase 4 — Frontend + Channels (Day 4)
- Website widget integration
- Telegram integration
- WhatsApp (if approved) integration

### Phase 5 — QA & Launch (Day 5)
- Load test
- Safety/policy checks
- Deploy and monitor

## 6) Enhancement Backlog
1. Confidence-aware hybrid routing (FAQ fast path + LLM path)
2. Answer caching (Redis)
3. Daily analytics dashboard for top unanswered questions
4. Active-learning loop to auto-propose new FAQ entries
5. Domain-specific sub-intents for finance/legal/investor track

## 7) Recommended CPU-Only Stack
- Backend: FastAPI
- Embeddings: sentence-transformers (`all-MiniLM-L6-v2`)
- Vector DB: ChromaDB or FAISS
- LLM runtime: Ollama (`phi3`)
- Frontend: React widget or plain JS embed

## 8) Quality Guardrails
- English-only outputs enforced in prompt
- Grounded answers only from retrieved context
- If no strong context, return clarification + human escalation path

## 9) Next Improvements to Scale Further
- Increase dialogues from 1,800 to 5,000+ with scenario simulation
- Add role-conditioned dialogues (attendee/organizer/volunteer)
- Add date-sensitive synthetic records for dynamic event schedules
