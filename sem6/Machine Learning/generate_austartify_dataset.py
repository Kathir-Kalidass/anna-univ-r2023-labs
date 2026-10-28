#!/usr/bin/env python3
import json
import random
from pathlib import Path
from datetime import datetime

random.seed(42)

OUTPUT_DIR = Path("/home/kathir/Drone_Smart_City/ml_data/datasets")
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

EVENT_NAME = "Austartify"
CITY = "Chennai"
STATE = "Tamil Nadu"

MASTER_FLOW = [
    "Registration",
    "Application",
    "Team Formation",
    "Orientation",
    "Bootcamp (Training + Activity)",
    "Pitch Club",
    "Pitching Round",
    "Zonal Pitching",
    {"decision": {"selected": "Pre-Final", "rejected": "Rebootcamp"}},
    "Pre-Final Evaluation",
    {"decision": {"selected": "Final", "rejected": "Rebootcamp"}},
    "Final Pitch (Physical)",
    "Final Jury Evaluation",
    "Funding (Installments)",
    "Incubation",
    "Utilization Certificate",
    "Scaling to VC",
]

ADVANCED_INTENT_SEED = [
    {
        "tag": "registration",
        "context": "start",
        "base_patterns": [
            "How to register?",
            "What is registration process?",
            "How to apply in startup 4.0?",
            "What is application process?",
            "How do I join?",
        ],
        "base_response": "You need to register, login, and apply with your idea.",
        "topic": "registration",
    },
    {
        "tag": "team_formation",
        "context": "post_registration",
        "base_patterns": [
            "How to form team?",
            "Team requirement?",
            "Can I join a team?",
            "Team formation process?",
        ],
        "base_response": "After registration, you must form or join a team to proceed.",
        "topic": "team formation",
    },
    {
        "tag": "orientation",
        "context": "early_stage",
        "base_patterns": [
            "What is orientation?",
            "Orientation details?",
            "What happens in orientation?",
        ],
        "base_response": "Orientation introduces the startup program, expectations, and workflow.",
        "topic": "orientation",
    },
    {
        "tag": "bootcamp",
        "context": "training",
        "base_patterns": [
            "What is bootcamp?",
            "Bootcamp activities?",
            "Training process?",
            "What happens in bootcamp?",
        ],
        "base_response": "Bootcamp includes training, idea validation, and practical activities.",
        "topic": "bootcamp",
    },
    {
        "tag": "pitch_club",
        "context": "pre_pitch",
        "base_patterns": [
            "What is pitch club?",
            "Pitch preparation?",
            "How to prepare pitch?",
        ],
        "base_response": "Pitch club helps teams refine their ideas before pitching.",
        "topic": "pitch club",
    },
    {
        "tag": "pitching",
        "context": "evaluation",
        "base_patterns": [
            "What is pitching?",
            "Pitching process?",
            "Pitch day?",
        ],
        "base_response": "Teams present their ideas to evaluators during pitch rounds.",
        "topic": "pitching",
    },
    {
        "tag": "zonal_pitching",
        "context": "regional_round",
        "base_patterns": [
            "What is zonal pitching?",
            "Regional pitching?",
            "Zonal evaluation?",
        ],
        "base_response": "Zonal pitching evaluates teams at regional level before finals.",
        "topic": "zonal pitching",
    },
    {
        "tag": "selection",
        "context": "decision",
        "base_patterns": [
            "What happens if selected?",
            "Selection process?",
            "After passing pitch?",
        ],
        "base_response": "Selected teams move to pre-final stage.",
        "topic": "selection",
    },
    {
        "tag": "rejection",
        "context": "decision",
        "base_patterns": [
            "What if rejected?",
            "Failure case?",
            "If not selected?",
        ],
        "base_response": "Rejected teams are sent to rebootcamp for improvement.",
        "topic": "rejection handling",
    },
    {
        "tag": "pre_final",
        "context": "advanced_round",
        "base_patterns": [
            "What is pre-final?",
            "Pre-final evaluation?",
            "Before final?",
        ],
        "base_response": "Pre-final is a screening stage before final selection.",
        "topic": "pre-final",
    },
    {
        "tag": "final",
        "context": "advanced_round",
        "base_patterns": [
            "Final round details?",
            "Final pitch?",
            "How final works?",
        ],
        "base_response": "Final round includes physical pitching and jury evaluation.",
        "topic": "final round",
    },
    {
        "tag": "funding",
        "context": "post_selection",
        "base_patterns": [
            "Funding process?",
            "How money is given?",
            "Startup funding details?",
        ],
        "base_response": "Funding is provided in stages based on performance.",
        "topic": "funding",
    },
    {
        "tag": "incubation",
        "context": "post_funding",
        "base_patterns": [
            "What is incubation?",
            "After funding?",
            "Post funding support?",
        ],
        "base_response": "Selected startups enter incubation for growth and development.",
        "topic": "incubation",
    },
    {
        "tag": "vc",
        "context": "scale_up",
        "base_patterns": [
            "What is VC?",
            "How to reach VC?",
            "Scaling stage?",
        ],
        "base_response": "Startups move to venture capital stage after successful growth.",
        "topic": "venture capital",
    },
]

