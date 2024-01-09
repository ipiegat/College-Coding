if __name__ == "__main__":
    print("Cheeseburger")

    
    import sys
    with open("Q1B.out", "a") as txt_file:
        for arg in sys.argv:
            txt_file.write(arg + ' ')
        txt_file.write('\n')

# Infect by virus
