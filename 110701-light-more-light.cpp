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
        long long sqrtOfN = sqrt(n);
        if (sqrtOfN * sqrtOfN == n) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }

        cin >> n;
    }
}
