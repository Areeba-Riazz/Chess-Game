# ♟️ Console Chess — C++

A **console-based two-player Chess game** written in C++ as a Programming Fundamentals (Spring 2023) course project. The game runs entirely in the terminal and implements core chess piece movement rules on a full 8×8 board.

> **Authors:** Areeba Riaz (i221244) · Arslan Javed (i220613)  
> **Course:** Programming Fundamentals — Spring 2023

---

## 🎮 Features

- Full 8×8 chess board rendered in the console
- Two-player alternating turn system
- **5 piece types** with correct movement rules:
  - ♔ **King** — moves one square in any direction
  - ♕ **Queen** — moves any number of squares diagonally or straight
  - ♗ **Bishop** — moves any number of squares diagonally
  - ♖ **Rook** — moves any number of squares in a straight line
  - ♘ **Knight** — moves in an L-shape (2+1 squares)
- **Valid move highlighting** — shows all possible destinations before you choose
- Piece capture support
- Input validation (handles non-integer and out-of-bounds input)

---

## 🧠 Concepts Used

This project was built using **Programming Fundamentals** concepts only:

- 2D Arrays (`char board[8][8]`)
- Functions (modular design — each piece has its own move + possibilities function)
- Loops (`for`, `while`)
- Conditionals (`if/else`)
- Global variables & basic I/O

---

## 🕹️ How to Play

### Compile
```bash
g++ "Areeba-Riaz_i221244_Arslan-Javed_i220613_D_Project.cpp" -o chess
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
 ┣ 📄 Areeba-Riaz_i221244_Arslan-Javed_i220613_D_Project.cpp   ← Full source code
 ┣ 📄 Final Project 2023.pdf                                    ← Original project spec
 ┗ 📄 README.md
```

---

## ⚠️ Known Limitations

- Pawns are not yet implemented (planned)
- Checkmate detection is a stub (declares a message but does not end the game)
- No check / check-detection logic yet
- Special moves (castling, en passant, pawn promotion) not implemented

---

## 🔄 Planned Improvements

- [ ] Add pawns with full movement rules
- [ ] Implement proper checkmate (game ends + winner declared)
- [ ] Add pointers (required by project spec)
- [ ] Refactor into multiple files for cleaner organization
- [ ] Capture counter / score display
- [ ] Game mode menu: "Explore Moves" vs "Play Game"

---

## 📜 License

This project was submitted as an academic assignment. Feel free to reference it for learning purposes.
