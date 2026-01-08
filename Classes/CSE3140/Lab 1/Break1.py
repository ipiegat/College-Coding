import time
import subprocess

x = 1

start_time = time.time()

passwords = []


with open("MostCommonPWs.txt") as PWs:  
    for line in PWs:
        passwords.append(line.strip())  


for password in passwords:
    subprocess.run(['python3', 'Login.pyc', 'Adam', password])

end_time = time.time()

print(passwords)
print("Time taken:", end_time - start_time)  
