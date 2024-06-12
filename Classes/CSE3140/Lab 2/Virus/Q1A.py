"""
This script writes the names of all python files in the current working directory to ./py_file_names.txt, seperated by newlines.

Also prints the name of the file containing the list of filenames.

Usage:
    python Q1A.py
"""

import os

current_directory = os.getcwd()

files = os.listdir(current_directory)

py_files = [file for file in files if file.endswith(".py")]

output_filename = "py_file_names.txt"

with open(output_filename, "w") as output_file:
    for py_file in py_files:
        output_file.write(py_file + "\n")

print(output_filename)