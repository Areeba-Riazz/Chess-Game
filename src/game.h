// ============================================================
//  game.h  —  Game logic: menus, turns, choose, checkmate
// ============================================================

#ifndef GAME_H
#define GAME_H

#include "globals.h"

// Main entry point — sets up game, gets player names, runs menu
void start();

// Mode 1: "Your Next Move" — standalone piece move explorer (PDF Part A)
void explore_moves_mode();

// Mode 2: "Save the King" — full 2-player chess game (PDF Part B)
void play_game();

// Handle one player's full turn (choose piece → show moves → move)
void player_turn(char (*b)[COLS]);

// Let player choose which piece to move; returns false if player chose Exit
bool choose_piece(char (*b)[COLS]);

// Handle selecting and moving a pair piece (rook/bishop/knight)
// piece_white = white version char, piece_black = black version char
// piece_name = display name (e.g. "Rook")
void handle_pair_piece(char (*b)[COLS], char piece_white, char piece_black, const char* piece_name);

// Announce winner and end the game
void declare_checkmate();

#endif
