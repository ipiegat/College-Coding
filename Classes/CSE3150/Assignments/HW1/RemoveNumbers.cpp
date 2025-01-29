#include <string>
using namespace std;

string RemoveNumbers(string strIn) {
    string result;

    for (char c : strIn) {
        // add c to result if not in numbers
        if (!isdigit(c)) {
            result += c;
        }
    }

    return result;

}
