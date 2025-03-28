#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

// In this project, you will build a simple decryption tool using a 
// Caesar cipher—a substitution cipher where each character is shifted by 
// a fixed number of positions. Note that the shift should wrap around
// such that A left shifted by 1 should be Z and X right shifted by 5
// should be C. (Hint: use modulo)

// Cipher rules:
// Apply a Caesar cipher to uppercase letters (A-Z) with a left shift of 13
// Apply a Caesar cipher to lowercase letters (a-z) with a right shift of 8 
// Apply a Caesar cipher to numbers (0-9) with a right shift of 3
// Leave all other characters unchanged

// Implement ECCreateCipherMap() to generate a mapping of original characters to their encrypted versions.
// Implement ECDecryptMessage() to decode an encrypted message using the cipher map.




map<char, char> ECCreateCipherMap() {
    // TO DO: create cipher map
    map<char, char> cipher;

    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        cipher[ch] = (ch - 'A' - 13 + 26) % 26 + 'A';
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        cipher[ch] = (ch - 'a' + 8) % 26 + 'a';
    }

    for (char ch = '0'; ch <= '9'; ++ch) {
        cipher[ch] = (ch - '0' + 3) % 10 + '0';
    }

    return cipher;
}

template <typename Container>
string ECDecryptMessage(const map<char, char>& cipher, const Container& encrypted_text) {    
    // TO DO: apply cipher to encrypted text and return the decrypted text
    string result;
    for (const auto& ch : encrypted_text) {
        if (cipher.find(ch) != cipher.end()) {
            result += cipher.at(ch);
        } else {
            result += ch;
        }
    }
    return result;
}


/*
int main() {

    map<char, char> cipher =  ECCreateCipherMap();
    
    // Need to maintain order, so we will use sequence containers
    vector<char> v = {'U', 'w', 'd', 'd', 'g', ' ', 'J', 'g', 'j', 'd', 'v', '!'}; // Example vector input 
    string s = "V se P++ Zsf sfv V se zwjw lg ksnw lzw vsq!";  // Example string input 
    list<char> l = {'0', '.', '8', '1', '8', '2', '6', '9', '3', '2', '0', '2'};  // Example list input 
    
    // You will know when your cipher map works, because these messages will be clear!
    cout << "Vector input: " << ECDecryptMessage(cipher, v) << endl;
    cout << "String input: " << ECDecryptMessage(cipher, s) << endl;
    cout << "List input: " << ECDecryptMessage(cipher, l) << endl;
    
    return 0;
}
*/