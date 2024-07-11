#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include "Word.h"

using namespace sf;
using namespace std;

class Game {
public:
    Game();

    void showMainMenu();
    void run();
    void showEndMenu();
    void resetGame();

private:
    void processEvents();
    void update(Time deltaTime);
    void render();
    void handleInput();
    void loadWordsFromFile(const string &filename);
    void saveScore(const string &filename);
    void settingsPage();
    void saveGameState();
    void loadGameState();

    RenderWindow window;
    Font font;
    vector<Word> words;
    vector<std::string> remainingWords; // Store remaining words to be displayed
    Clock clock;
    Time timeSinceLastSpawn;
    string currentTypedText;
    Text typedTextDisplay;
    Text typedTextCount;
    int typedTextCounter;
    Text livesText;
    int lives;
    Text scoreText;
    int score;
    int highScore;
    float setSpeedDefault = 125.f;
    float setSpeedSlow = 100.f;
    float setSpeedFast = 175.f;
    string adjustedDifficulty;
};

#endif // GAME_H
