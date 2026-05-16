// ============================================================
//  board.h  —  Board display, initialization, utility funcs
// ============================================================

#ifndef BOARD_H
#define BOARD_H

#include "globals.h"

// Set up the board with all standard starting piece positions
void init_board(char (*b)[COLS]);

// Print the current board state to the console
void display_board(char (*b)[COLS]);

// Reset 'x' (highlighted moves) back to '.'
void reset_highlights(char (*b)[COLS]);

// Returns true if (row, col) is inside the 8x8 grid
bool is_valid_pos(int row, int col);

// Safe integer input — loops until user enters a valid integer
void check_int(int &num);

// Print the captured pieces count for both players
void show_score();

#endif
