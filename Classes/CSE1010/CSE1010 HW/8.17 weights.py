# FIXME (1): Prompt for four weights. Add all weights to a list. Output list.
weights = []

for i in range(4):
    weights.append(float(input(f"Enter weight {i+1}:\n")))

print(f"Weights: {weights}\n")

# FIXME (2): Output average of weights.
# FIXME (3): Output max weight from list.

average = sum(weights)/len(weights)
largest = max(weights)
print(f"Average weight: {average:.2f}")
print(f"Max weight: {largest:.2f}\n")

# FIXME (4): Prompt the user for a list index and output that weight in pounds and kilograms.

print("Enter a list location (1 - 4):")
user_index = int(input())-1
print(f"Weight in pounds: {weights[user_index]:.2f}")
print(f"Weight in kilograms: {(weights[user_index]/2.2):.2f}\n")

# FIXME (5): Sort the list and output it.

sort = sorted(weights)
print(f"Sorted list: {sort}")