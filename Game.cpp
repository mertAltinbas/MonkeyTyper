#include "Game.h"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

// Paths to resources
auto fontPath = R"(C:\Users\lordo\OneDrive\Belgeler\MonkeyTyper\components\fonts\Roboto-Medium.ttf)";
auto wordsPath = R"(C:\Users\lordo\OneDrive\Belgeler\MonkeyTyper\components\words\words.txt)";
auto iconPath = R"(C:\Users\lordo\OneDrive\Belgeler\MonkeyTyper\components\images\monkey.png)";
auto scorePath = R"(C:\Users\lordo\OneDrive\Belgeler\MonkeyTyper\components\score.txt)";
auto saveGamePath = R"(C:\Users\lordo\OneDrive\Belgeler\MonkeyTyper\components\saveGame.txt)";

Game::Game() : window(VideoMode(1600, 600), "MonkeyTyper"), timeSinceLastSpawn(Time::Zero) {
    font.loadFromFile(fontPath);
    loadWordsFromFile(wordsPath);

    // Set Icon
    Image monkeyIcon;
    monkeyIcon.loadFromFile(iconPath);
    window.setIcon(monkeyIcon.getSize().x, monkeyIcon.getSize().y, monkeyIcon.getPixelsPtr());

    // show typed word
    typedTextDisplay.setString("[  ]");
    typedTextDisplay.setFont(font);
    typedTextDisplay.setFillColor(Color::White);
    typedTextDisplay.setPosition(100, 25);

    // Lives
    lives = 4;
    livesText.setString("Lives: " + to_string(lives));
    livesText.setFont(font);
    livesText.setFillColor(Color::White);
    livesText.setPosition(1400, 25);

    // Typed counter
    typedTextCounter = 0;
    typedTextCount.setString("Typed Text Count: " + to_string(typedTextCounter));
    typedTextCount.setFont(font);
    typedTextCount.setFillColor(Color::White);
    typedTextCount.setPosition(400, 25);

    score = 0;
    scoreText.setString("Score: " + to_string(score));
    scoreText.setFont(font);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(1000, 25);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        Time deltaTime = clock.restart();
        update(deltaTime);
        render();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            saveGameState();
            showMainMenu();
        }
    }
}

void Game::processEvents() {
    Event event{};
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::TextEntered) {
            if (event.text.unicode < 128) {
                currentTypedText += static_cast<char>(event.text.unicode);
                handleInput();
                typedTextDisplay.setString("[ " + currentTypedText + " ]");
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
            if (!currentTypedText.empty()) {
                currentTypedText.pop_back();
                typedTextDisplay.setString("[ " + currentTypedText + " ]");
            }
        }
    }
}

void Game::update(Time deltaTime) {
    timeSinceLastSpawn += deltaTime;

    // Spawn new words with time
    if (timeSinceLastSpawn >= seconds(1.5f) && !remainingWords.empty()) {
        timeSinceLastSpawn = Time::Zero;
        const string &wordText = remainingWords.front();

        // Set words speed
        if (wordText.length() <= 3) {
            words.emplace_back(wordText, font, setSpeedFast);
        } else if (wordText.length() >= 10) {
            words.emplace_back(wordText, font, setSpeedSlow);
        } else {
            words.emplace_back(wordText, font, setSpeedDefault);
        }
        remainingWords.erase(remainingWords.begin()); // Remove word from remaining words list
    }

    for (auto &word: words) {
        word.update(deltaTime.asSeconds());
        if (word.isTyped()) {
            words.erase(remove_if(words.begin(), words.end(),
                                  [](const Word &w) { return w.isTyped(); }), words.end());
            break;
        }

        if (lives > 0 && word.isOutOfBounds()) {
            lives--;
            livesText.setString("Lives: " + to_string(lives));
        }
    }
    if (lives == 0) {
        showEndMenu();
    }
}

void Game::render() {
    window.clear();

    for (const auto &word: words) {
        word.draw(window);
    }
    window.draw(typedTextDisplay);
    window.draw(livesText);
    window.draw(typedTextCount);
    window.draw(scoreText);

    window.display();
}

void Game::handleInput() {
    vector<Word *> typedWords; // Create a vector to store the typed words

    for (auto &word: words) {
        word.checkTyping(currentTypedText);
        if (word.isTyped()) {
            typedWords.push_back(&word); // Add the typed word to the vector
            currentTypedText.clear();
            typedTextCounter++;
            score += word.getWordLength() / 2;
        }
    }

    // Clear the typed words from the vector
    typedWords.clear();

    typedTextDisplay.setString("");
    typedTextCount.setString("Typed Text Count: " + to_string(typedTextCounter));
    scoreText.setString("Score: " + to_string(score));


    // Check if space key is pressed
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        // Clear typed text if space key is pressed
        currentTypedText.clear();
    }
}

void Game::loadWordsFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file - '" << filename << "'" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            remainingWords.push_back(line); // Store words in the remainingWords list
        }
    }
    file.close();
}

void Game::saveScore(const string &filename) {
    ifstream fileRead(filename); // to read
    ofstream fileWrite(filename, ios::app); // to write, ios::app overwrite file

    if (!fileRead.is_open() || !fileWrite.is_open()) {
        cout << "Could not open the file - '" << filename << "'" << endl;
        return;
    }
    fileWrite << score << endl; // add score

    highScore = 0;
    int currentScore;
    while (fileRead >> currentScore) {
        if (currentScore > highScore) {
            highScore = currentScore;
        }
    }

    fileRead.close();
    fileWrite.close();
}


