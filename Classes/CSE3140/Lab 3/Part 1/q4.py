from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad


def Decryption(output_file, input_file):
    with open(output_file, 'rb') as file:
        iv = file.read(16)  
        encrypted_data = file.read()  


    with open("/home/cse/Lab3/Q4files/.key.txt", 'rb') as key_file:
        encryption_key = key_file.read()


    cipher = AES.new(encryption_key, AES.MODE_CBC, iv=iv)
    decrypted_data = unpad(cipher.decrypt(encrypted_data), AES.block_size)
   
    with open(input_file, 'wb') as decrypted_file:
        decrypted_file.write(decrypted_data)


    print(decrypted_data.strip())


if __name__ == "__main__":
    output_file = '/home/cse/Lab3/Q4files/Encrypted4'  
    input_file = 'Decrypted.txt'  
    Decryption(output_file=output_file, input_file=input_file)