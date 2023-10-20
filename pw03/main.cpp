#include "longmath.h"
#include <iostream>

using namespace std;
using namespace longMath;

int main() {

    size_t const CAPA = 100;
    DigitType a[CAPA]; size_t na;
    DigitType b[CAPA]; size_t nb;
    DigitType c[CAPA]; size_t nc;

    while(true) {
       cout << "Entrez un calcul sous la forme 123 + 345 ou 234 * 567 en utilisant au plus " << CAPA
            << " chiffres decimaux" << endl;
       char op;
       string sa, sb;
       if (cin >> sa >> op >> sb) {
          if (from_string(sa, a, na, CAPA) and from_string(sb, b, nb, CAPA)) {
             switch (op) {
                case '+':
                   add(a, na, b, nb, c, nc, CAPA);
                   break;
                case '*':
                   multiply(a, na, b, nb, c, nc, CAPA);
                   break;
                default:
                   cout << "Operation inconnue" << endl;
                   continue;
             }
             cout << to_string(a, na)
                  << ' ' << op << ' '
                  << to_string(b, nb)
                  << " = "
                  << to_string(c, nc) << endl;
          } else break;
       } else break;
    }
}
