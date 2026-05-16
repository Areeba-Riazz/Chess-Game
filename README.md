# ♟️ Console Chess

A **console-based two-player Chess game** written in C++ as a Programming Fundamentals (Spring 2023) course project. The game runs entirely in the terminal and implements core chess piece movement rules on a full 8×8 board.

> **Authors:** Areeba Riaz (i221244)
> **Course:** Programming Fundamentals — Spring 2023

---

## Features

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

## Concepts Used

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

## How to Play

### Compile
```bash
cd src
g++ main.cpp board.cpp pieces.cpp game.cpp -o chess
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

## Project Structure

```
📦 Chess-Game/
 ┣ 📂 src/                   ← Source code
 ┃  ┣ 📄 main.cpp        ← Entry point — defines globals, calls start()
 ┃  ┣ 📄 globals.h       ← Shared constants, Position struct, extern vars
 ┃  ┣ 📄 board.h/.cpp    ← Board display, initialization, input validation
 ┃  ┣ 📄 pieces.h/.cpp   ← All 6 pieces: movement + possibilities (pointers)
 ┃  ┗ 📄 game.h/.cpp     ← Game loop, menus, turn logic, checkmate, resign
 ┣ 📂 docs/                  ← Project documentation
 ┃  ┗ 📄 Final Project 2023.pdf
 ┣ 📄 .gitignore
 ┗ 📄 README.md
```

---

## ⚠️ Known Limitations

- No "check" warning when King is threatened (only detects when King is actually captured)
- Special moves not implemented: castling, en passant, pawn promotion
- No AI opponent — two human players only

---

*Developed for Programming Fundamentals (CL-1002), FAST-NUCES Islamabad — Project Chess Game*
