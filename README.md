# ♟️ Console Chess — C++

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=c%2B%2B)
![Paradigm](https://img.shields.io/badge/Paradigm-Procedural-green?style=flat-square)
![Concepts](https://img.shields.io/badge/Concepts-Pointers%20%7C%20Arrays%20%7C%20Structs%20%7C%20Functions-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)

A fully functional **two-player Chess game** built in C++ using only **Programming Fundamentals** concepts — no OOP, no STL, no templates. Runs entirely in the console with an 8×8 board, all major piece types, valid move highlighting, checkmate detection, and a clean multi-file architecture.

> 👩‍💻 **Author:** Areeba Riaz  
> 🏫 **University:** FAST-NUCES, Islamabad  
> 📚 **Course:** Programming Fundamentals (CL-1002) — Spring 2023

---

## 🎮 Game Preview

```
       0   1   2   3   4   5   6   7
     +---+---+---+---+---+---+---+---+
  0  | r | n | b | q | k | b | n | r |
     +---+---+---+---+---+---+---+---+
  1  | p | p | p | p | p | p | p | p |
     +---+---+---+---+---+---+---+---+
  2  | . | . | . | . | . | . | . | . |
     +---+---+---+---+---+---+---+---+
  3  | . | . | . | . | . | . | . | . |
     +---+---+---+---+---+---+---+---+
  4  | . | . | . | . | . | . | . | . |
     +---+---+---+---+---+---+---+---+
  5  | . | . | . | . | . | . | . | . |
     +---+---+---+---+---+---+---+---+
  6  | P | P | P | P | P | P | P | P |
     +---+---+---+---+---+---+---+---+
  7  | R | N | B | Q | K | B | N | R |
     +---+---+---+---+---+---+---+---+

  [WHITE = UPPERCASE: K Q B R N P]
  [BLACK = lowercase: k q b r n p]
  [x = valid move destination]
```

---

## ✨ Features

| Feature | Description |
|---|---|
| 🏁 **8×8 Board** | Full chess board rendered in the terminal with row/column labels |
| ♟️ **All 6 Piece Types** | King, Queen, Bishop, Rook, Knight, and Pawn — all with correct rules |
| 🔦 **Move Highlighting** | Valid destinations are marked with `x` before you enter a move |
| ⚔️ **Piece Capture** | Captures enemy pieces; live score shown after each turn |
| 👑 **Checkmate Detection** | Game ends immediately when a King is captured; winner is declared |
| 🏳️ **Resign Option** | Either player can resign on their turn |
| 🔢 **Input Validation** | Handles non-integer input and out-of-bounds positions gracefully |
| 🎯 **Two Game Modes** | Explore Moves (study piece movement) + Play Chess (full 2-player game) |

### Piece Movement Rules

| Piece | Symbol | Movement |
|---|---|---|
| King | `K` / `k` | 1 square in any direction |
| Queen | `Q` / `q` | Any number of squares — straight or diagonal |
| Bishop | `B` / `b` | Any number of squares diagonally |
| Rook | `R` / `r` | Any number of squares in a straight line |
| Knight | `N` / `n` | L-shape: 2 squares + 1 square (can jump over pieces) |
| Pawn | `P` / `p` | 1 forward (2 from start); captures diagonally |

---

## 🧠 C++ Concepts Demonstrated

This project was intentionally built using **Procedural / Programming Fundamentals concepts only**:

| Concept | How It's Used |
|---|---|
| **2D Arrays** | `char board[8][8]` stores the entire game state |
| **Pointers** | Board passed as `char (*b)[8]` to every function; `Position*` used to return piece locations from scanning functions |
| **Structs** | `struct Position { int row; int col; }` used throughout for clean coordinate handling |
| **Functions** | Fully modular — each piece has its own `_move()` and `_possibilities()` function |
| **Loops** | `for`/`while` for board scanning, sliding piece movement, and input validation retry |
| **Conditionals** | `if/else`, `switch` for piece selection, move validation, and game flow |
| **Multi-file Design** | Code split across `globals.h`, `board`, `pieces`, `game`, and `main` for maintainability |
| **Header Guards** | `#ifndef` / `#define` / `#endif` in every header file |

> **No OOP, no classes, no STL containers, no templates** — pure procedural C++.

---

## 🗂️ Project Structure

```
📦 Chess-Game/
 ┣ 📂 src/
 ┃  ┣ 📄 main.cpp       ← Entry point: defines globals, calls start()
 ┃  ┣ 📄 globals.h      ← Shared constants, Position struct, extern declarations
 ┃  ┣ 📄 board.h        ← Board function declarations
 ┃  ┣ 📄 board.cpp      ← Board init, display, input validation, score display
 ┃  ┣ 📄 pieces.h       ← Piece function declarations
 ┃  ┣ 📄 pieces.cpp     ← All 6 pieces: move validation + possibility highlighting
 ┃  ┣ 📄 game.h         ← Game logic declarations
 ┃  ┗ 📄 game.cpp       ← Game loop, menus, turn handling, checkmate, resign
 ┣ 📂 docs/
 ┃  ┗ 📄 Final Project 2023.pdf   ← Original project specification
 ┣ 📄 .gitignore
 ┗ 📄 README.md
```

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler: [GCC / MinGW](https://gcc.gnu.org/) or any g++ compatible compiler

### Compile & Run

```bash
# Clone the repository
git clone https://github.com/Areeba-Riazz/Chess-Game.git
cd Chess-Game/src

# Compile
g++ main.cpp board.cpp pieces.cpp game.cpp -o chess

# Run
./chess          # Linux / macOS
chess.exe        # Windows
```

---

## 🕹️ How to Play

#### On Launch
1. Enter both player names
2. Choose a game mode from the main menu:
   - **Mode 1 — Explore Moves:** Pick any piece, give it a board position, and see all valid moves highlighted. Great for learning piece rules.
   - **Mode 2 — Play Chess:** Full two-player game with alternating turns.

#### During a Game Turn
1. The board is displayed showing all pieces
2. Choose which piece to move (1–6) or press 7 to resign
3. For pairs (Rook, Bishop, Knight): choose Left or Right
4. Board refreshes showing valid destinations marked with **`x`**
5. Enter your destination row and column
6. Invalid moves prompt you to try again — no crashes

#### Winning
- Capture the opponent's King to win. The game declares the winner and returns to the main menu.

---

## ⚠️ Limitations

- No *check* warning — the game detects checkmate only when the King is actually captured
- Special moves not implemented: castling, en passant, pawn promotion
- Local multiplayer only — no AI opponent

---

## 📌 Board Legend

| Symbol | Meaning |
|---|---|
| `K Q B R N P` | White pieces (Player 1) |
| `k q b r n p` | Black pieces (Player 2) |
| `.` | Empty square |
| `x` | Valid move for selected piece |

---

*Developed for Programming Fundamentals (CL-1002), FAST-NUCES Islamabad*
