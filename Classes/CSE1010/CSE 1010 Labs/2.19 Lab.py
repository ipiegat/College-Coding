"""goal: find amounts of stuff for given number fo servings, convert to gallons

high level structure:
get reference servings and quantities
get desired servings
compute desired quantities
print desired quantities
print conversion to gallons

pseudocode:
read in lemon juice
read in water
read in agave
read in servings

print out everything

read in desired servings

compute needed quantities (= reference * ratio of reference to desired)
print desired quantities

print desired / 16"""


lemon_juice_cups = 2  # float(input("Enter amount of lemon juice (in cups):\n"))

# FIXME (1): Finish reading other items into variables, then output the three ingredients

water = 16  # float(input("Enter amount of water (in cups):\n"))
agave = 2.5  # float(input("Enter amount of agave nectar (in cups):\n"))
servings = 6  # float(input("How many servings does this make?\n"))

# FIXME (2): Prompt user for desired number of servings. Convert and output the ingredients

print("\nLemonade ingredients - yields", (f"{servings:.2f}"), "servings")
print((f"{lemon_juice_cups:.2f}"), "cup(s) lemon juice")
print((f"{water:.2f}"), "cup(s) water")
print((f"{agave:.2f}"), "cup(s) agave nectar\n")

servings2 = 48  # float(input("How many servings would you like to make?\n"))
print("\nLemonade ingredients - yields", (f"{servings2:.2f}"), "servings")
print(f"{(lemon_juice_cups/servings)*servings2:.2f} cup(s) lemon juice")
print(f"{(water/servings)*servings2:.2f} cup(s) water")
print(f"{(agave/servings)*servings2:.2f} cup(s) agave nectar")

# FIXME (3): Convert and output the ingredients from (2) to gallons

print("\nLemonade ingredients - yields", (f"{servings2:.2f}"), "servings")
print(f"{((lemon_juice_cups/servings)*servings2)/16:.2f} gallon(s) lemon juice")
print(f"{((water/servings)*servings2)/16:.2f} gallon(s) water")
print(f"{((agave/servings)*servings2)/16:.2f} gallon(s) agave nectar\n")
