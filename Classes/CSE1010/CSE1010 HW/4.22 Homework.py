Oil_change = int(35)
Tire_rotation = int(19)
Car_wash = int(7)
Car_wax = int(12)

oil1 = "$" + str(Oil_change)
tire1 = "$" + str(Tire_rotation)
wash1 = "$" + str(Car_wash)
wax1 = "$" + str(Car_wax)

service1 = input()
service2 = input()

print("Davy's auto shop services", end="")
print("\nOil change --", oil1, end="")
print("\nTire rotation --", tire1, end="")
print("\nCar wash --", wash1, end="")
print("\nCar wax --", wax1)
print()
print("Select first service:")
print("Select second service:")
print()
print("Davy's auto shop invoice")
print()

service_array = ["Oil change", "Tire rotation", "-", "Car wash", "Car wax"]
cost_array = [35, 19, 0, 7, 12]

for i, val in enumerate(service_array):
    if val == service1:
        if val != "-":
            cost1 = cost_array[i]
            cost1 = "$" + str(cost1)
            service1 = str(service1) + ","
            print("Service 1:", service1, cost1)
            cost1 = cost_array[i]
        if val == "-":
            cost1 = cost_array[i]
            print("Service 1: No service")
    if val == service2:
        if val != "-":
            cost2 = cost_array[i]
            cost2 = "$" + str(cost2)
            service2 = str(service2) + ","
            print("Service 2:", service2, cost2)
            cost2 = cost_array[i]
        if val == "-":
            cost2 = cost_array[i]
            print("Service 2: No service")

total_cost = cost1 + cost2
total_cost = "$" + str(total_cost)
print()
print("Total:", total_cost)
