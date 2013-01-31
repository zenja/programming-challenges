/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110201&format=html
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int main()
{
    string line;
    while (getline(cin, line)) {
        // parse line
        vector<int> numbers;
        stringstream ss;
        ss << line;
        unsigned int numNumbers;
        int theNumber;
        ss >> numNumbers;
        for (unsigned int i = 0; i < numNumbers; ++i) {
            ss >> theNumber;
            numbers.push_back(theNumber);
        }

        // judge jolly or not
        bool isJolly = true;

        vector<bool> vJolly(numbers.size() - 1, false);

        for (unsigned int i = 0; i < numbers.size() - 1; ++i) {
            unsigned int difference = abs(numbers[i] - numbers[i+1]);
            if (difference >= numbers.size() || difference < 1) {
                isJolly = false;
                break;
            } else {
                vJolly[difference - 1] = true;
            }
        }
        for (unsigned int i = 0; i < vJolly.size(); ++i) {
            if (vJolly[i] == false) {
                isJolly = false;
                break;
            }
        }

        if (isJolly == true) {
            cout << "Jolly" << endl;
        } else {
            cout << "Not jolly" << endl;
        }
    }
}