void Game::settingsPage() {
    adjustedDifficulty = "Medium";

    Text backText;
    backText.setString("BackSpace");
    backText.setFont(font);
    backText.setCharacterSize(25);
    backText.setFillColor(Color::White);
    backText.setPosition(50, 50);

    Text difficultyText;
    difficultyText.setString("Easy Difficulty 'e'\n\nMedium Difficulty 'm'\n\nHard Difficulty 'h'");
    difficultyText.setFont(font);
    difficultyText.setCharacterSize(30);
    difficultyText.setFillColor(Color::White);
    difficultyText.setPosition(600, 200);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                showMainMenu();
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) {
                setSpeedDefault = 75.f;
                setSpeedSlow = 50.f;
                setSpeedFast = 125.f;
                adjustedDifficulty = "Easy";
            } else if (Keyboard::isKeyPressed(Keyboard::M)) {
                setSpeedDefault = 125.f;
                setSpeedSlow = 100.f;
                setSpeedFast = 175.f;
                adjustedDifficulty = "Medium";
            } else if (Keyboard::isKeyPressed(Keyboard::H)) {
                setSpeedDefault = 225.f;
                setSpeedSlow = 200.f;
                setSpeedFast = 250.f;
                adjustedDifficulty = "Hard";
            }
        }

        Text adjustedDifficultyText;
        adjustedDifficultyText.setString("Difficulty: " + adjustedDifficulty);
        adjustedDifficultyText.setFont(font);
        adjustedDifficultyText.setCharacterSize(50);
        adjustedDifficultyText.setFillColor(Color::White);
        adjustedDifficultyText.setPosition(600, 100);

        window.clear();
        window.draw(backText);
        window.draw(difficultyText);
        window.draw(adjustedDifficultyText);
        window.display();
    }
}

void Game::showMainMenu() {
    Text mainMenuText;
    mainMenuText.setString("Monkey Typer");
    mainMenuText.setFont(font);
    mainMenuText.setCharacterSize(50);
    mainMenuText.setFillColor(Color::White);
    mainMenuText.setPosition(600, 200);

    Text newGameText;
    newGameText.setString("Press 'Space' to New Game");
    newGameText.setFont(font);
    newGameText.setCharacterSize(30);
    newGameText.setFillColor(Color::White);
    newGameText.setPosition(600, 300);

    Text loadGameText;
    loadGameText.setString("Press 'L' to Load Game");
    loadGameText.setFont(font);
    loadGameText.setCharacterSize(30);
    loadGameText.setFillColor(Color::White);
    loadGameText.setPosition(600, 350);

    Text settingsText;
    settingsText.setString("Press 'RShift' to Settings");
    settingsText.setFont(font);
    settingsText.setCharacterSize(20);
    settingsText.setFillColor(Color::White);
    settingsText.setPosition(1200, 500);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                resetGame(); // game is reset before starting
                run(); // Exit the menu and start the game
            }
            if (Keyboard::isKeyPressed(Keyboard::L)) {
                loadGameState(); // game is reset before starting
                run(); // Exit the menu and start the game
            }
            if (Keyboard::isKeyPressed(Keyboard::RShift)) {
                settingsPage();
            }
        }

        window.clear();
        window.draw(mainMenuText);
        window.draw(newGameText);
        window.draw(loadGameText);
        window.draw(settingsText);
        window.display();
    }
}


void Game::showEndMenu() {
    Text gameOverText;
    gameOverText.setString("G A M E   O V E R");
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(600, 150);

    Text playAgainText;
    playAgainText.setString("Press 'm' to Play Again");
    playAgainText.setFont(font);
    playAgainText.setCharacterSize(30);
    playAgainText.setFillColor(Color::White);
    playAgainText.setPosition(1200, 500);


    saveScore(scorePath); // Saving scores
    Text maxScoreText;
    maxScoreText.setString("Best Score: " + to_string(highScore));
    maxScoreText.setFont(font);
    maxScoreText.setCharacterSize(30);
    maxScoreText.setFillColor(Color::White);
    maxScoreText.setPosition(600, 450);

    typedTextCount.setPosition(600, 250);
    scoreText.setPosition(600, 350);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::M)) {
                resetGame();
                showMainMenu();
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(maxScoreText);
        window.draw(typedTextCount);
        window.draw(playAgainText);
        window.display();
    }
}

void Game::resetGame() {
    // reset game state
    lives = 4;
    score = 0;
    typedTextCounter = 0;
    currentTypedText.clear();
    words.clear();
    remainingWords.clear();
    loadWordsFromFile(wordsPath);

    typedTextDisplay.setString("[  ]");
    typedTextDisplay.setPosition(100, 25); // Set to original position

    livesText.setString("Lives: " + to_string(lives));
    livesText.setPosition(1400, 25); // Set to original position

    typedTextCount.setString("Typed Text Count: " + to_string(typedTextCounter));
    typedTextCount.setPosition(400, 25); // Set to original position

    scoreText.setString("Score: " + to_string(score));
    scoreText.setPosition(1000, 25); // Set to original position
}

void Game::saveGameState() {
    ofstream file(saveGamePath);
    file << score << endl;
    file << lives << endl;
    file << typedTextCounter << endl;
    file << currentTypedText << endl;
    file.close();
}

void Game::loadGameState() {
    ifstream file(saveGamePath);
    file >> score;
    file >> lives;
    file >> typedTextCounter;
    file >> currentTypedText;
    clock.restart();
    timeSinceLastSpawn = Time::Zero;

    file.close();
}