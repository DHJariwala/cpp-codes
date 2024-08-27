// Header files
#include <iostream>
using namespace std;

// Function declaration
void printBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool checkDraw(char board[3][3]);

int main() {
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    int choice;
    bool gameWon = false, gameDraw = false;

    while (!gameWon && !gameDraw) {
        printBoard(board);

        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> choice;

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Add X or O if not occupied
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
        } 
        else {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        gameWon = checkWin(board, currentPlayer);

        // If game not won, check for draw
        if (!gameWon) {
            gameDraw = checkDraw(board);
            if (currentPlayer == 'X') {
                currentPlayer = 'O';
            } 
            else {
                currentPlayer = 'X';
            }
        }
    }

    printBoard(board);

    if (gameWon) {
        cout << "Player " << currentPlayer << " wins!\n";
    } 
    else {
        cout << "It's a draw!\n";
    }

    return 0;
}

void printBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|"; // After 0 and 1 index in row
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n"; // After 0 and 1 index in column
    }
    cout << "\n";
}

bool checkWin(char board[3][3], char player) {
    // Check horizontal and vertical
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool checkDraw(char board[3][3]) {
    // If every place is filled with either X or O, then it's draw
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}