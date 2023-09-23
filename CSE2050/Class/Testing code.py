def oddSumHelp(count, bound, value):
    odd_sum = 0
    odd_numbers = []

    if odd_sum == value:
        return True
    
    num = 1
    for _ in range(count):
        if num >= bound:
            break

        odd_numbers.append(num)
        num += 2
    
    odd_sum += sum(odd_numbers)

    if odd_sum > value:
        remainder = odd_sum % value
        if remainder % 2 == 1:
            odd_numbers.remove(remainder)
            odd_sum = sum(odd_numbers)
        else:
            odd_numbers.remove(1)
            odd_sum += sum(odd_numbers)
            new_value = value - odd_sum
            odd_numbers.remove(new_value)

     #else:
      #  excess = value % odd_sum
       # if excess % 2 == 1:
        #    odd_numbers.remove(remainder)
         #   odd_sum = sum(odd_numbers)
    

    print(odd_numbers)
    print(odd_sum)


if __name__ == "__main__":
    x = oddSumHelp(4, 10, 17)


