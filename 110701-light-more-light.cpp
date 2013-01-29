/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110701&format=html
 */

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long n;
    cin >> n;
    while (n != 0) {
        int numDivides = 0;

        int upperBound = sqrt(n);

        for (int i = 1; i <= upperBound; ++i) {
            if (n % i == 0) ++numDivides;
        }

        ++numDivides;

        if (numDivides % 2 == 0) {
            cout << "no" << endl;
        } else {
            cout << "yes" << endl;
        }

        cin >> n;
    }
}
