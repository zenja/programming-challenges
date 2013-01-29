/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110501&format=html
 */

#include <iostream>

using namespace std;

unsigned int get_carry_num(unsigned int a, unsigned int b);

int main()
{
    unsigned int a, b;
    cin >> a >> b;
    while (a != 0 || b != 0) {
        int numCarries =  get_carry_num(a, b);
        if (numCarries == 0) {
            cout << "No carry operation." << endl;
        } else if (numCarries == 1) {
            cout << "1 carry operation." << endl;
        } else {
            cout << numCarries << " carry operations." << endl;
        }

        cin >> a >> b;
    }
}

/* a and b are unsigned int with less than 10 digits */
unsigned int get_carry_num(unsigned int a, unsigned int b)
{
    int c = 0;
    int cNum = 0;
    while ((a > 0) || (b > 0)) {
        if (a%10 + b%10 + c >= 10) {
            c = 1;
            cNum++;
        } else {
            c = 0;
        }

        a /= 10;
        b /= 10;
    }

    return cNum;
}
