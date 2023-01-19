"""
make a food receipt 

get the name, price, and quantity 
print the receipt
get the name, price, and quantity of second item
print receipt
print third receipt with 15% increase in cost
    total cost, percentage increase cost, and grand cost
"""

item1 = input("Enter food item name:\n")

# FIXME (1): Finish reading item price and quantity, then output a receipt

price1 = float(input("Enter item price:\n"))
quantity1 = int(input("Enter item quantity:\n"))
print("\nRECEIPT")
print(quantity1, item1, f"@ ${price1:.2f} = ${quantity1*price1:.2f}")
print(f"Total cost: ${quantity1*price1:.2f}")
print("\n")

# FIXME (2): Read in a second food item name, price, and quantity, then output a second receipt

item2 = input("Enter second food item name:\n")
price2 = float(input("Enter item price:\n"))
quantity2 = int(input("Enter item quantity:\n"))
print("\nRECEIPT")
print(quantity1, item1, f"@ ${price1:.2f} = ${quantity1*price1:.2f}")
print(quantity2, item2, f"@ ${price2:.2f} = ${quantity2*price2:.2f}")
print(f"Total cost: ${(quantity2*price2)+(quantity1*price1):.2f}\n")

# FIXME (3): Add a gratuity and total with tip to the second receipt

print(f"15% gratuity: ${((quantity2*price2)+(quantity1*price1))*.15:.2f}")
print(
    f"Total with tip: ${(((quantity2*price2)+(quantity1*price1))*.15)+((quantity2*price2)+(quantity1*price1)):.2f}"
)
