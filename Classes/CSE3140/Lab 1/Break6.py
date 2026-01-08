import time
import subprocess
import hashlib

def main():
    start_time = time.time()
    gang_names = set()

    with open("gang.txt", encoding="utf8") as gang_file:
        gang_names.update(line.strip() for line in gang_file)

    name_to_salt = {}
    name_to_salted_hash = {}
    with open("SaltedPWs.txt", encoding="utf8") as salted_pws:
        for line in salted_pws:
            name, salt, salted_hash = line.strip().split(",")
            if name not in gang_names:
                continue
            if name not in name_to_salt:
                name_to_salt[name] = []
                name_to_salted_hash[name] = []
            name_to_salt[name].append(salt)
            name_to_salted_hash[name].append(salted_hash)

    with open("PwnedPWs100k.txt", encoding="utf8") as pwned_passwords:
        for password in pwned_passwords:
            password = password.strip()
            for numbers in range(10):
                num_password = f"{password}{numbers}"
                for gang_name in gang_names:
                    if gang_name in name_to_salt:
                        for salt, salted_hash in zip(name_to_salt[gang_name], name_to_salted_hash[gang_name]):
                            salted_password = salt + num_password
                            salted_hashed_pw = hashlib.sha256(salted_password.encode()).hexdigest()
                            if salted_hashed_pw == salted_hash:
                                result = subprocess.run(['python3', 'Login.pyc', gang_name, num_password], capture_output=True, text=True)
                                if "success" in result.stdout:
                                    print(gang_name, num_password)
                                    break

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(elapsed_time)

if __name__ == "__main__":
    main()
