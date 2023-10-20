#include <iostream>
#include <iomanip>
#include "montantEnToutesLettres.h"

using namespace std;

int main() {
    long double d;

    while (cin >> d) { // finir par EOF (Ctrl-D) ou autre chose qu'un nombre
        cout << fixed << setprecision(2)
             << d << endl
             << montantEnToutesLettres(d) << endl;
    }
}
