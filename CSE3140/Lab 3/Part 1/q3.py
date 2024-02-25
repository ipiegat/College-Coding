import os
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA




def keyExchange(pk, directory):
    # go through each file in the directory
    for file_name in directory:
        if ".sign" in file_name:
            exefile = file_name.replace(".sign", "")
            exepath = os.path.join("Q3files", exefile)
            with open(exepath, "rb") as f:
                exeContents = f.read()
                sigpath = os.path.join("Q3files", file_name)
            with open(sigpath, "rb") as f:
                signature = f.read()
                h = SHA256.new(exeContents)
                public_key = RSA.import_key(pk)
            try:
                pkcs1_15.new(public_key).verify(h, signature)
                print(f"Correctly signed file: {file_name}")


            except Exception as e:
                print(str(e))


if __name__ == "__main__":
    # Load public key
    with open("Q3pk.pem", "r") as key_file:
        public_key = key_file.read()
        directoryFiles = [f for f in os.listdir("Q3files")]
        keyExchange(pk=public_key, directory=directoryFiles)
