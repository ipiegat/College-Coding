def file_writer(file, min, max):

    for num in range(min, max):
        with open(file, 'w') as file:
            file.write(str(num))

if __name__ == "__main__":
    test = file_writer(r"C:\Users\ipieg\OneDrive\College-Coding\Fun Stuff\Personal Projects\idek\some.txt", 52, 83)    
    
