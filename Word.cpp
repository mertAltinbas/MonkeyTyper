#include "Word.h"

using namespace sf;
using namespace std;

Word::Word(const string &text, const Font &font, float speed) : text(text), speed(speed), typed(false) {
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(30);
    sfText.setFillColor(Color::White);
    sfText.setPosition(0, rand() % 400 + 100); // Random Y position
}

void Word::update(float deltaTime) {
    if (!typed) {
        sfText.move(speed * deltaTime, 0);
    }
}

void Word::draw(RenderWindow &window) const {
    window.draw(sfText);
}

bool Word::isTyped() const {
    return typed;
}

void Word::checkTyping(const string &typedText) {
    if (typedText == text) {
        typed = true;
    }
}

bool Word::isOutOfBounds() {
    if (sfText.getPosition().x > 1600 && !isOutOfBoundsFlag) {
        isOutOfBoundsFlag = true;
        return true;
    }
    return false;
}

int Word::getWordLength() const {
    return text.size();
}
