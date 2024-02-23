import time
import subprocess
import hashlib

def main():
    start_time = time.time()
    gang_names = set()

    with open("gang.txt") as gang_file:  # Assuming the file is a .txt file
        gang_names.update(line.strip() for line in gang_file)

    gang_names.discard("Bonnie")
    gang_names.discard("Adam")
    gang_names.discard("Benedict")

    hashes_to_potential_passwords = {}
    with open("PwnedPWs100k.txt") as passwords_file:  # Assuming the file is a .txt file
        for password in passwords_file:
            password = password.strip()
            for numbers in range(100):
                num_password = f"{password} {numbers:02d}"
                hashed_password = hashlib.sha256(num_password.encode()).hexdigest()
                hashes_to_potential_passwords[hashed_password] = num_password

    username_to_hashes = {}
    with open("HashedPWs.txt") as leaked_hashes:  # Assuming the file is a .txt file
        for line in leaked_hashes:
            name, leaked_hash = line.strip().split(",")
            if name in gang_names:
                username_to_hashes[name] = leaked_hash

    for name, leaked_hash in username_to_hashes.items():
        if leaked_hash in hashes_to_potential_passwords:
            num_password = hashes_to_potential_passwords[leaked_hash]
            result = subprocess.run(['python3', 'Login.pyc', name, num_password], capture_output=True, text=True)
            if "success" in result.stdout:
                print(name, num_password)
                break

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(elapsed_time)

if __name__ == "__main__":
    main()
