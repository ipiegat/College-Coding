class ItemToPurchase:
    def __init__(self, item_name = "none", item_description = "none", item_price = 0, item_quantity = 0):
        self.item_name = item_name
        self.item_description = item_description
        self.item_price = item_price
        self.item_quantity = item_quantity
    
    def item_cost(self):
        total_item_cost = self.item_quantity*self.item_price
        return total_item_cost
    
    def print_item_cost(self):
        print(f"{self.item_name} {self.item_quantity} @ ${self.item_price} = ${self.item_cost()}")
    
    def print_item_description(self):
        print(f"{self.item_name}: {self.item_description}")


class ShoppingCart:
    def __init__(self, customer_name = "none", current_date = "January 1, 2016"):
        self.customer_name = customer_name
        self.current_date = current_date
        self.cart_items = []
    
    def add_item(self, itemToPurchase):
        self.cart_items.append(itemToPurchase)
    
    def remove_item(self, item_name):
        item = None
        for i in self.cart_items:
            if i.item_name == item_name:
                item = i
                break
        if item is None:
            print("Item not found in cart. Nothing removed.")
        else:
            self.cart_items.remove(item)
    
    def modify_item(self, itemToPurchase):
        item = None
        for i in self.cart_items:
            if i.item_name == itemToPurchase.item_name:
                item = i
                break
        if item is None:
            print("Item not found in cart. Nothing modified.")
        else:
            item.item_quantity = itemToPurchase.item_quantity 
    
    def get_num_items_in_cart(self):
        return sum([i.item_quantity for i in self.cart_items])
        
    def get_cost_of_cart(self):
        return sum([i.item_cost() for i in self.cart_items])
        
    def print_total(self):
        print(f"{self.customer_name}'s Shopping Cart - {self.current_date}")
        print(f"Number of Items: {self.get_num_items_in_cart()}\n")
        for i in self.cart_items:
            i.print_item_cost()
        if len(self.cart_items) == 0:
            print("SHOPPING CART IS EMPTY")
        print(f"\nTotal: ${self.get_cost_of_cart()}\n")
    
    def print_descriptions(self):
        print(f"{self.customer_name}'s Shopping Cart - {self.current_date}\n\nItem Descriptions")
        for i in self.cart_items:
            i.print_item_description()
        print()
    
    def print_name_and_date(self):
        print(f"Customer name: {self.customer_name}")
        print(f"Today's date: {self.current_date}") 

def print_menu():
    print("MENU")
    print("a - Add item to cart")
    print("r - Remove item from cart")
    print("c - Change item quantity")
    print("i - Output items' descriptions")
    print("o - Output shopping cart")
    print("q - Quit")

def execute_menu(selected_char, s):
    if selected_char == "a":
        print("ADD ITEM TO CART")
        s.add_item(ItemToPurchase(str(input("Enter the item name:\n")), str(input("Enter the item description:\n")), int(input("Enter the item price:\n")), int(input("Enter the item quantity:\n"))))
        print()
    elif selected_char == "r":
        print("REMOVE ITEM FROM CART")
        s.remove_item(str(input("Enter name of item to remove:\n")))
        print()
    elif selected_char == "c":
        print("CHANGE ITEM QUANTITY")
        s.modify_item(ItemToPurchase(item_name = str(input("Enter the item name:\n")), item_quantity = int(input("Enter the new quantity:\n"))))
        print()

    elif selected_char == "i":
        print("OUTPUT ITEMS' DESCRIPTIONS")
        s.print_descriptions()
    elif selected_char == "o":
        print("OUTPUT SHOPPING CART")
        s.print_total()
    else:
        return False
    
    return True
    

if __name__ == "__main__":
    customer_name = str(input("Enter customer's name:\n"))
    current_date = str(input("Enter today's date:\n"))
    s = ShoppingCart(customer_name, current_date)
    print()
    s.print_name_and_date()
    print()
    print_menu()
    print()
    selected_char = str(input("Choose an option:\n"))
    while selected_char != "q":
        char_valid = execute_menu(selected_char, s)
        if char_valid:
            print_menu()
            print()
        selected_char = str(input("Choose an option:\n"))
    
    
    
    