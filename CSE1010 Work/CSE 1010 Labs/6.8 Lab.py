def int_to_reverse_binary(integer_value):
    input_string = ''
    while(integer_value > 0):
        if integer_value % 2 == 0:
            input_string += "0"
        else:
            input_string += "1"
        integer_value = int(integer_value // 2)
    return input_string

def string_reverse(input_string):
    return(input_string[::-1])
    #reverse = ''
    #for i in range(len(input_string-1), -1,-1):
    #    reverse += integer_value[i]
    #return reverse

if __name__ == '__main__':
    integer_value = int(input())
    input_string = ''
    result = int_to_reverse_binary(integer_value)
    result = string_reverse(input_string)
    print(str(result))