INTENT_BLUEPRINTS = [
    {
        "tag": "registration_process",
        "goal": "Explain how to register and create an account",
        "core_response": "Register on the official Austartify portal, verify your email, and complete your profile to activate your team workspace.",
        "next_step": "After registration, create or join a team before orientation.",
    },
    {
        "tag": "login_and_team_id",
        "goal": "Explain login and team ID generation",
        "core_response": "Once you sign up and log in, the platform auto-generates a unique team ID linked to your email.",
        "next_step": "Use your team ID for submissions, attendance, and pitch tracking.",
    },
    {
        "tag": "team_formation",
        "goal": "Guide users on team creation and joining",
        "core_response": "You can either create a new team or request to join an existing team after registration.",
        "next_step": "Finalize team roles before the orientation date.",
    },
    {
        "tag": "orientation_schedule",
        "goal": "Provide orientation timeline and purpose",
        "core_response": "Orientation introduces event rules, milestones, submission workflow, and communication channels.",
        "next_step": "Attendance in orientation is required to unlock bootcamp activities.",
    },
    {
        "tag": "orientation_mandatory",
        "goal": "Clarify if orientation is compulsory",
        "core_response": "Yes, orientation is mandatory for all shortlisted teams and individual participants.",
        "next_step": "Missing orientation may pause your progress to the next stage.",
    },
    {
        "tag": "bootcamp_overview",
        "goal": "Describe bootcamp learning format",
        "core_response": "Bootcamp includes mentor sessions, activity tasks, problem validation, and presentation preparation.",
        "next_step": "Complete all assigned activities to qualify for pitching.",
    },
    {
        "tag": "bootcamp_activities",
        "goal": "List activity expectations",
        "core_response": "Activities typically include market validation, prototype notes, pitch deck drafts, and progress demos.",
        "next_step": "Upload activity outputs before the deadline in your dashboard.",
    },
    {
        "tag": "presentation_rounds",
        "goal": "Explain presentation and review rounds",
        "core_response": "Teams present ideas to reviewers who evaluate clarity, feasibility, impact, and execution readiness.",
        "next_step": "Strong review scores can move your team directly toward finals.",
    },
    {
        "tag": "zonal_pitching",
        "goal": "Explain zonal/regional pitching",
        "core_response": "Zonal pitching is a regional screening round where teams present to a local jury before central selection.",
        "next_step": "Top zonal teams proceed to pre-final or final rounds.",
    },
    {
        "tag": "selection_criteria",
        "goal": "Explain selection criteria",
        "core_response": "Selection is based on problem relevance, innovation quality, validation evidence, team strength, and pitch clarity.",
        "next_step": "Keep your documentation updated for transparent evaluation.",
    },
    {
        "tag": "rejection_path",
        "goal": "Handle rejection and next attempt",
        "core_response": "If not selected, teams usually receive feedback and may re-enter through a re-bootcamp or improvement cycle.",
        "next_step": "Use feedback points to refine your idea and resubmit in the next window.",
    },
    {
        "tag": "pre_final_stage",
        "goal": "Define pre-final stage",
        "core_response": "Pre-final stage verifies traction, prototype maturity, and mentor feedback before final jury presentation.",
        "next_step": "Pre-final qualifiers receive final round instructions.",
    },
    {
        "tag": "final_round",
        "goal": "Explain final round process",
        "core_response": "Finals include structured pitching, Q&A with jury, and scoring on business and technical readiness.",
        "next_step": "Winners and shortlisted teams move to funding and incubation tracks.",
    },
    {
        "tag": "grouping_and_batching",
        "goal": "Explain grouping model",
        "core_response": "Participants are grouped into batches based on stage, domain, and mentor capacity for efficient progression.",
        "next_step": "Check your dashboard for batch allocation updates.",
    },
    {
        "tag": "mentoring_support",
        "goal": "Describe mentoring support",
        "core_response": "Mentors guide teams on validation, business model design, prototype strategy, and investor readiness.",
        "next_step": "Book mentor slots through the official calendar.",
    },
    {
        "tag": "funding_process",
        "goal": "Explain funding release process",
        "core_response": "Funding is milestone-based and released in phases after progress review and documentation checks.",
        "next_step": "Maintain clear proof of work to avoid funding delays.",
    },
    {
        "tag": "funding_split",
        "goal": "Share funding split details",
        "core_response": "A common structure is 50% initial support, 30% mid-milestone release, and 20% final release.",
        "next_step": "Exact percentages can vary by program policy updates.",
    },
    {
        "tag": "cash_prize_vs_grant",
        "goal": "Differentiate cash prize and grant",
        "core_response": "Cash prizes reward competition performance, while grants support startup development against milestones.",
        "next_step": "Read your offer letter carefully for usage conditions.",
    },
    {
        "tag": "incubation_benefits",
        "goal": "Explain incubation support",
        "core_response": "Incubation support may include workspace access, mentorship, pilot connections, legal guidance, and investor exposure.",
        "next_step": "Selected teams receive incubation onboarding details.",
    },
    {
        "tag": "certificate_query",
        "goal": "Answer certificate related queries",
        "core_response": "Participation certificates are typically shared digitally after stage completion and attendance verification.",
        "next_step": "Ensure your profile email is correct to receive certificates.",
    },
    {
        "tag": "timeline_duration",
        "goal": "Clarify duration between stages",
        "core_response": "Timeline can range from one week to several weeks depending on stage complexity and review volume.",
        "next_step": "Refer to the latest event calendar for exact dates.",
    },
    {
        "tag": "communication_channels",
        "goal": "Explain official communication channels",
        "core_response": "Official updates are shared through dashboard notifications, email, and authorised group channels.",
        "next_step": "Enable notifications so you do not miss deadlines.",
    },
    {
        "tag": "website_publish_updates",
        "goal": "Handle questions on publish date",
        "core_response": "Registration and stage updates are published on the official website and announcement channels.",
        "next_step": "Use only verified links from official communication.",
    },
    {
        "tag": "deadline_reminders",
        "goal": "Provide deadline reminder process",
        "core_response": "Automated reminders are sent before key deadlines for activities, submissions, and pitch slots.",
        "next_step": "Late submissions may affect your evaluation outcome.",
    },
    {
        "tag": "eligibility",
        "goal": "Explain participant eligibility",
        "core_response": "Eligibility typically includes students, early founders, and innovators meeting the event rules.",
        "next_step": "Check the current program terms for final eligibility.",
    },
    {
        "tag": "domain_categories",
        "goal": "Explain startup domain categories",
        "core_response": "Projects are often classified into domain categories for targeted mentoring and fair evaluation.",
        "next_step": "Choose your domain carefully during application.",
    },
    {
        "tag": "prototype_expectations",
        "goal": "Set prototype expectations",
        "core_response": "A working prototype is preferred, but validated mockups can be accepted in early rounds.",
        "next_step": "Document user feedback to strengthen your submission.",
    },
    {
        "tag": "evaluation_status",
        "goal": "Help users track status",
        "core_response": "You can track status directly in your dashboard under submissions, review, and stage progression tabs.",
        "next_step": "If status is delayed, raise a support ticket with your team ID.",
    },
    {
        "tag": "finance_awareness",
        "goal": "Explain finance awareness sessions",
        "core_response": "Finance awareness sessions cover budgeting, grant usage, runway planning, and compliance basics.",
        "next_step": "Attend finance sessions before requesting funding disbursement.",
    },
    {
        "tag": "post_event_support",
        "goal": "Explain post-event support",
        "core_response": "Post-event support may include networking, investor connects, and follow-up mentoring tracks.",
        "next_step": "Keep your startup profile updated after finals.",
    },
    {
        "tag": "faq_general",
        "goal": "Handle broad event FAQs",
        "core_response": "I can help with registration, orientation, bootcamp, pitching, selection, and funding questions.",
        "next_step": "Ask a specific question for a precise answer.",
    },
]

