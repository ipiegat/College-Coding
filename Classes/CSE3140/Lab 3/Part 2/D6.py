import ast
from Crypto.Cipher import AES
import os


shared_key = ast.literal_eval(input())


for filename in os.listdir():
    if filename.endswith(".txt.encrypted"):
        with open(filename, "rb") as file:
            nonce, tag, ciphertext = [file.read(x) for x in (16, 16, -1)]


        cipher_aes = AES.new(shared_key, AES.MODE_EAX, nonce=nonce)
        file_data = cipher_aes.decrypt_and_verify(ciphertext, tag)


        with open(filename.replace(".encrypted", ""), "wb") as file:
            file.write(file_data)


