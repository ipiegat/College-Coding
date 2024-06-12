# This is the ransomware program that encrypts a specified file.  
# Make sure you spend time to understand how it works.  
# Feel free to change the input file to get a snesne of the programs capabilities.  
# The given input program is an example .txt file, with several made up passwords.  


#Use the following link to read documentation on this imported library:
        #https://pycryptodome.readthedocs.io/en/latest/


from Crypto.PublicKey import RSA


key = RSA.generate(2048)
pub_key = key.publickey().export_key()
priv_key = key.export_key()


with open("/home/cse/Lab3/Solutions/d.key", "wb") as file:
    file.write(priv_key)


with open("/home/cse/Lab3/Solutions/e.key", "wb") as file:
    file.write(pub_key)
