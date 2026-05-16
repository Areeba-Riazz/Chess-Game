// ============================================================
//  game.cpp  —  Game logic: menus, turns, choose, checkmate
//  Chess Game | PF Spring 2023
//  Authors: Areeba Riaz (i221244) | Arslan Javed (i220613)
// ============================================================

#include "game.h"
#include "board.h"
#include "pieces.h"

// ============================================================
//  start() — Entry point: get names, show main menu
// ============================================================
void start() {
    cout << "========================================" << endl;
    cout << "        WELCOME TO CHESS IN C++         " << endl;
    cout << "========================================" << endl;
    cout << "  White pieces = UPPERCASE (Player 1)"   << endl;
    cout << "  Black pieces = lowercase (Player 2)"   << endl;
    cout << "========================================"  << endl << endl;

    cout << "  Enter Player 1 name (White): ";
    cin  >> player1;
    cout << "  Enter Player 2 name (Black): ";
    cin  >> player2;
    cout << "\n  Good luck, " << player1 << " & " << player2 << "!\n" << endl;

    int choice = 0;
    bool running = true;

    while (running) {
        cout << "========================================"  << endl;
        cout << "               MAIN MENU               "  << endl;
        cout << "========================================"  << endl;
        cout << "  1. Your Next Move  (explore piece moves)" << endl;
        cout << "  2. Play Chess      (2-player game)"      << endl;
        cout << "  3. Exit"                                  << endl;
        cout << "----------------------------------------"  << endl;
        cout << "  Choose: ";
        check_int(choice);

        switch (choice) {
            case 1:
                explore_moves_mode();
                break;
            case 2:
                // Reset game state for a fresh game
                turn          = 0;
                game_over     = false;
                white_captured = 0;
                black_captured = 0;
                init_board(board);
                play_game();
                break;
            case 3:
                cout << "\n  Thanks for playing! Goodbye.\n" << endl;
                running = false;
                break;
            default:
                cout << "  Please enter 1, 2, or 3." << endl << endl;
        }
    }
}

// ============================================================
//  Mode 1: explore_moves_mode
//  PDF Part A — pick any piece, give a position, see valid moves
// ============================================================
void explore_moves_mode() {
    cout << "\n  ---- YOUR NEXT MOVE MODE ----" << endl;
    cout << "  Pick any piece, enter a position on an empty" << endl;
    cout << "  board, and see all valid moves highlighted." << endl << endl;

    bool exploring = true;
    while (exploring) {
        // Temporary empty board for demonstration
        char demo[ROWS][COLS];
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                demo[i][j] = '.';

        cout << "  Choose a piece to explore:" << endl;
        cout << "   1. King    2. Queen   3. Bishop" << endl;
        cout << "   4. Rook    5. Knight  6. Pawn" << endl;
        cout << "   7. Back to Main Menu" << endl;
        cout << "  Choice: ";
        int piece_choice = 0;
        check_int(piece_choice);

        if (piece_choice == 7) { exploring = false; break; }
        if (piece_choice < 1 || piece_choice > 6) {
            cout << "  Invalid choice." << endl; continue;
        }

        cout << "  Enter position (row 0-7): ";
        int r = 0; check_int(r);
        cout << "  Enter position (col 0-7): ";
        int c = 0; check_int(c);

        if (!is_valid_pos(r, c)) {
            cout << "  Position out of bounds (use 0-7)." << endl; continue;
        }

        // Place the selected piece symbol on the demo board
        // Using 0 (even) as current_turn so uppercase White pieces are used
        char symbols[] = {' ', 'K', 'Q', 'B', 'R', 'N', 'P'};
        char sym = symbols[piece_choice];
        demo[r][c] = sym;

        Position pos;
        pos.row = r; pos.col = c;

        // Show possibilities on the demo board
        switch (piece_choice) {
            case 1: king_possibilities(demo, pos, 0);   break;
            case 2: queen_possibilities(demo, pos, 0);  break;
            case 3: bishop_possibilities(demo, pos, 0); break;
            case 4: rook_possibilities(demo, pos, 0);   break;
            case 5: knight_possibilities(demo, pos, 0); break;
            case 6: pawn_possibilities(demo, pos, 0);   break;
        }

        cout << "\n  [" << sym << "] at [" << r << "," << c << "] — valid moves marked with 'x':" << endl;
        display_board(demo);

        cout << "  Explore another piece? (1=Yes / 2=No): ";
        int again = 0;
        check_int(again);
        if (again != 1) exploring = false;
    }
}

