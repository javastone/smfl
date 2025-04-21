#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>

class Textbox {
public:
    Textbox() : isSelected(false), hasLimit(false), limit(0) {}

    void setFont(const sf::Font& font) {
        text.setFont(font);
    }

    void setColor(const sf::Color& color) {
        text.setFillColor(color);
    }

    void setPosition(float x, float y) {
        text.setPosition(x, y);
    }

    void setLimit(bool hasLimit, unsigned int limit = 0) {
        this->hasLimit = hasLimit;
        this->limit = limit;
    }

    void setSelected(bool selected) {
        isSelected = selected;
        if (!isSelected) {
            text.setString(inputString);
        }
    }

    void handleInput(sf::Event event) {
        if (isSelected) {
            if (event.type == sf::Event::TextEntered) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (std::isalpha(enteredChar)) { // Only allow regular characters
                    if (!hasLimit || inputString.size() < limit) {
                        inputString += enteredChar;
                    }
                } else if (enteredChar == '\b' && !inputString.empty()) { // Handle backspace
                    inputString.pop_back();
                }
                text.setString(inputString + "_");
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                isSelected = false;
                text.setString(inputString);
                // Capitalize the first letter and set others to lowercase
                
                if (!inputString.empty()) {
                    inputString[0] = std::toupper(inputString[0]);
                    for (size_t i = 1; i < inputString.size(); ++i) {
                        inputString[i] = std::tolower(inputString[i]);
                    }
                }

                // Center the string
                sf::FloatRect textBounds = text.getLocalBounds();
                sf::Vector2f position = text.getPosition();
                text.setOrigin(textBounds.width / 2, textBounds.height / 2);
                text.setPosition(position.x + textBounds.width / 2, position.y + textBounds.height / 2);
            }
        }
    }

    std::string getText() const {
        return inputString;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }

private:
    sf::Text text;
    std::string inputString;
    bool isSelected;
    bool hasLimit;
    unsigned int limit;
};

#endif // TEXTBOX_H