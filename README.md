# C++ Terminal Typing Game 🖥️⌨️

A simple **terminal-based typing game** written in C++.  
Test your typing speed and accuracy under a time limit!

---

## Overview

This game displays random words from a word list (`words.txt`) and challenges the player to type them correctly before the timer runs out. Correct letters are highlighted in **green**, incorrect letters in **red**, and the score is tracked in real time.  

---

## Features

- Random words loaded from a text file.
- Real-time feedback on typed letters:
  - ✅ Green for correct letters
  - ❌ Red for incorrect letters
- Timer-based gameplay.
- Tracks number of correctly typed words.
- Uses non-blocking input (`termios` + `fcntl`) to read characters without pressing Enter.
- Cross-platform compatible with Linux and WSL (Windows Subsystem for Linux).

---

## Requirements

- C++20 compatible compiler (e.g., `g++` 10+)
- Linux or WSL terminal (uses POSIX `termios` and `fcntl`)

---

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/typing-game.git
   cd typing-game

2. For most efficient compile use:
   g++ -std=c++17 -O0 -Wall -Wextra -o game main.cpp