// ============================================================
//  declare_checkmate: announce winner and set game_over
// ============================================================
void declare_checkmate() {
    cout << "\n  ======================================" << endl;
    if (turn % 2 == 0) {
        // Even turn = White just moved = White captured Black king
        cout << "  CHECKMATE! " << player1 << " (White) WINS!" << endl;
    } else {
        cout << "  CHECKMATE! " << player2 << " (Black) WINS!" << endl;
    }
    cout << "  ======================================" << endl;
    show_score();
    game_over = true;
}

// ============================================================
//  handle_pair_piece: for pieces that come in pairs (R/B/N)
//  Asks player to pick Left or Right, finds that piece,
//  shows possibilities, then asks for a destination.
// ============================================================
void handle_pair_piece(char (*b)[COLS], char piece_white, char piece_black, const char* piece_name) {
    char piece = (turn % 2 == 0) ? piece_white : piece_black;
    char* current_player = (turn % 2 == 0) ? player1 : player2;

    // Count how many of this piece remain on the board
    int count = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (b[i][j] == piece) count++;

    if (count == 0) {
        cout << "  " << current_player << ", you have no " << piece_name << " left!" << endl;
        return;
    }

    Position pos;
    pos.row = -1; pos.col = -1;

    if (count == 1) {
        // Only one remains — find it automatically
        find_piece(b, piece, &pos);
    } else {
        // Two remain — ask Left (lower col) or Right (higher col)
        int side_choice = 0;
        do {
            cout << "  Choose your " << piece_name << ":" << endl;
            cout << "   1. Left " << piece_name << "   2. Right " << piece_name << endl;
            cout << "  Choice: ";
            check_int(side_choice);
            if (side_choice != 1 && side_choice != 2)
                cout << "  Please enter 1 or 2." << endl;
        } while (side_choice != 1 && side_choice != 2);

        int side = (side_choice == 1) ? 0 : 1; // 0=leftmost, 1=rightmost
        if (!find_piece_side(b, piece, side, &pos)) {
            cout << "  That " << piece_name << " is not available." << endl;
            return;
        }
    }

    // Show possibilities
    if (piece_white == 'B' || piece == 'b')
        bishop_possibilities(b, pos, turn);
    else if (piece_white == 'R' || piece == 'r')
        rook_possibilities(b, pos, turn);
    else
        knight_possibilities(b, pos, turn);

    display_board(b);
    reset_highlights(b);

    // Ask destination
    Position dest;
    bool moved = false;
    do {
        cout << "  Enter destination row (0-7): "; check_int(dest.row);
        cout << "  Enter destination col (0-7): "; check_int(dest.col);

        if (!is_valid_pos(dest.row, dest.col)) {
            cout << "  Out of bounds. Try again." << endl;
            continue;
        }

        if (piece_white == 'B')
            moved = bishop_move(b, pos, dest, turn);
        else if (piece_white == 'R')
            moved = rook_move(b, pos, dest, turn);
        else
            moved = knight_move(b, pos, dest, turn);

        if (!moved)
            cout << "  Invalid move for " << piece_name << ". Try again." << endl;
    } while (!moved);
}

