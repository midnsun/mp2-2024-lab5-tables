#include "myQueue.h"
#include "myList.h"
#include <iostream>
#include <random>
#include "polinom.h"
#include "commonHeader.h"
#include "unsortedArray.h"
#include "sortedArray.h"
#include "myHashTable.h"
#include "myAVLtree.h"

using namespace std;

void foo() {
    myHashTable<polinom> t;

    for (int i = 0; i < 1'000'000; ++i) {
        t.ins(Data<polinom>(stringToMyvec(to_string(i)), generatePolinom()));
    }

    system("pause");
}

int main() {
    foo();
    cout << "Hello, world!" << endl;
    system("pause");

    /*
    return 0;
    try {
        char c = ' ';
        polinom p;
        cout << "Format for polinoms is: [-]<number> * x<degx> y<degy> z<degz> <+/-> <number> etc. " << endl;
        cout << "Enter the polinom: " << endl;
        cin >> p;
        while (c != '0') {
            do {
                cout << endl << "Enter the action: 1 - add; 2 - multiply by number; 3 - multiply by other polinom; 4 - calculate; 0 - quit; other - retry" << endl;
                cin >> c;
            } while (c < '0' || c > '4');
            switch (c)
            {
            case '1':
            {
                cout << endl << "Enter ohter polinom: " << endl;
                polinom m;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> m;
                cout << endl << "The result is: " << p + m << endl;
                break;
            }
            case '2':
            {
                cout << endl << "Enter the number: " << endl;
                double v;
                cin >> v;
                cout << endl << "The result is: " << p * v << endl;
                break;
            }
            case '3':
            {
                cout << endl << "Enter ohter polinom: " << endl;
                polinom m;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> m;
                cout << endl << "The result is: " << p * m << endl;
                break;
            }
            case '4':
            {
                cout << endl << "Enter three numbers in a row: " << endl;
                double x, y, z;
                cin >> x >> y >> z;
                cout << endl << "The result is: " << p.calculate(x, y, z) << endl;
                break;
            }
            case '0':
                break;
            default:
                break;
            }
        }
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
    */
	return 0;
    
}