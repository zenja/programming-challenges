/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110101&format=html
 */

#include <iostream>

using namespace std;

unsigned long getMaxCycle(unsigned long a);
unsigned long getMaxCycleBetween(unsigned long a, unsigned long b);

int main()
{
    int a, b;

    while (cin >> a >> b) {
        unsigned long maxCycle = getMaxCycleBetween(min(a,b), max(a,b));
        cout << a << " " << b << " " << maxCycle << endl;
    }
}

unsigned long getMaxCycle(unsigned long a)
{
    if ( a == 0) return 0;

    unsigned long cycle = 1;

    while (a != 1) {
        if (a % 2 == 0) {
            a /= 2;
        } else {
            a = 3*a + 1;
        }
        cycle++;
    }

    return cycle;
}

unsigned long getMaxCycleBetween(unsigned long a, unsigned long b)
{
    unsigned long maxCycle = 0;

    for (unsigned long i = a; i <= b; ++i) {
        unsigned long cycle = getMaxCycle(i);
        maxCycle = maxCycle > cycle ? 
            maxCycle : cycle;
    }

    return maxCycle;
}
