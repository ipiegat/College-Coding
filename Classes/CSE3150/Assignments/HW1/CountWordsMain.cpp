// Usage: ./CountWords  <filename>
// Read a file as given as the first parameter, count the number of spaces in the file and output it
// If no file or bad file is provided, just quit
// Only submit Countwords.cpp
#include <iostream>
#include <fstream>
#include "CountWords.h"
using namespace std;

int CountWords(char const *);

int main(int argc, char const *argv[]){
    // Your code goes here

    if (argc != 2) {
        cout << "Wrong number of arguments." << endl;
        return 1;
    }	
    int spaceCount = CountWords(argv[1]);
    cout << "Number of words: " << spaceCount << endl;

   return 0;
}