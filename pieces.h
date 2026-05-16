// ============================================================
//  pieces.h  —  Piece movement and possibilities declarations
// ============================================================

#ifndef PIECES_H
#define PIECES_H

#include "globals.h"

// -------------------------------------------------------
// Utility — piece identity checks
// -------------------------------------------------------

// Find a piece on the board; stores result in a Position pointer
// Returns true if found, false if piece is not on board (captured)
bool find_piece(char (*b)[COLS], char piece, Position *result);

// Find the leftmost OR rightmost instance of a piece (for rook/bishop/knight)
// side: 0 = leftmost (lowest col), 1 = rightmost (highest col)
bool find_piece_side(char (*b)[COLS], char piece, int side, Position *result);

// Returns true if the square is occupied by a friendly piece
bool is_own_piece(char square, int current_turn);

// Returns true if the square is occupied by an enemy piece
bool is_enemy_piece(char square, int current_turn);

// Returns true if the captured piece is the opponent's king
bool is_king_captured(char captured, int attacker_turn);

// -------------------------------------------------------
// Possibilities — mark valid moves with 'x' on the board
// -------------------------------------------------------
void king_possibilities(char (*b)[COLS], Position pos, int current_turn);
void queen_possibilities(char (*b)[COLS], Position pos, int current_turn);
void rook_possibilities(char (*b)[COLS], Position pos, int current_turn);
void bishop_possibilities(char (*b)[COLS], Position pos, int current_turn);
void knight_possibilities(char (*b)[COLS], Position pos, int current_turn);
void pawn_possibilities(char (*b)[COLS], Position pos, int current_turn);

// -------------------------------------------------------
// Movement — validate and execute a move
// Returns true if move was legal and performed
// Sets game_over = true if a king is captured
// -------------------------------------------------------
bool king_move(char (*b)[COLS], Position from, Position to, int current_turn);
bool queen_move(char (*b)[COLS], Position from, Position to, int current_turn);
bool rook_move(char (*b)[COLS], Position from, Position to, int current_turn);
bool bishop_move(char (*b)[COLS], Position from, Position to, int current_turn);
bool knight_move(char (*b)[COLS], Position from, Position to, int current_turn);
bool pawn_move(char (*b)[COLS], Position from, Position to, int current_turn);

#endif
