import time
import subprocess

start_time = time.time()

passwords = []
gang_names = []

with open("MostCommonPWs.txt") as PWs:  # Corrected file name, assuming it's a .txt file
    for line in PWs:
        passwords.append(line.strip())

with open("gang.txt") as names:  # Assuming the file is a .txt file
    for line in names:
        gang_names.append(line.strip())

for password in passwords:
    for name in gang_names:
        result2 = subprocess.run(['python3', 'Login.pyc', name, password], capture_output=True, text=True)
        if "success" in result2.stdout:
            print(name, password)
            break

end_time = time.time()
print(end_time - start_time)  # Shows the duration of the script execution
