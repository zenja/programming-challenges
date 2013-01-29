/*
 * http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110102&format=html
 */

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int get_mine_num(const vector<vector<int> >& matrix, int numRow, int numColumn, int x, int y);

int main()
{
    int numRow, numColumn;
    int groupIndex = 1;
    string strTmp;
    string line;

    cin >> numRow >> numColumn;
    while (numRow > 0 && numColumn > 0) {
        // remove newline
        getline(cin, strTmp);

        // initial matrix
        vector<vector<int> > matrix;
        // read mine map
        for (int i = 0; i < numRow; ++i) {
            vector<int> vLine(numColumn);
            getline(cin, line);
            for (int j = 0; j < numColumn; ++j) {
                if (line[j] == '*') {
                    vLine[j] = -1;
                } else {
                    vLine[j] = 0;
                }
            }
            matrix.push_back(vLine);
        }

        // handle matrix
        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numColumn; ++j) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] = get_mine_num(matrix, numRow, numColumn, i, j);
                }
            }
        }

        // output matrix
        cout << "Field #" << groupIndex << ":" << endl;
        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numColumn; ++j) {
                if (matrix[i][j] == -1) {
                    cout << '*';
                } else {
                    cout << matrix[i][j];
                }
            }
            cout << endl;
        }

        // receive next input
        cin >> numRow >> numColumn;
        ++groupIndex;

        // decide whether to output a new line
        if (numRow > 0 && numColumn > 0) {
            cout << endl;
        }
    }
}

int get_mine_num(const vector<vector<int> >& matrix, int numRow, int numColumn, int x, int y)
{
    vector<pair<int, int> > checkPoints(8);

    checkPoints[0].first = x-1;
    checkPoints[0].second = y-1;

    checkPoints[1].first = x-1;
    checkPoints[1].second = y;

    checkPoints[2].first = x-1;
    checkPoints[2].second = y+1;

    checkPoints[3].first = x;
    checkPoints[3].second = y-1;

    checkPoints[4].first = x;
    checkPoints[4].second = y+1;

    checkPoints[5].first = x+1;
    checkPoints[5].second = y-1;

    checkPoints[6].first = x+1;
    checkPoints[6].second = y;

    checkPoints[7].first = x+1;
    checkPoints[7].second = y+1;

    int numMine = 0;
    for (vector<pair<int, int> >::iterator it = checkPoints.begin(); it != checkPoints.end(); it++) {
        int xx = it->first;
        int yy = it->second;
        if ((xx >= 0 && yy >= 0) && (xx < numRow && yy < numColumn) && matrix[xx][yy] == -1) {
            ++numMine;
        }
    }

    return numMine;
}
