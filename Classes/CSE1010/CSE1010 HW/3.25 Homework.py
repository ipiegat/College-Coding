# define the function


def a(total_sqft, ppg_cost, number_of_exor):
    nog = total_sqft / 200
    noh = total_sqft / 20
    cop = (total_sqft / 200) * ppg_cost
    col = (total_sqft / 20) * 40
    coe = number_of_exor * 100
    return (
        nog,  # number of gallons
        noh,  # number of labor hours
        cop,  # cost of paint
        col,  # cost of labor
        coe,  # exorcism cost
        cop + col + coe,  # total cost
    )


# ask for input
sqft_painted = float(input("How many sqft is required to be painted?\n"))
ppg = float(input("What is the paint price per gallon?\n"))
demons = float(input("How many demons need to be exorcised?\n"))

# call the function and print
print(a(sqft_painted, ppg, demons))
