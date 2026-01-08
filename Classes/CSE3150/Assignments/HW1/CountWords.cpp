// Usage: ./CountWords  <filename>
// Read a file as given as the first parameter, count the number of spaces in the file and output it
// If no file or bad file is provided, just quit

#include <iostream>
#include <fstream>
using namespace std;

int CountWords(char const *fileInput){
    // Your code goes here
    // open file

    std::ifstream f(fileInput);

    int count = 0;
    char c;
    while (f.get(c)) {
        if (c == ' ') {
            count ++;
        }
    }
    f.close();


   return count;

}