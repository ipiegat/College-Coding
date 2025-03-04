/*Instructions-
Write the function removeMatch which takes a vector of pointers to strings "string_pointers", 
	and a pointer to a string "to_remove" 
This function should remove any elements of the vector that point to the same string as to_remove. 
Note that we do not care about the value of the string being pointed to, only its address. 
Also note that we are not returning a new vector, we want to modify an existing vector. 
This is done by passing string_pointers by reference, rather than by value. 
For example: If you have a pointer p1 that points to string s1, where s1 equals "ABC" 
And a pointer p2 that points to a string s2, where s2 ALSO equals "ABC" 
If p1 is passed into remove_match as to_remove, only p1 should be removed from the vector. 
*/
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void removeMatch(vector<string *> &string_pointers, string *to_remove) {
    // Use erase-remove idiom to remove elements that point to the same address as to_remove
    string_pointers.erase(
        remove(string_pointers.begin(), string_pointers.end(), to_remove), string_pointers.end());
}