// ============================================================
//  choose_piece: let the current player select a piece to move
//  Returns false if player chose to Exit/Resign
// ============================================================
bool choose_piece(char (*b)[COLS]) {
    char* current_player = (turn % 2 == 0) ? player1 : player2;
    char king_char   = (turn % 2 == 0) ? 'K' : 'k';
    char queen_char  = (turn % 2 == 0) ? 'Q' : 'q';
    char pawn_char   = (turn % 2 == 0) ? 'P' : 'p';

    int choice = 0;
    bool valid_piece = false;

    do {
        cout << "  " << current_player << ", choose a piece:" << endl;
        cout << "   1. King    2. Queen   3. Bishop" << endl;
        cout << "   4. Rook    5. Knight  6. Pawn   7. Resign" << endl;
        cout << "  Choice: ";
        check_int(choice);

        if (choice == 7) return false; // player resigns

        if (choice < 1 || choice > 7) {
            cout << "  Enter a number between 1 and 7." << endl;
            continue;
        }

        // ---- KING ----
        if (choice == 1) {
            Position pos;
            if (!find_piece(b, king_char, &pos)) {
                cout << "  You have no King?! Something went very wrong." << endl;
                continue;
            }
            king_possibilities(b, pos, turn);
            display_board(b);
            reset_highlights(b);

            Position dest;
            bool moved = false;
            do {
                cout << "  Enter destination row (0-7): "; check_int(dest.row);
                cout << "  Enter destination col (0-7): "; check_int(dest.col);
                if (!is_valid_pos(dest.row, dest.col)) { cout << "  Out of bounds.\n"; continue; }
                moved = king_move(b, pos, dest, turn);
                if (!moved) cout << "  Invalid move for King. Try again." << endl;
            } while (!moved);
            valid_piece = true;
        }

        // ---- QUEEN ----
        else if (choice == 2) {
            Position pos;
            if (!find_piece(b, queen_char, &pos)) {
                cout << "  You have no Queen left!" << endl; continue;
            }
            queen_possibilities(b, pos, turn);
            display_board(b);
            reset_highlights(b);

            Position dest;
            bool moved = false;
            do {
                cout << "  Enter destination row (0-7): "; check_int(dest.row);
                cout << "  Enter destination col (0-7): "; check_int(dest.col);
                if (!is_valid_pos(dest.row, dest.col)) { cout << "  Out of bounds.\n"; continue; }
                moved = queen_move(b, pos, dest, turn);
                if (!moved) cout << "  Invalid move for Queen. Try again." << endl;
            } while (!moved);
            valid_piece = true;
        }

        // ---- BISHOP ----
        else if (choice == 3) {
            handle_pair_piece(b, 'B', 'b', "Bishop");
            valid_piece = true;
        }

        // ---- ROOK ----
        else if (choice == 4) {
            handle_pair_piece(b, 'R', 'r', "Rook");
            valid_piece = true;
        }

        // ---- KNIGHT ----
        else if (choice == 5) {
            handle_pair_piece(b, 'N', 'n', "Knight");
            valid_piece = true;
        }

        // ---- PAWN ----
        else if (choice == 6) {
            // Let player choose which pawn (by column)
            cout << "  Enter the column (0-7) of the Pawn you want to move: ";
            int col = 0;
            check_int(col);
            if (!is_valid_pos(0, col)) { cout << "  Invalid column." << endl; continue; }

            // Find that pawn in the given column
            Position pos; pos.row = -1; pos.col = -1;
            for (int i = 0; i < ROWS; i++) {
                if (b[i][col] == pawn_char) { pos.row = i; pos.col = col; break; }
            }
            if (pos.row == -1) {
                cout << "  No " << (turn%2==0?"White":"Black") << " Pawn in column " << col << "." << endl;
                continue;
            }

            pawn_possibilities(b, pos, turn);
            display_board(b);
            reset_highlights(b);

            Position dest;
            bool moved = false;
            do {
                cout << "  Enter destination row (0-7): "; check_int(dest.row);
                cout << "  Enter destination col (0-7): "; check_int(dest.col);
                if (!is_valid_pos(dest.row, dest.col)) { cout << "  Out of bounds.\n"; continue; }
                moved = pawn_move(b, pos, dest, turn);
                if (!moved) cout << "  Invalid Pawn move. Try again." << endl;
            } while (!moved);
            valid_piece = true;
        }

    } while (!valid_piece);

    return true;
}

// ============================================================
//  play_game: the main 2-player game loop
// ============================================================
void play_game() {
    cout << "\n  ---- CHESS GAME STARTED ----" << endl;
    cout << "  " << player1 << " plays White (UPPERCASE)" << endl;
    cout << "  " << player2 << " plays Black (lowercase)" << endl << endl;

    display_board(board);

    while (!game_over) {
        char* current_player = (turn % 2 == 0) ? player1 : player2;
        char* color          = (turn % 2 == 0) ? (char*)"White" : (char*)"Black";

        cout << "  ======================================" << endl;
        cout << "  " << current_player << "'s Turn (" << color << ")" << endl;
        cout << "  ======================================" << endl;

        bool continued = choose_piece(board);

        if (!continued) {
            // Player resigned
            char* winner = (turn % 2 == 0) ? player2 : player1;
            cout << "\n  " << current_player << " resigned!" << endl;
            cout << "  " << winner << " WINS!" << endl;
            show_score();
            game_over = true;
            break;
        }

        if (game_over) {
            // King was captured during this move
            declare_checkmate();
            break;
        }

        display_board(board);
        show_score();
        turn++;
    }

    cout << "\n  Game over. Returning to main menu..." << endl << endl;
}