QUESTION_TEMPLATES = [
    "How does {topic} work in {event}?",
    "Can you explain {topic}?",
    "What happens during {topic}?",
    "What is the process for {topic}?",
    "Please describe {topic} clearly.",
    "I need details about {topic}.",
    "Guide me on {topic} in simple steps.",
    "What should our team do for {topic}?",
    "When does {topic} happen?",
    "Is {topic} mandatory?",
    "Any update about {topic}?",
    "Give me complete info about {topic}.",
    "What are the rules for {topic}?",
    "Tell me the timeline for {topic}.",
    "Can I get support in {topic}?",
]

POLITE_PREFIX = ["", "Hi, ", "Hello, ", "Hey team, ", "Quick question: "]
POLITE_SUFFIX = ["", " please.", " for my team.", " in English.", " for Austartify Tamil Nadu."]

TOPIC_LABELS = {
    "registration_process": "registration",
    "login_and_team_id": "login and team ID",
    "team_formation": "team formation",
    "orientation_schedule": "orientation",
    "orientation_mandatory": "orientation attendance",
    "bootcamp_overview": "bootcamp",
    "bootcamp_activities": "bootcamp activities",
    "presentation_rounds": "presentation rounds",
    "zonal_pitching": "zonal pitching",
    "selection_criteria": "selection criteria",
    "rejection_path": "rejection process",
    "pre_final_stage": "pre-final stage",
    "final_round": "final round",
    "grouping_and_batching": "grouping and batches",
    "mentoring_support": "mentoring support",
    "funding_process": "funding process",
    "funding_split": "funding split",
    "cash_prize_vs_grant": "cash prize and grant",
    "incubation_benefits": "incubation support",
    "certificate_query": "certificates",
    "timeline_duration": "stage duration",
    "communication_channels": "official communication",
    "website_publish_updates": "website publish updates",
    "deadline_reminders": "deadline reminders",
    "eligibility": "eligibility",
    "domain_categories": "project domains",
    "prototype_expectations": "prototype expectations",
    "evaluation_status": "evaluation status",
    "finance_awareness": "finance awareness",
    "post_event_support": "post-event support",
    "faq_general": "event FAQ",
}


