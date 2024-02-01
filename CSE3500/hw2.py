import os

directory_path = r"C:\Users\ipieg\OneDrive\College-Coding\CSE3500\CollectionNumbers"
num_list = []

for file_name in os.listdir(directory_path):
        if file_name.endswith("nsol.txt"):
            with open(file_name, "r") as f:
                for line in f:
                    line = int(line)
                    num_list.append(line)

print(num_list)
