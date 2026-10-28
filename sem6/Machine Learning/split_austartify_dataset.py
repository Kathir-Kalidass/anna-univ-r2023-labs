#!/usr/bin/env python3
import json
import random
from pathlib import Path

random.seed(42)

BASE = Path('/home/kathir/Drone_Smart_City/ml_data/datasets')
COMPLETE_FILE = BASE / 'austartify_complete_dataset.json'
DIALOGUES_FILE = BASE / 'austartify_dialogues_large.jsonl'

OUT_DIR = BASE / 'splits'
OUT_DIR.mkdir(parents=True, exist_ok=True)

TRAIN_RATIO = 0.8
VAL_RATIO = 0.1
TEST_RATIO = 0.1

assert abs((TRAIN_RATIO + VAL_RATIO + TEST_RATIO) - 1.0) < 1e-9


def split_records(records):
    rows = list(records)
    random.shuffle(rows)
    n = len(rows)
    n_train = int(n * TRAIN_RATIO)
    n_val = int(n * VAL_RATIO)
    train = rows[:n_train]
    val = rows[n_train:n_train + n_val]
    test = rows[n_train + n_val:]
    return train, val, test


def write_jsonl(path: Path, rows):
    with path.open('w', encoding='utf-8') as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + '\n')


# Split QA from complete dataset
complete = json.loads(COMPLETE_FILE.read_text(encoding='utf-8'))
qa = complete.get('qa_dataset', [])
qa_train, qa_val, qa_test = split_records(qa)

write_jsonl(OUT_DIR / 'qa_train.jsonl', qa_train)
write_jsonl(OUT_DIR / 'qa_val.jsonl', qa_val)
write_jsonl(OUT_DIR / 'qa_test.jsonl', qa_test)

# Split Dialogues
all_dialogues = []
with DIALOGUES_FILE.open('r', encoding='utf-8') as f:
    for line in f:
        all_dialogues.append(json.loads(line))

d_train, d_val, d_test = split_records(all_dialogues)

write_jsonl(OUT_DIR / 'dialogues_train.jsonl', d_train)
write_jsonl(OUT_DIR / 'dialogues_val.jsonl', d_val)
write_jsonl(OUT_DIR / 'dialogues_test.jsonl', d_test)

manifest = {
    'split_version': '1.0',
    'source_files': {
        'complete_dataset': str(COMPLETE_FILE.name),
        'dialogues_dataset': str(DIALOGUES_FILE.name),
    },
    'ratios': {
        'train': TRAIN_RATIO,
        'val': VAL_RATIO,
        'test': TEST_RATIO,
    },
    'counts': {
        'qa': {
            'total': len(qa),
            'train': len(qa_train),
            'val': len(qa_val),
            'test': len(qa_test),
        },
        'dialogues': {
            'total': len(all_dialogues),
            'train': len(d_train),
            'val': len(d_val),
            'test': len(d_test),
        }
    },
    'output_dir': str(OUT_DIR),
}

(OUT_DIR / 'SPLIT_MANIFEST.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding='utf-8')

print('Split generation completed')
print(json.dumps(manifest['counts'], indent=2))
