import time
import subprocess
import hashlib 

def main():
  start_time = time.time()

  gang_names = set()
  with open("gang") as gang_file:
    gang_names.update(line.strip() for line in gang_file)
  
  #disgard already found gang members
  #gang_names.discard("Bonnie")
  #gang_names.discard("Adam")
  #gang_names.discard("Benedict")
  #gang_names.discard("Richard")
  
  # find name, salt, and salted hash
  name_to_salt = {}
  name_to_salted_hash = {}
  with open("SaltedPWs", encoding="utf8") as salted_pws:
    # map data {name: salt}, {name: salted hash}
    for line in salted_pws:
      name, salt, salted_hash = line.strip().split(",")
      if name not in gang_names:
        continue
      
      if name not in name_to_salt:
        name_to_salt[name] = []
        name_to_salted_hash[name] = []
      name_to_salt[name].append(salt)
      name_to_salted_hash[name].append(salted_hash)

  # define search space  (100k file)
  with open("PwnedPWs100k", encoding="utf8") as pwned_passwords:
    for passwords in pwned_passwords:
      # strip pwned_passwords of white space
      password = passwords.strip()
      # add numbers 0-9 to end of each pwned password 
      for numbers in range(10):
        numbers = str(numbers)
        num_password = password+numbers
        # go through gang members
        for gang_name in gang_names:
          # if gang member name is in dictionary
          if gang_name in name_to_salt:
            # find gang member salt and salted hash
            for salt, salted_hash in zip(name_to_salt[gang_name], name_to_salted_hash[gang_name]):
                salted_password = salt+num_password
                #print(salt, salted_password)
                # create salted_hashed_pw to check against salted_hash
                salted_hashed_pw = hashlib.sha256(salted_password.encode()).hexdigest()
                salted_password.strip()
                salted_hashed_pw.strip()
                if salted_hash == salted_hashed_pw:
                    #print(f'1: {salted_hash}\n2: {salted_hashed_pw}\n')
                    result = subprocess.run(['python3', 'Login.pyc', gang_name, num_password],
                                        capture_output=True,
                                        text=True)
                    print(gang_name, num_password)
                    print(result.stdout)
                    if "success" in result.stdout:
                        print(name, num_password)
                        break
             
  end_time = time.time()
  elapsed_time = end_time - start_time
  print(elapsed_time)
  
  
if __name__ == "__main__":
  main()



"""
Jack angels17
Login successful.

Kalen angels17
Vlad darklord8
Login failed: incorrect password.

Jack yesterday17
Login failed: incorrect password.

Ted bigtime12
Login failed: incorrect password.

Vlad swoosh4
Login failed: incorrect password.

Anne fatty122
Login failed: incorrect password.

Donald jeremiah125
Login failed: incorrect password.

Jack chrisbrow18
Login failed: incorrect password.

John sorciere4
Login failed: incorrect password.

Anne 2206736
Login failed: incorrect password.

11.442211151123047

"""