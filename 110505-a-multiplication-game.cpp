/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110505&format=html
 */

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long double n;
    int divider = 9;
    int times = 0;
    while (cin >> n) {
        times = 0;

        do {
            n /= divider;
            ++times;
            divider = ((divider == 9)? 2 : 9);
        } while (n > 1); 

        if (times % 2 == 0) {
            cout << "Ollie wins." << endl;
        } else {
            cout << "Stan wins." << endl;
        }
    }
}
