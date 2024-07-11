#ifndef WORD_H
#define WORD_H

#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;

class Word {
public:
    Word(const string& text, const Font& font, float speed);


    void update(float deltaTime);
    void draw(RenderWindow& window) const;
    bool isTyped() const;
    void checkTyping(const string& typedText);
    bool isOutOfBounds();
    auto getWordLength() const -> int; // define

    bool isOutOfBoundsFlag = false;
    Text sfText;
private:
    string text;
    float speed;
    bool typed;
};

#endif // WORD_H
