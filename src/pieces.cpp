// ============================================================
//  pieces.cpp  —  Piece movement logic for all chess pieces
//  Chess Game | PF Spring 2023
//  Authors: Areeba Riaz (i221244) | Arslan Javed (i220613)
//
//  PF Concepts demonstrated:
//   - Pointers: board passed as char (*b)[COLS], Position*
//   - 2D Arrays: board[ROWS][COLS]
//   - Structs: Position
//   - Functions, Loops, Conditionals
// ============================================================

#include "pieces.h"
#include "board.h"

// ============================================================
//  UTILITY FUNCTIONS
// ============================================================

// -------------------------------------------------------
// find_piece: scan the board and return the position of a
// specific piece character using a pointer to store result.
// Demonstrates pointer usage (PF requirement).
// -------------------------------------------------------
bool find_piece(char (*b)[COLS], char piece, Position *result) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (b[i][j] == piece) {
                result->row = i;   // write through pointer
                result->col = j;
                return true;
            }
        }
    }
    return false; // piece has been captured / not on board
}

// -------------------------------------------------------
// find_piece_side: for pieces that come in pairs (R/r, N/n, B/b)
// side 0 = leftmost instance (lowest column index)
// side 1 = rightmost instance (highest column index)
// -------------------------------------------------------
bool find_piece_side(char (*b)[COLS], char piece, int side, Position *result) {
    bool found = false;
    result->row = -1;
    result->col = (side == 0) ? COLS : -1; // sentinel values

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (b[i][j] == piece) {
                if (side == 0 && j < result->col) {
                    result->row = i; result->col = j; found = true;
                } else if (side == 1 && j > result->col) {
                    result->row = i; result->col = j; found = true;
                }
            }
        }
    }
    return found;
}

// -------------------------------------------------------
// is_own_piece: true if the square holds a friendly piece
// White (Player 1, even turns) = uppercase letters
// Black (Player 2, odd turns)  = lowercase letters
// -------------------------------------------------------
bool is_own_piece(char square, int current_turn) {
    if (current_turn % 2 == 0)
        return (square >= 'A' && square <= 'Z');
    else
        return (square >= 'a' && square <= 'z');
}

// -------------------------------------------------------
// is_enemy_piece: true if the square holds an enemy piece
// -------------------------------------------------------
bool is_enemy_piece(char square, int current_turn) {
    if (square == '.' || square == 'x') return false;
    if (current_turn % 2 == 0)
        return (square >= 'a' && square <= 'z');
    else
        return (square >= 'A' && square <= 'Z');
}

// -------------------------------------------------------
// is_king_captured: check if captured piece is enemy king
// -------------------------------------------------------
bool is_king_captured(char captured, int attacker_turn) {
    if (attacker_turn % 2 == 0) return (captured == 'k');
    else                         return (captured == 'K');
}

// ============================================================
//  POSSIBILITIES — mark reachable squares with 'x'
// ============================================================

// -------------------------------------------------------
// King: moves 1 square in any of 8 directions
// -------------------------------------------------------
void king_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = pos.row + dr;
            int nc = pos.col + dc;
            if (is_valid_pos(nr, nc) && !is_own_piece(b[nr][nc], current_turn)) {
                if (b[nr][nc] == '.')
                    b[nr][nc] = 'x';
                // enemy pieces keep their letter so player can see what they're capturing
            }
        }
    }
}

// -------------------------------------------------------
// Queen: combines rook (straight) + bishop (diagonal) moves
// Slides until hitting a piece or board edge
// -------------------------------------------------------
void queen_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    // All 8 directions: [row_step][col_step]
    int dir[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},    // straight
        {-1,-1}, {-1, 1}, {1, -1}, {1, 1}     // diagonal
    };
    for (int d = 0; d < 8; d++) {
        int nr = pos.row + dir[d][0];
        int nc = pos.col + dir[d][1];
        while (is_valid_pos(nr, nc)) {
            if (b[nr][nc] == '.') {
                b[nr][nc] = 'x';
            } else if (is_enemy_piece(b[nr][nc], current_turn)) {
                break; // can capture but cannot pass through
            } else {
                break; // blocked by own piece
            }
            nr += dir[d][0];
            nc += dir[d][1];
        }
    }
}

