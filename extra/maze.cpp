/*
 * Solving maze problem.
 *
 * Input: a maze matrix like this:
 * *****   
 * *   *   
 * *S***   
 * *   ****
 * * *    *
 * *   *  *
 * ***** E*
 *     ****
 *
 * Output:
 * A graphic solution to the maze if it is solvable
 *
 */

#include <iostream>
#include <vector>

using namespace std;

bool solveMaze(vector<string>& maze, vector<vector<int> >& traceMatrix);
bool solveMaze(vector<string>& maze, vector<vector<int> >& traceMatrix, int numRow, int numCol, int x, int y);
void printSolution(vector<string>& maze, vector<vector<int> >& traceMatrix);

int main()
{
    string line;
    vector<string> maze;

    // input maze
    while (getline(cin, line)) {
        maze.push_back(line);
    }

    // the trace matrix
    // 0  - initial value
    // 1  - correct step
    // -1 - visited step that are not correct
    int numRow = maze.size();
    int numCol = maze[0].size();
    vector<vector<int> > traceMatrix;
    for (int i = 0; i < numRow; ++i) {
        vector<int> vRow(numCol, 0);
        traceMatrix.push_back(vRow);
    }

    bool isSolved = solveMaze(maze, traceMatrix);

    if (isSolved) {
        printSolution(maze, traceMatrix);
    } else {
        cout << "Not Solved!" << endl;
    }
}

bool solveMaze(vector<string>& maze, vector<vector<int> >& traceMatrix) {
    // find row and colume number
    int numRow = maze.size();
    int numCol = maze[0].size();

    // find start points
    int startX, startY;
    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < numCol; ++j) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
            }
        }
    }

    return solveMaze(maze, traceMatrix, numRow, numCol, startX, startY);
}

bool solveMaze(vector<string>& maze, vector<vector<int> >& traceMatrix, int numRow, int numCol, int x, int y) {
    if (x < 0 || x > numRow - 1 || y < 0 || y > numCol - 1) {
        return false;
    }

    if (maze[x][y] == '*') return false;

    if (traceMatrix[x][y] == -1) return false;

    if (maze[x][y] == 'E') return true;

    traceMatrix[x][y] = -1;

    if (solveMaze(maze, traceMatrix, numRow, numCol, x - 1, y) == true) {
        traceMatrix[x][y] = 1;
        return true;
    }
    if (solveMaze(maze, traceMatrix, numRow, numCol, x + 1, y) == true) {
        traceMatrix[x][y] = 1;
        return true;
    }
    if (solveMaze(maze, traceMatrix, numRow, numCol, x, y - 1) == true) {
        traceMatrix[x][y] = 1;
        return true;
    }
    if (solveMaze(maze, traceMatrix, numRow, numCol, x, y + 1) == true) {
        traceMatrix[x][y] = 1;
        return true;
    }

    return false;
}

void printSolution(vector<string>& maze, vector<vector<int> >& traceMatrix) {
    int numRow = maze.size();
    int numCol = maze[0].size();

    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < numCol; ++j) {
            if (maze[i][j] == '*') cout << '*';
            if (maze[i][j] == 'S') cout << 'S';
            if (maze[i][j] == 'E') cout << 'E';
            if (maze[i][j] == ' ') {
                if (traceMatrix[i][j] == 1) cout << 'X';
                else cout << ' ';
            }
        }
        cout << endl;
    }
}
