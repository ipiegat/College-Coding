// Your code goes here
#include <iostream>
#include <string>

std::string HelloWorld() 
{
    return "Hello, World!";
}

int main()
{
    std::string result = HelloWorld();
    std::cout << result << std::endl;
    return 0;
}