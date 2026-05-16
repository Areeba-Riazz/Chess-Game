// ============================================================
//  board.cpp  —  Board display, initialization, utility funcs
//  Chess Game | PF Spring 2023
//  Authors: Areeba Riaz (i221244) | Arslan Javed (i220613)
// ============================================================

#include "board.h"

// -------------------------------------------------------
// init_board: place all pieces in their starting positions
// Parameter b is a pointer to the 2D board array
// (Demonstrates pointer usage — PF requirement)
// -------------------------------------------------------
void init_board(char (*b)[COLS]) {
    // Clear the entire board first
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            b[i][j] = '.';

    // --- White pieces (Player 1) — Row 7 ---
    b[7][0] = 'R';  b[7][1] = 'N';  b[7][2] = 'B';
    b[7][3] = 'Q';  b[7][4] = 'K';
    b[7][5] = 'B';  b[7][6] = 'N';  b[7][7] = 'R';

    // White pawns — Row 6
    for (int j = 0; j < COLS; j++)
        b[6][j] = 'P';

    // --- Black pieces (Player 2) — Row 0 ---
    b[0][0] = 'r';  b[0][1] = 'n';  b[0][2] = 'b';
    b[0][3] = 'q';  b[0][4] = 'k';
    b[0][5] = 'b';  b[0][6] = 'n';  b[0][7] = 'r';

    // Black pawns — Row 1
    for (int j = 0; j < COLS; j++)
        b[1][j] = 'p';
}

// -------------------------------------------------------
// display_board: print the board with row/col labels
// -------------------------------------------------------
void display_board(char (*b)[COLS]) {
    cout << "\n       0   1   2   3   4   5   6   7" << endl;
    cout << "     +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "  " << i << "  |";
        for (int j = 0; j < COLS; j++) {
            cout << " " << b[i][j] << " |";
        }
        cout << endl;
        cout << "     +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl;
    cout << "  [WHITE = UPPERCASE: K Q B R N P]" << endl;
    cout << "  [BLACK = lowercase: k q b r n p]" << endl;
    cout << "  [x = valid move destination]" << endl << endl;
}

// -------------------------------------------------------
// reset_highlights: replace all 'x' markers with '.'
// -------------------------------------------------------
void reset_highlights(char (*b)[COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (b[i][j] == 'x')
                b[i][j] = '.';
}

// -------------------------------------------------------
// is_valid_pos: boundary check for row and column
// -------------------------------------------------------
bool is_valid_pos(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

// -------------------------------------------------------
// check_int: keeps asking until a valid integer is entered
// -------------------------------------------------------
void check_int(int &num) {
    while (true) {
        if (cin >> num)
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Please enter a number: ";
    }
}

// -------------------------------------------------------
// show_score: display how many pieces each player captured
// -------------------------------------------------------
void show_score() {
    cout << "  ----------------------------------------" << endl;
    cout << "  Score: " << player1 << " (White) captured " << white_captured << " piece(s)" << endl;
    cout << "         " << player2 << " (Black) captured " << black_captured << " piece(s)" << endl;
    cout << "  ----------------------------------------" << endl << endl;
}
