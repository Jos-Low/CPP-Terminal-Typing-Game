# C++ Terminal Typing Game & Wordle 🖥️⌨️  
**A dual-mode terminal application featuring a fast-paced typing speed test and a classic Wordle clone — all built in modern C++.**

Test your **typing accuracy under pressure** or challenge your **word-guessing skills** with two engaging games in one lightweight, cross-platform terminal program.

---

## 🎮 Game Modes

### 1. **Typing Speed Challenge**
- Random words are loaded from `words.txt`.
- Type as many words as possible before the timer expires.
- **Real-time visual feedback**:
  - ✅ **Green** for correct characters
  - ❌ **Red** for mistakes
- Tracks **Words Per Minute (WPM)** and **accuracy** in real time.

### 2. **Wordle Clone**
- Guess the hidden 5-letter word in **6 attempts**.
- Feedback system:
  - 🟩 **Green** — Correct letter in correct position  
  - 🟨 **Yellow** — Correct letter in wrong position  
  - ⬜ **Gray** — Letter not in word
- Uses a curated list of valid 5-letter words.
- Displays letters left not used

---

## ✨ Features

- **Interactive menu** to switch between Typing Game and Wordle
- **Non-blocking keyboard input** using `termios` and `fcntl` (no Enter required)
- **ANSI color escape codes** for vibrant terminal UI
- **Modular C++20 design** with clean separation of concerns
- **Cross-compatible**: Works on **Linux**, **WSL**, and **macOS** (with minor adjustments)
- Lightweight — no external dependencies

---

## 🛠️ Compilation & Running

### Requirements
- **C++20-compatible compiler** (e.g., `g++` 10 or later)
- **POSIX terminal** (Linux, WSL, or macOS)

### Compile
```bash
g++ -std=c++20 main.cpp typing_game.cpp wordle.cpp -o typer
```

### Run
```bash
./typer
```

> **Tip**: Add `-O2` for optimized performance or `-g` for debugging.

---

## 📁 Project Structure
```
.
├── main.cpp          → Entry point & game mode selector
├── typing_game.cpp   → Core typing speed logic
├── wordle.cpp        → Wordle game implementation
├── words.txt         → Word bank for typing mode
├── wordle_words.txt  → Valid 5-letter words for Wordle
└── README.md
```

---

## 🚀 Why This Project?

Designed with **clean code**, **modern C++ practices**, and **user experience** in mind:
- Demonstrates **file I/O**, **real-time input handling**, and **state management**
- Showcases **modular design** and **menu-driven architecture**
- Highlights **terminal UI/UX** without GUI frameworks
- Ideal for **portfolio review** — shows problem-solving, systems programming, and attention to detail

---

## 🔧 Customization

- Edit `words.txt` to change typing vocabulary
- Modify `wordle_words.txt` to adjust Wordle word pool
- Adjust timer duration in `typing_game.cpp`
- Change colors via ANSI codes in source
