from Crypto.Hash import MD5
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad


def CalculateKeyFromR5(file_path):
    # Read the content of "R5.py"
    with open(file_path, 'rb') as r5_file:
        r5_content = r5_file.read()


    # Calculate the MD5 hash of the content
    md5_hash = MD5.new()
    md5_hash.update(r5_content)
    key = md5_hash.digest()
    return key


def Decryption(output_file, input_file, r5_file):
    encryption_key = CalculateKeyFromR5(r5_file)


    with open(output_file, 'rb') as file:
        iv = file.read(16)  
        encrypted_data = file.read()


    cipher = AES.new(encryption_key, AES.MODE_CBC, iv=iv)
    decrypted_data = unpad(cipher.decrypt(encrypted_data), AES.block_size)
   
    with open(input_file, 'wb') as decrypted_file:
        decrypted_file.write(decrypted_data)


    print(decrypted_data.strip())


if __name__ == "__main__":
    output_file = '/home/cse/Lab3/Q5files/Encrypted5'  
    input_file = 'Q5Decrypted.txt'
    r5_file = '/home/cse/Lab3/Q5files/R5.py'
    Decryption(output_file=output_file, input_file=input_file, r5_file=r5_file)
