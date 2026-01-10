#include <iostream>
#include <string>

int main() {
    std::cout << "Give me a word: ";
    std::string s;
    std::getline(std::cin, s);

    unsigned long long hash = 1469598103934665603ULL; // FNV-1a 64-bit offset basis
    for (unsigned char c : s) {
        hash ^= c;
        hash *= 1099511628211ULL; // FNV-1a 64-bit prime
    }

    std::cout << "Your word: " << s << "\n";
    std::cout << "A deterministic 64-bit hash of it: " << hash << "\n";
    std::cout << "(Try changing one character and see how much the hash changes.)\n";
    return 0;
}
