# Monkey Typer

Monkey Typer is a fast-paced typing game built with C++ and SFML. The goal is to type falling words before they reach the edge of the screen. The game includes a scoring system, adjustable difficulty levels, and a save/load feature for game progress.

## Features
- **Typing Challenge:** Type words before they disappear.
- **Scoring System:** Earn points based on word length.
- **Lives System:** Lose lives for missed words.
- **Adjustable Difficulty:** Choose from Easy, Medium, or Hard modes.
- **Game Save & Load:** Continue where you left off.
- **Simple UI:** Uses SFML for smooth rendering.

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/MonkeyTyper.git
   ```
2. Ensure you have SFML installed.
3. Compile the project:
   ```sh
   g++ -o MonkeyTyper main.cpp Game.cpp Word.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```
4. Run the game:
   ```sh
   ./MonkeyTyper
   ```

## Controls
- **Type Words:** Type as they appear on the screen.
- **Backspace:** Delete characters.
- **Escape:** Save and return to the main menu.
- **Space:** Start a new game.
- **L:** Load a saved game.
- **Right Shift:** Open settings.
- **M:** Restart after game over.

## Dependencies
- **SFML** (Simple and Fast Multimedia Library)
