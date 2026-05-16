# ♟️ Console Chess — C++

A **console-based two-player Chess game** written in C++ as a Programming Fundamentals (Spring 2023) course project. The game runs entirely in the terminal and implements core chess piece movement rules on a full 8×8 board.

> **Authors:** Areeba Riaz (i221244) · Arslan Javed (i220613)  
> **Course:** Programming Fundamentals — Spring 2023

---

## 🎮 Features

- Full 8×8 chess board rendered in the console
- Two-player alternating turn system
- **6 piece types** with correct movement rules:
  - ♔ **King** — moves one square in any direction
  - ♕ **Queen** — moves any number of squares diagonally or straight
  - ♗ **Bishop** — moves any number of squares diagonally
  - ♖ **Rook** — moves any number of squares in a straight line
  - ♘ **Knight** — moves in an L-shape (2+1 squares)
  - ♙ **Pawn** — moves forward 1 (or 2 from start), captures diagonally
- **Two game modes**: Explore Moves (single-player) and Play Chess (2-player)
- **Valid move highlighting** — shows all possible destinations before you choose
- **Proper piece capture** with live score tracking
- **Checkmate detection** — game ends when the King is captured
- **Resign option** — any player can resign on their turn
- Input validation (handles non-integer and out-of-bounds input)

---

## 🧠 Concepts Used

This project was built using **Programming Fundamentals** concepts only:

- **2D Arrays** — `char board[8][8]` for the chess board
- **Pointers** — board passed as `char (*b)[8]` to all functions; `Position*` used to return piece locations
- **Structs** — `Position { int row; int col; }` for clean position handling
- **Functions** — fully modular; each piece has its own move + possibilities function
- **Loops** — `for`/`while` for board scanning, sliding pieces, input retry
- **Conditionals** — `if/else`, `switch` for piece selection and game flow
- **Multi-file organization** — `globals.h`, `board`, `pieces`, `game`, `main`
- **No OOP** — no classes, no templates, no STL containers

---

## 🕹️ How to Play

### Compile (Multi-file version)
```bash
g++ main.cpp board.cpp pieces.cpp game.cpp -o chess
```

### Compile (Original single-file version)
```bash
g++ "Areeba-Riaz_i221244_Arslan-Javed_i220613_D_Project.cpp" -o chess_original
```

### Run
```bash
./chess
```

### Board Legend
| Symbol | Piece | Player |
|--------|-------|--------|
| `K` | King | White (Player 1) |
| `Q` | Queen | White |
| `B` | Bishop | White |
| `R` | Rook | White |
| `N` | Knight | White |
| `k` | King | Black (Player 2) |
| `q` | Queen | Black |
| `b` | Bishop | Black |
| `r` | Rook | Black |
| `n` | Knight | Black |
| `x` | Valid move | — |
| `.` | Empty square | — |

### Controls
1. Enter player names when prompted
2. On your turn, choose a piece by number (1–6)
3. If you have two of the same piece (e.g. two Rooks), choose Left or Right
4. The board displays your valid moves marked with `x`
5. Enter the row and column of your destination

---

## 📁 Project Structure

```
📦 console-chess-cpp
 ┣ 📄 main.cpp        ← Entry point — defines globals, calls start()
 ┣ 📄 globals.h       ← Shared constants, Position struct, extern declarations
 ┣ 📄 board.h / .cpp  ← Board display, initialization, input validation
 ┣ 📄 pieces.h / .cpp ← All 6 piece movement + possibility functions (uses pointers)
 ┣ 📄 game.h / .cpp   ← Game loop, menus, turn logic, checkmate, resign
 ┣ 📄 Areeba-Riaz_i221244_Arslan-Javed_i220613_D_Project.cpp  ← Original single-file version
 ┣ 📄 Final Project 2023.pdf                                   ← Project specification
 ┗ 📄 README.md
```

---

## ⚠️ Known Limitations

- No "check" warning when King is threatened (only detects when King is actually captured)
- Special moves not implemented: castling, en passant, pawn promotion
- No AI opponent — two human players only

---

## ✅ Improvements Made (vs. Original)

- [x] Added Pawns with full movement (forward 1/2, diagonal capture)
- [x] Implemented proper checkmate — game ends and winner is declared
- [x] Added pointers throughout (board as `char (*b)[8]`, `Position*` for piece finding)
- [x] Added `Position` struct for clean coordinate handling
- [x] Refactored into 5 separate files (`globals`, `board`, `pieces`, `game`, `main`)
- [x] Added live capture score tracking
- [x] Added game mode menu (Explore Moves + Play Game)
- [x] Added resign option
- [x] Fixed all copy-paste bugs from original (knight checking bishop squares, etc.)
- [x] Replaced all `goto` statements with `do-while` loops
- [x] Replaced recursion-based retries with `while` loops

---

## 📜 License

This project was submitted as an academic assignment. Feel free to reference it for learning purposes.
