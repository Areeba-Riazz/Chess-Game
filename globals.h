// ============================================================
//  globals.h  —  Shared constants, struct, and extern vars
//  Chess Game | PF Spring 2023
//  Authors: Areeba Riaz (i221244) | Arslan Javed (i220613)
// ============================================================

#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <climits>
#include <limits>
using namespace std;

// Board size constants
const int ROWS = 8;
const int COLS = 8;

// -------------------------------------------------------
// Position struct — represents a row/column on the board
// (Demonstrates struct — PF concept)
// -------------------------------------------------------
struct Position {
    int row;
    int col;
};

// -------------------------------------------------------
// Shared global variables — defined once in main.cpp,
// declared here so all files can access them via extern
// -------------------------------------------------------
extern char board[ROWS][COLS];   // The 8x8 chess board
extern char player1[50];         // Player 1 name (White)
extern char player2[50];         // Player 2 name (Black)
extern int  turn;                // Even = P1 (White), Odd = P2 (Black)
extern bool game_over;           // Set to true when a king is captured
extern int  white_captured;      // Pieces captured by White
extern int  black_captured;      // Pieces captured by Black

// -------------------------------------------------------
// Board Legend:
//   Uppercase = White (Player 1): K Q B R N P
//   Lowercase = Black (Player 2): k q b r n p
//   '.' = empty square
//   'x' = valid move highlight
// -------------------------------------------------------

#endif