// -------------------------------------------------------
// Rook: slides in 4 straight directions (no diagonals)
// -------------------------------------------------------
void rook_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (int d = 0; d < 4; d++) {
        int nr = pos.row + dir[d][0];
        int nc = pos.col + dir[d][1];
        while (is_valid_pos(nr, nc)) {
            if (b[nr][nc] == '.') {
                b[nr][nc] = 'x';
            } else if (is_enemy_piece(b[nr][nc], current_turn)) {
                break;
            } else {
                break;
            }
            nr += dir[d][0];
            nc += dir[d][1];
        }
    }
}

// -------------------------------------------------------
// Bishop: slides in 4 diagonal directions only
// -------------------------------------------------------
void bishop_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    int dir[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
    for (int d = 0; d < 4; d++) {
        int nr = pos.row + dir[d][0];
        int nc = pos.col + dir[d][1];
        while (is_valid_pos(nr, nc)) {
            if (b[nr][nc] == '.') {
                b[nr][nc] = 'x';
            } else if (is_enemy_piece(b[nr][nc], current_turn)) {
                break;
            } else {
                break;
            }
            nr += dir[d][0];
            nc += dir[d][1];
        }
    }
}

// -------------------------------------------------------
// Knight: L-shape moves (2+1). Can jump over pieces.
// 8 possible destination squares.
// -------------------------------------------------------
void knight_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    int moves[8][2] = {
        {-2,-1},{-2,1},{2,-1},{2,1},
        {-1,-2},{-1,2},{1,-2},{1,2}
    };
    for (int i = 0; i < 8; i++) {
        int nr = pos.row + moves[i][0];
        int nc = pos.col + moves[i][1];
        if (is_valid_pos(nr, nc) && !is_own_piece(b[nr][nc], current_turn)) {
            if (b[nr][nc] == '.')
                b[nr][nc] = 'x';
        }
    }
}

// -------------------------------------------------------
// Pawn:
//   White (P): moves UP  (row decreases). Starts at row 6.
//   Black (p): moves DOWN (row increases). Starts at row 1.
//   Forward 1 always; forward 2 from starting row if clear.
//   Captures diagonally forward only.
// -------------------------------------------------------
void pawn_possibilities(char (*b)[COLS], Position pos, int current_turn) {
    if (current_turn % 2 == 0) {
        // White pawn moves up
        if (is_valid_pos(pos.row-1, pos.col) && b[pos.row-1][pos.col] == '.') {
            b[pos.row-1][pos.col] = 'x';
            // Two squares from starting row (only if one-square path is clear)
            if (pos.row == 6 && b[pos.row-2][pos.col] == '.')
                b[pos.row-2][pos.col] = 'x';
        }
        // Diagonal capture (left)
        if (is_valid_pos(pos.row-1, pos.col-1) && is_enemy_piece(b[pos.row-1][pos.col-1], current_turn))
            b[pos.row-1][pos.col-1] = 'x';
        // Diagonal capture (right)
        if (is_valid_pos(pos.row-1, pos.col+1) && is_enemy_piece(b[pos.row-1][pos.col+1], current_turn))
            b[pos.row-1][pos.col+1] = 'x';
    } else {
        // Black pawn moves down
        if (is_valid_pos(pos.row+1, pos.col) && b[pos.row+1][pos.col] == '.') {
            b[pos.row+1][pos.col] = 'x';
            if (pos.row == 1 && b[pos.row+2][pos.col] == '.')
                b[pos.row+2][pos.col] = 'x';
        }
        if (is_valid_pos(pos.row+1, pos.col-1) && is_enemy_piece(b[pos.row+1][pos.col-1], current_turn))
            b[pos.row+1][pos.col-1] = 'x';
        if (is_valid_pos(pos.row+1, pos.col+1) && is_enemy_piece(b[pos.row+1][pos.col+1], current_turn))
            b[pos.row+1][pos.col+1] = 'x';
    }
}

// ============================================================
//  MOVEMENT FUNCTIONS — validate then execute a move
//  Each returns true on success, false on invalid move.
//  Captures increment the score counter; king capture sets game_over.
// ============================================================

// Helper: execute the move and handle capture scoring
static void execute_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    char captured = b[to.row][to.col];

    // Update capture score
    if (is_enemy_piece(captured, current_turn)) {
        if (current_turn % 2 == 0) white_captured++;
        else                        black_captured++;
    }

    // Check if king was captured → trigger game over
    if (is_king_captured(captured, current_turn))
        game_over = true;

    // Move piece
    b[to.row][to.col] = b[from.row][from.col];
    b[from.row][from.col] = '.';
}

