#ifndef WELCOME_H
#define WELCOME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

class Welcome
{
    int width, height;
    sf::Font font;

public:
    Welcome(){};
    Welcome(int w, int h, sf::Font f)
    {
        width = w;
        height = h;
        font = f;
    }

    string welcomeWindow()
    {
        sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

        sf::Text title;
        title.setFont(font);
        title.setString("WELCOME TO MINESWEEPER!");
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width / 2.0f,
                        titleRect.top + titleRect.height / 2.0f);
        title.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 150));

        // enter your name
        sf::Text name;
        name.setFont(font);
        name.setString("Enter your name:");
        name.setCharacterSize(20);
        name.setFillColor(sf::Color::White);
        name.setStyle(sf::Text::Bold);
        sf::FloatRect name1Rect = name.getLocalBounds();
        name.setOrigin(name1Rect.left + name1Rect.width / 2.0f,
                       name1Rect.top + name1Rect.height / 2.0f);
        name.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 75));

        sf::Text userInput;
        userInput.setFont(font);
        userInput.setCharacterSize(18);
        userInput.setFillColor(sf::Color::Yellow);
        userInput.setStyle(sf::Text::Bold);
        sf::FloatRect userInputRect = userInput.getLocalBounds();
        userInput.setOrigin(userInputRect.left + userInputRect.width / 2.0f,
                            userInputRect.top + userInputRect.height / 2.0f);
        userInput.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 45));
        userInput.setString("|");

        string x = "";

        while (welcomeWindow.isOpen())
        {
            sf::Event event;
            while (welcomeWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    welcomeWindow.close();
                    return "";
                }
                if (event.type == sf::Event::TextEntered)
                {
                    // userInput.setString(x + "|");
                    // sf::FloatRect newBounds = userInput.getLocalBounds();
                    // userInput.setOrigin(newBounds.left + newBounds.width / 2.0f,
                    //                     newBounds.top + newBounds.height / 2.0f);
                    // userInput.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 34));
                    if (event.text.unicode >= 32 && event.text.unicode < 128)
                    {
                        if (x.size() < 10)
                        {
                            if (isalpha(event.text.unicode))
                            {
                                x += event.text.unicode;
                                if (x.size() >= 1)
                                {
                                    x[0] = toupper(x[0]);
                                    for (unsigned int i = 1; i < x.size(); i++)
                                    {
                                        x[i] = tolower(x[i]);
                                    }
                                    userInput.setString(x + "|");
                                    sf::FloatRect newBounds = userInput.getLocalBounds();
                                    userInput.setOrigin(newBounds.left + newBounds.width / 2.0f,
                                                        newBounds.top + newBounds.height / 2.0f);
                                    userInput.setPosition(sf::Vector2f(width / 2.0, height / 2.0 - 28));
                                }
                                userInput.setString(x + "|");
                            }
                        }
                    }
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::BackSpace)
                    {
                        userInput.setString(x + "|");
                        sf::FloatRect newBounds = userInput.getLocalBounds();
                        userInput.setOrigin(newBounds.left + newBounds.width / 2.0f,
                                            newBounds.top + newBounds.height / 2.0f);
                        userInput.setPosition(sf::Vector2f(394, height / 2.0f - 28));

                        if (!x.empty())
                        {
                            x.pop_back();
                            userInput.setString(x + "|");
                        }
                    }
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (x.size() >= 1)
                        {
                            welcomeWindow.close();
                            return x;
                        }
                    }
                }
            }
            welcomeWindow.clear(sf::Color::Blue);
            welcomeWindow.draw(title);
            welcomeWindow.draw(name);
            welcomeWindow.draw(userInput);
            welcomeWindow.display();
        }
        return "";
    }
};

#endif //WELCOME_H