def generate_patterns(tag: str, count: int = 120):
    topic = TOPIC_LABELS[tag]
    results = set()
    while len(results) < count:
        t = random.choice(QUESTION_TEMPLATES)
        prefix = random.choice(POLITE_PREFIX)
        suffix = random.choice(POLITE_SUFFIX)
        q = f"{prefix}{t.format(topic=topic, event=EVENT_NAME)}{suffix}".replace("  ", " ").strip()
        q = q[0].upper() + q[1:]
        results.add(q)
    return sorted(results)


def generate_responses(base):
    variants = [
        f"{base['core_response']} {base['next_step']}",
        f"{base['core_response']}",
        f"For {EVENT_NAME}, {base['core_response'].lower()} {base['next_step']}",
        f"{base['core_response']} Please follow official announcements for any revision.",
        f"{base['core_response']} If needed, contact support with your team ID.",
        f"{base['core_response']} This is part of the {EVENT_NAME} startup lifecycle.",
    ]
    return variants


def generate_advanced_patterns(topic: str, seed_patterns, count: int = 120):
    templates = [
        "Explain {topic} in {event}.",
        "How does {topic} work?",
        "Please guide me on {topic}.",
        "What are the steps in {topic}?",
        "Any rules for {topic}?",
        "Give me details about {topic}.",
        "Is {topic} mandatory in {event}?",
        "What should our team prepare for {topic}?",
        "Can you share timeline for {topic}?",
        "How to complete {topic} successfully?",
    ]
    results = set(seed_patterns)
    while len(results) < count:
        t = random.choice(templates)
        prefix = random.choice(POLITE_PREFIX)
        suffix = random.choice(POLITE_SUFFIX)
        q = f"{prefix}{t.format(topic=topic, event=EVENT_NAME)}{suffix}".replace("  ", " ").strip()
        q = q[0].upper() + q[1:]
        results.add(q)
    return sorted(results)


