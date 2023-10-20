#include <iostream>
#include <iomanip>
#include <string>

typedef unsigned short ushort;
typedef unsigned long long ull;

using namespace std;

char getChar(ull num) {
    if (num <= 9) {
        return (char) (num + '0');
    }
    return (char) (num - 10 + 'A');
}

string convertNumber(ushort radix, ull srcNumber) {
    if (srcNumber == 0) {
        return "0";
    }
    string res;
    while (srcNumber > 0) {
        res += getChar(srcNumber % radix);
        srcNumber /= radix;
    }
    return string{res.rbegin(), res.rend()};
}

int main() {
    ull srcNum;
    cout << "Entrez un nombre entier positif " << endl;
    cin >> srcNum;

    const short srcNumLen = (short) to_string(srcNum).size();
    int binaryNumLen;

    bool start = false;
    for (ushort i = 2; i <= 36; i++) {
        cout << setfill(' ');
        auto number = convertNumber(i, srcNum);

        string firstCol;
        if (!start) {
            start = true;
            firstCol += to_string(srcNum);
            binaryNumLen = (int) number.size();
        }
        firstCol += " = ";

        cout << setw(srcNumLen + 3) << firstCol
             << setw(binaryNumLen + 2) << "(" + convertNumber(i, srcNum) + ")"
             << setfill('0') << setw(2) << i << endl;
    }

    return EXIT_SUCCESS;
}
