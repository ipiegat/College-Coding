import hashlib
import os


directory = "/home/cse/Lab3/Q2files"
hashed_files_to_file = {}
for file in os.listdir(directory):
    file_path = os.path.join(directory, file)
    if os.path.isfile(file_path):
        with open(file_path, 'rb') as f:
            content = f.read()
            file_hash = hashlib.sha256(content).hexdigest()
        hashed_files_to_file[file] = file_hash


with open("Q2hash.txt", "r") as file:
    for line in file:
        expected_hash = line.strip()
        for file_name, file_hash in hashed_files_to_file.items():
            if expected_hash == file_hash:
                print(f"Located file: {file_name} with hash: {expected_hash}")
                break