intents_payload = {
    "meta": {
        "dataset_name": "austartify_intents_large",
        "language": "en",
        "generated_at": datetime.utcnow().isoformat() + "Z",
        "source": "Converted from raw startup process notes",
        "region": f"{CITY}, {STATE}",
    },
    "intents": [],
}

for blueprint in INTENT_BLUEPRINTS:
    tag = blueprint["tag"]
    intents_payload["intents"].append(
        {
            "tag": tag,
            "goal": blueprint["goal"],
            "patterns": generate_patterns(tag, 120),
            "responses": generate_responses(blueprint),
            "context": ["austartify_event_assistant", "english_only"],
        }
    )

# Q&A dataset for RAG training/evaluation
qa_records = []
for intent in intents_payload["intents"]:
    for idx, q in enumerate(intent["patterns"]):
        answer = random.choice(intent["responses"])
        qa_records.append(
            {
                "id": f"qa_{intent['tag']}_{idx+1:03d}",
                "intent": intent["tag"],
                "question": q,
                "answer": answer,
                "language": "en",
                "channel": random.choice(["web", "whatsapp", "telegram"]),
                "priority": random.choice(["normal", "high"]),
            }
        )

# Long-form knowledge docs for chunk-based retrieval
knowledge_docs = []
FLOW_STEPS = [
    "Registration/Application",
    "Team Formation",
    "Orientation",
    "Bootcamp Training",
    "Activity Submission",
    "Pitching Rounds",
    "Selection/Rejection",
    "Pre-Final",
    "Final Pitch",
    "Funding",
    "Incubation",
    "Post-Event Support",
]

for i, step in enumerate(FLOW_STEPS, start=1):
    knowledge_docs.append(
        {
            "doc_id": f"flow_{i:02d}",
            "title": f"{EVENT_NAME} Stage {i}: {step}",
            "section": "lifecycle",
            "content": (
                f"In {EVENT_NAME}, stage {i} is {step}. This stage includes clear instructions, deadlines, "
                f"review checkpoints, and support channels for participants in {STATE}. Teams should complete "
                "mandatory tasks on time and track updates on the official dashboard."
            ),
            "keywords": [step.lower(), "austartify", "startup", "process", "english"],
            "language": "en",
        }
    )

# Add expanded intent-guidance chunks to create a richer retrieval corpus
for intent in intents_payload["intents"]:
    for j in range(1, 9):
        knowledge_docs.append(
            {
                "doc_id": f"intent_{intent['tag']}_{j:02d}",
                "title": f"Guidance: {intent['tag']} Variant {j}",
                "section": "intent_guidance",
                "content": (
                    f"{EVENT_NAME} guidance for {intent['tag']}: {intent['goal']}. "
                    f"Recommended response approach: {intent['responses'][j % len(intent['responses'])]} "
                    "Always keep the response concise, factual, and aligned with official announcements."
                ),
                "keywords": [intent["tag"], "guidance", "assistant", "english", "austartify"],
                "language": "en",
            }
        )

