// ============================================================
//  main.cpp  —  Entry point and global variable definitions
//  Chess Game | PF Spring 2023
//  Authors: Areeba Riaz (i221244) | Arslan Javed (i220613)
//
//  Compile:
//    g++ main.cpp board.cpp pieces.cpp game.cpp -o chess
//  Run:
//    ./chess
// ============================================================

#include "game.h"
#include "board.h"

// -------------------------------------------------------
// Global variable definitions (declared extern in globals.h)
// All files share these via the extern declarations.
// -------------------------------------------------------
char board[ROWS][COLS];
char player1[50];
char player2[50];
int  turn          = 0;
bool game_over     = false;
int  white_captured = 0;
int  black_captured = 0;

// -------------------------------------------------------
// main: only starts the game (matches PDF deliverable spec)
// -------------------------------------------------------
int main() {
    start();
    return 0;
}
