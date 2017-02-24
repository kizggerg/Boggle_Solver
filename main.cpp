#include <iostream>
#include <set>
#include "Words.h"

using namespace std;

struct doublePair{
    int left;
    int right;

    void print() {
        cout << "(" + to_string(left) + "," + to_string(right) + ")" << endl;
    }

    bool operator== (const doublePair& rhs) {
        return (left == rhs.left && right == rhs.right);
    }
};

bool operator <(const doublePair& x, const doublePair& y) {
    return tie(x.left, x.right) < tie(y.left, y.right);
}



// Functions
void parseString(string str, int row, int col);
void getData();
void printBoard();
void solve();
set<doublePair> potentialMoves(int row, int col);
set<doublePair> setDifference(set<doublePair> lhs, set<doublePair> rhs);

// Fields
string board[4][4]; // A 4 by 4 Boggle Board, where 0 in any spot is an invalid space.
set<string> solutions;
Words* validWords =  new Words();

int main() {
    cout << "Welcome to Greg's Boggle Solver." << endl;
    getData();
    printBoard();
    solve();
    delete validWords;
    return 0;
}

/**
 * Collects the user input to represent the board
 * ASSUMES String is Well-Formed
 * //TODO: Make more robust
 * @param str  The user input
 * @param row  The row to represent
 * @param col  The column to represent
 */
void parseString(string str, int row, int col) {
    if (str.length() == 0) return;
    if (str.substr(0, 1) == " ") {
        parseString(str.substr(1), row, col);
    }
    else {
        board[row][col] = str.substr(0, 1);
        parseString(str.substr(1), row, ++col);
    }
}

/**
 * Gathers data from user to represent board.
 * //TODO: Make more robust
 */
void getData() {
    string input = "";
    cout << "Enter the first row of the board: ";
    getline(cin, input); cout << endl;
    parseString(input, 0, 0);
    input = "";
    cout << "Enter the second row of the board: ";
    getline(cin, input); cout << endl;
    parseString(input, 1, 0);
    input = "";
    cout << "Enter the third row of the board: ";
    getline(cin, input); cout << endl;
    parseString(input, 2, 0);
    input = "";
    cout << "Enter the fourth row of the board: ";
    getline(cin, input); cout << endl;
    parseString(input, 3, 0);
}

/**
 * Prints the board to the user.
 */
void printBoard() {
    cout << "Your board looks like: " << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] + " ";
        }
        cout << endl;
    }
}

set<doublePair> setDifference(set<doublePair> lhs, set<doublePair> rhs) {
    set<doublePair> result;
    bool toAdd;
    for (doublePair pair1 : lhs) {
        toAdd = true;
        for (doublePair pair2 : rhs) {
            if (pair1 == pair2) toAdd = false;
        }
        if (toAdd) result.insert(pair1);
    }
    return result;
}

void solveBoard(int row, int col, set<doublePair> visited, string solution) {
    doublePair current; current.left = row; current.right = col; visited.insert(current);
    set<doublePair> moves = setDifference(potentialMoves(row, col), visited);
    if (validWords->isWord(solution)) solutions.insert(solution);
    if (moves.empty()) return;
    else {
        for (doublePair move : moves) {
            if (validWords->isFruitful(solution)) {
                solveBoard(move.left, move.right, visited, solution + board[move.left][move.right]);
           }
        }
    }
}

void printSolutions() {
  cout << "You can make a the following " + to_string(solutions.size()) + " words from this board:" << endl;
    for (string solution : solutions) {
        cout << solution << endl;
    }
}

/**
 * Finds all solutions given a board
 * @param board  The Boggle Board to Solve
 * @param row    The current row to solve from
 * @param col    The current column to solve from
 */

void solve() {
    set<doublePair> visited;

   for (int currentRow = 0; currentRow < 4; currentRow++) {
       for (int currentCol = 0; currentCol < 4; currentCol++) {
           solveBoard(currentRow , currentCol, visited, board[currentRow][currentCol]);
           visited.clear();
       }
   }
    printSolutions();
}


set<doublePair> powerSet(doublePair rowdoublePair, doublePair coldoublePair, int row, int col) {
    set<doublePair> result;

    int left = rowdoublePair.left;
    int right = rowdoublePair.right;
    int up = coldoublePair.left;
    int down = coldoublePair.right;

    if (left != -1) {
        if (up != -1) {
            doublePair left_up;
            left_up.left = left;
            left_up.right = up;
            result.insert(left_up);
        }
        doublePair left_only;
        left_only.left = left;
        left_only.right = col;
        result.insert(left_only);
        if (down != -1) {
            doublePair left_down;
            left_down.left = left;
            left_down.right = down;
            result.insert(left_down);
        }
    }
    if (right != -1) {
        if (up != -1) {
            doublePair right_up;
            right_up.left = right;
            right_up.right = up;
            result.insert(right_up);
        }
        doublePair right_only;
        right_only.left = right;
        right_only.right = col;
        result.insert(right_only);
        if (down != -1) {
            doublePair right_down;
            right_down.left = right;
            right_down.right = down;
            result.insert(right_down);
        }
    }
    if (up != -1) {
        doublePair up_only;
        up_only.left = row;
        up_only.right = up;
        result.insert(up_only);
    }
    if (down != -1) {
        doublePair down_only;
        down_only.left = row;
        down_only.right = down;
        result.insert(down_only);
    }

    return result;
}

set<doublePair> potentialMoves(int row, int col) {
    // Moving Left/Right
    doublePair rowdoublePair;
    if (row > 0) rowdoublePair.left = row - 1;
    else rowdoublePair.left = -1;

    if (row < 3) rowdoublePair.right = row + 1;
    else rowdoublePair.right = -1;

    // Moving Up/Down
    doublePair coldoublePair;
    if (col > 0) coldoublePair.left = col - 1;
    else coldoublePair.left = -1;

    if (col < 3) coldoublePair.right = col + 1;
    else coldoublePair.right = -1;

    return powerSet(rowdoublePair, coldoublePair, row, col);
}