# Funding knowledge chunks
funding_chunks = [
    "Funding is milestone-based and linked to review outcomes.",
    "A common disbursement structure is 50% + 30% + 20%.",
    "Teams must submit utilisation proof and progress reports.",
    "Grant usage must align with approved startup development activities.",
    "Missed milestones can delay or pause future disbursement.",
    "Cash prizes are award-based, while grants are goal-based support.",
]

for i, text in enumerate(funding_chunks, start=1):
    knowledge_docs.append(
        {
            "doc_id": f"funding_{i:02d}",
            "title": f"Funding Policy Chunk {i}",
            "section": "funding",
            "content": text,
            "keywords": ["funding", "grant", "cash prize", "milestone", "finance"],
            "language": "en",
        }
    )

# Multi-turn dialogue dataset
dialogues = []
for i in range(1, 1801):
    intent = random.choice(intents_payload["intents"])
    user_q = random.choice(intent["patterns"])
    assistant_a = random.choice(intent["responses"])
    followup = random.choice([
        "What should we do next?",
        "Any deadline we should track?",
        "Can you keep the answer short?",
        "Is this same for all teams?",
        "Can rejected teams try again?",
    ])
    followup_answer = random.choice([
        "Check your dashboard timeline and complete tasks before the due date.",
        "Yes, this process is standard, but official updates may revise details.",
        "Yes, rejected teams can improve and re-enter through the next cycle.",
        "Track announcements via email and dashboard notifications.",
        "Prepare documents early to avoid last-minute issues.",
    ])

    dialogues.append(
        {
            "conversation_id": f"conv_{i:04d}",
            "language": "en",
            "messages": [
                {"role": "user", "text": user_q},
                {"role": "assistant", "text": assistant_a},
                {"role": "user", "text": followup},
                {"role": "assistant", "text": followup_answer},
            ],
            "primary_intent": intent["tag"],
        }
    )

# Write files
intents_file = OUTPUT_DIR / "austartify_intents_large.json"
qa_file = OUTPUT_DIR / "austartify_qa_large.jsonl"
knowledge_file = OUTPUT_DIR / "austartify_knowledge_chunks.jsonl"
dialogue_file = OUTPUT_DIR / "austartify_dialogues_large.jsonl"
summary_file = OUTPUT_DIR / "DATASET_SUMMARY.md"

intents_file.write_text(json.dumps(intents_payload, ensure_ascii=False, indent=2), encoding="utf-8")

with qa_file.open("w", encoding="utf-8") as f:
    for row in qa_records:
        f.write(json.dumps(row, ensure_ascii=False) + "\n")

with knowledge_file.open("w", encoding="utf-8") as f:
    for row in knowledge_docs:
        f.write(json.dumps(row, ensure_ascii=False) + "\n")

with dialogue_file.open("w", encoding="utf-8") as f:
    for row in dialogues:
        f.write(json.dumps(row, ensure_ascii=False) + "\n")

summary = f"""# Austartify English Chatbot Dataset

Generated files:
- `austartify_intents_large.json`
- `austartify_qa_large.jsonl`
- `austartify_knowledge_chunks.jsonl`
- `austartify_dialogues_large.jsonl`

## Counts
- Intents: {len(intents_payload['intents'])}
- Patterns per intent: 120
- Total intent patterns: {sum(len(i['patterns']) for i in intents_payload['intents'])}
- QA pairs: {len(qa_records)}
- Knowledge chunks: {len(knowledge_docs)}
- Dialogues: {len(dialogues)}

## Suggested usage
1. Intent classification: train on `tag` + `patterns`.
2. RAG retrieval index: ingest `austartify_knowledge_chunks.jsonl` + `austartify_qa_large.jsonl`.
3. Supervised chat fine-tuning: use `austartify_dialogues_large.jsonl`.
4. Evaluation set: hold out 15% randomly from QA/dialogues.

## English-only policy
All records are generated in English to match deployment requirements.
"""
summary_file.write_text(summary, encoding="utf-8")

