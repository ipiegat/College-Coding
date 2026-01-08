import argparse
from duckProcess import *

if __name__ == '__main__':
    #parser = argparse.ArgumentParser(description='Testing out the main.')

    #args = parser.parse_args()

    filePath = input("Input path of DuckyScript: ")
    
    valid = ValidateCode(filePath)

    if valid:
        npt = input("Script has been validated. Execute? (Y/n) : ")
        if npt == "Y" or npt == "y":
            ReadFile(filePath)