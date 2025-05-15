import json, os
from config import DATA_TODAY, DATA_YESTERDAY, BASE_DIR

def save_current_data(data):
    os.makedirs(BASE_DIR, exist_ok=True)
    with open(DATA_TODAY, "w") as f:
        json.dump(data, f, indent=2)

def load_previous_data():
    if not os.path.exists(DATA_YESTERDAY):
        return []
    with open(DATA_YESTERDAY, "r") as f:
        return json.load(f)

def rotate_data_files():
    if os.path.exists(DATA_TODAY):
        os.replace(DATA_TODAY, DATA_YESTERDAY)
