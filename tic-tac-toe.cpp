#include <iostream>
#include <limits.h>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

void displayBoard(char board[3][3]) {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

int evaluate(char board[3][3]) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    // No winner
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If computer has won
    if (score == 10)
        return score - depth;

    // If player has won
    if (score == -10)
        return score + depth;

    // No more moves and no winner
    if (!isMovesLeft(board))
        return 0;

    // If this is the computer's move
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    // If this is the player's move
    else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(char board[3][3]) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove.first = i;
                    bestMove.second = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

bool checkWin(char board[3][3], char mark) {
    return evaluate(board) == (mark == COMPUTER ? 10 : -10);
}

bool isDraw(char board[3][3]) {
    return !isMovesLeft(board) && evaluate(board) == 0;
}

void playerMove(char board[3][3]) {
    int row, col;
    do {
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
    } while (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != EMPTY);

    board[row - 1][col - 1] = PLAYER;
}

void computerMove(char board[3][3]) {
    pair<int, int> bestMove = findBestMove(board);
    board[bestMove.first][bestMove.second] = COMPUTER;
}

int main() {
    char board[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    cout << "Welcome to Tic-Tac-Toe! You are 'X' and the computer is 'O'.\n";
    displayBoard(board);

    while (true) {
        playerMove(board);
        displayBoard(board);

        if (checkWin(board, PLAYER)) {
            cout << "Congratulations! You won!\n";
            break;
        }
        if (isDraw(board)) {
            cout << "It's a draw!\n";
            break;
        }

        computerMove(board);
        displayBoard(board);

        if (checkWin(board, COMPUTER)) {
            cout << "The computer won! Better luck next time.\n";
            break;
        }
        if (isDraw(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
    cout<<"Author:karthikkrazy"<<endl<<"github.com/krazykarthik2";
    return 0;
}