// -------------------------------------------------------
// king_move
// -------------------------------------------------------
bool king_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (from.row == to.row && from.col == to.col) return false;
    if (abs(from.row - to.row) > 1 || abs(from.col - to.col) > 1) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    execute_move(b, from, to, current_turn);
    return true;
}

// -------------------------------------------------------
// queen_move
// -------------------------------------------------------
bool queen_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (from.row == to.row && from.col == to.col) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    int dr = to.row - from.row;
    int dc = to.col - from.col;
    bool straight = (dr == 0 || dc == 0);
    bool diagonal = (abs(dr) == abs(dc));
    if (!straight && !diagonal) return false;

    // Check path is clear
    int step_r = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int step_c = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);
    int cr = from.row + step_r, cc = from.col + step_c;
    while (cr != to.row || cc != to.col) {
        if (b[cr][cc] != '.') return false;
        cr += step_r; cc += step_c;
    }

    execute_move(b, from, to, current_turn);
    return true;
}

// -------------------------------------------------------
// rook_move
// -------------------------------------------------------
bool rook_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (from.row == to.row && from.col == to.col) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    int dr = to.row - from.row;
    int dc = to.col - from.col;
    if (dr != 0 && dc != 0) return false; // must be straight line

    int step_r = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int step_c = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);
    int cr = from.row + step_r, cc = from.col + step_c;
    while (cr != to.row || cc != to.col) {
        if (b[cr][cc] != '.') return false;
        cr += step_r; cc += step_c;
    }

    execute_move(b, from, to, current_turn);
    return true;
}

// -------------------------------------------------------
// bishop_move
// -------------------------------------------------------
bool bishop_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (from.row == to.row && from.col == to.col) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    int dr = to.row - from.row;
    int dc = to.col - from.col;
    if (abs(dr) != abs(dc)) return false; // must be diagonal

    int step_r = (dr > 0) ? 1 : -1;
    int step_c = (dc > 0) ? 1 : -1;
    int cr = from.row + step_r, cc = from.col + step_c;
    while (cr != to.row || cc != to.col) {
        if (b[cr][cc] != '.') return false;
        cr += step_r; cc += step_c;
    }

    execute_move(b, from, to, current_turn);
    return true;
}

// -------------------------------------------------------
// knight_move (can jump — no path checking needed)
// -------------------------------------------------------
bool knight_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    int dr = abs(to.row - from.row);
    int dc = abs(to.col - from.col);
    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) return false;

    execute_move(b, from, to, current_turn);
    return true;
}

// -------------------------------------------------------
// pawn_move
// White moves up (row-1), Black moves down (row+1)
// Captures only diagonally forward
// -------------------------------------------------------
bool pawn_move(char (*b)[COLS], Position from, Position to, int current_turn) {
    if (!is_valid_pos(to.row, to.col)) return false;
    if (is_own_piece(b[to.row][to.col], current_turn)) return false;

    int dr = to.row - from.row;
    int dc = to.col - from.col;

    if (current_turn % 2 == 0) {
        // White: must move up (negative dr)
        if (dr >= 0) return false;
        if (dc == 0) {
            // Forward move: must be empty
            if (b[to.row][to.col] != '.') return false;
            if (dr == -1) { execute_move(b, from, to, current_turn); return true; }
            if (dr == -2 && from.row == 6 && b[from.row-1][from.col] == '.') {
                execute_move(b, from, to, current_turn); return true;
            }
        } else if (abs(dc) == 1 && dr == -1) {
            // Diagonal capture
            if (!is_enemy_piece(b[to.row][to.col], current_turn)) return false;
            execute_move(b, from, to, current_turn); return true;
        }
    } else {
        // Black: must move down (positive dr)
        if (dr <= 0) return false;
        if (dc == 0) {
            if (b[to.row][to.col] != '.') return false;
            if (dr == 1) { execute_move(b, from, to, current_turn); return true; }
            if (dr == 2 && from.row == 1 && b[from.row+1][from.col] == '.') {
                execute_move(b, from, to, current_turn); return true;
            }
        } else if (abs(dc) == 1 && dr == 1) {
            if (!is_enemy_piece(b[to.row][to.col], current_turn)) return false;
            execute_move(b, from, to, current_turn); return true;
        }
    }
    return false;
}