# Complete, detailed master dataset (requested schema + expanded examples)
complete_dataset = {
    "meta": {
        "dataset_name": "austartify_complete_dataset",
        "language": "en",
        "english_only": True,
        "generated_at": datetime.utcnow().isoformat() + "Z",
        "region": f"{CITY}, {STATE}",
        "version": "2.0",
    },
    "startup_flow": MASTER_FLOW,
    "funding_structure": {
        "stage_1": {"duration": "1-4 months", "fund_percentage": "50%"},
        "stage_2": {"duration": "5-8 months", "fund_percentage": "30%"},
        "stage_3": {"duration": "9-12 months", "fund_percentage": "20%"},
    },
    "final_stage": {
        "final_pitch": "Physical presentation",
        "evaluation": "Jury evaluation",
        "output": "Selected startups receive funding",
        "rejection": "Redirected to rebootcamp",
    },
    "post_funding": {
        "requirements": [
            "Prototype development",
            "Maintain bank account",
            "Submit bills",
            "Provide utilization certificate",
        ],
        "next_stage": "Secondary funding / Market expansion fund",
    },
    "decision_tree": [
        {
            "stage": "Zonal Pitching",
            "if_selected": "Pre-Final",
            "if_rejected": "Rebootcamp",
        },
        {
            "stage": "Pre-Final",
            "if_selected": "Final",
            "if_rejected": "Rebootcamp",
        },
        {
            "stage": "Final",
            "if_selected": "Funding",
            "if_rejected": "Rebootcamp",
        },
    ],
    "intents": [],
    "qa_dataset": [],
}

for seed in ADVANCED_INTENT_SEED:
    patterns = generate_advanced_patterns(seed["topic"], seed["base_patterns"], 140)
    responses = [
        seed["base_response"],
        f"In {EVENT_NAME}, {seed['base_response'].lower()}",
        f"{seed['base_response']} Follow official dashboard notifications for exact updates.",
        f"{seed['base_response']} If you need stage-specific help, share your team ID with support.",
    ]

    complete_dataset["intents"].append(
        {
            "tag": seed["tag"],
            "patterns": patterns,
            "responses": responses,
            "context": seed["context"],
        }
    )

    for idx, q in enumerate(patterns, start=1):
        complete_dataset["qa_dataset"].append(
            {
                "id": f"complete_qa_{seed['tag']}_{idx:03d}",
                "question": q,
                "answer": random.choice(responses),
                "intent": seed["tag"],
                "language": "en",
            }
        )

# Keep the specific sample Q&A requested by user as canonical examples
complete_dataset["qa_dataset"][:0] = [
    {
        "id": "sample_qa_001",
        "question": "What happens after registration?",
        "answer": "After registration, users form teams and attend orientation.",
        "intent": "registration",
        "language": "en",
    },
    {
        "id": "sample_qa_002",
        "question": "What is bootcamp?",
        "answer": "Bootcamp includes training, idea validation, and activities.",
        "intent": "bootcamp",
        "language": "en",
    },
    {
        "id": "sample_qa_003",
        "question": "What happens if I get rejected?",
        "answer": "You will be sent to rebootcamp for improvement.",
        "intent": "rejection",
        "language": "en",
    },
    {
        "id": "sample_qa_004",
        "question": "What is final round?",
        "answer": "Final round includes physical pitching and jury evaluation.",
        "intent": "final",
        "language": "en",
    },
    {
        "id": "sample_qa_005",
        "question": "How funding is distributed?",
        "answer": "Funding is given in stages: 50%, 30%, and 20%.",
        "intent": "funding",
        "language": "en",
    },
]

complete_file = OUTPUT_DIR / "austartify_complete_dataset.json"
complete_file.write_text(json.dumps(complete_dataset, ensure_ascii=False, indent=2), encoding="utf-8")

print("Dataset generated successfully")
print(f"Intents: {len(intents_payload['intents'])}")
print(f"Total patterns: {sum(len(i['patterns']) for i in intents_payload['intents'])}")
print(f"QA pairs: {len(qa_records)}")
print(f"Knowledge chunks: {len(knowledge_docs)}")
print(f"Dialogues: {len(dialogues)}")
print(f"Complete intents: {len(complete_dataset['intents'])}")
print(f"Complete QA records: {len(complete_dataset['qa_dataset'])}")
