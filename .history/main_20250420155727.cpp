
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <random>
#include <numeric>
#include "timer.h"
#include "tile.h"
#include "board.h"
#include "welcome.h"
#include "main.h"
using namespace std;

int main()
{
    string boardFile = "files/config.cfg";
    ifstream input(boardFile);
    string number;
    vector<int> board;
    while (getline(input, number))
    {
        int num = stoi(number);
        board.push_back(num);
    }

    int numColumns = board[0];
    int numRows = board[1];
    int numMines = board[2];
    int width = numColumns * 32;
    int height = (numRows * 32) + 100;

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    Welcome welcome(width, height, font);
    string name = welcome.welcomeWindow();

    if (name.empty())
    {
        cout << "Exiting..." << endl;
        return 0;
    }

    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Game board", sf::Style::Close);
    // gameWindow.setFramerateLimit(10);

    Board newBoard(numColumns, numRows, numMines);
    bool debug = false;

    sf::Sprite gameSprite;
    sf::Sprite digitSprite;

    sf::Texture happyTexture;
    happyTexture.loadFromFile("files/images/face_happy.png");
    float happyPositionX = (numColumns / 2.0 * 32) - 32;
    float happyPositionY = (numRows + 0.5) * 32;
    sf::Vector2u happyTextureSize = happyTexture.getSize();

    sf::Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    float debugPositionX = (numColumns * 32) - 304;
    float debugPositionY = (numRows + 0.5) * 32;
    sf::Vector2u debugTextureSize = debugTexture.getSize();
    float debugEndX = debugPositionX + debugTextureSize.x;
    float debugEndY = debugPositionY + debugTextureSize.y;

    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");
    float pausePositionX = numColumns * 32 - 240;
    float pausePositionY = (numRows + 0.5) * 32;
    sf::Vector2u pauseTextureSize = pauseTexture.getSize();
    float pauseEndX = pausePositionX + pauseTextureSize.x;
    float pauseEndY = pausePositionY + pauseTextureSize.y;

    sf::Texture playTexture;
    playTexture.loadFromFile("files/images/play.png");

    sf::Texture digitsTexture;
    digitsTexture.loadFromFile("files/images/digits.png");
    digitSprite.setTexture(digitsTexture);

    timer timer;
    while (gameWindow.isOpen())
    {

        gameWindow.clear(sf::Color::White);

        newBoard.drawGameBoard(gameWindow, debug);

        gameSprite.setTexture(happyTexture);
        gameSprite.setPosition(happyPositionX, happyPositionY);
        gameWindow.draw(gameSprite);

        gameSprite.setTexture(debugTexture);
        gameSprite.setPosition(debugPositionX, debugPositionY);
        gameWindow.draw(gameSprite);

        if (timer.isPaused())
        {
            gameSprite.setTexture(playTexture);
        }
        else
        {
            gameSprite.setTexture(pauseTexture);
        }
        gameSprite.setPosition(pausePositionX, pausePositionY);
        gameWindow.draw(gameSprite);

        // timer
        pair<int, int> elapsed = timer.get_elapsed_time();
        float minutesStartX = numColumns * 32 - 97; // Starting X position for minutes
        float secondsStartX = numColumns * 32 - 54; // Starting X position for seconds
        float timerY = (numRows + 0.5) * 32 + 16;   // Y position for the timer

        string minutes = (elapsed.first < 10) ? "0" + to_string(elapsed.first) : to_string(elapsed.first);
        string seconds = (elapsed.second < 10) ? "0" + to_string(elapsed.second) : to_string(elapsed.second);

        float currentX = minutesStartX;
       drawDigits(minutes, digitSprite, digitsTexture, currentX, timerY, gameWindow);

        currentX = secondsStartX;
        for (char c : seconds)
        {
            int digit = c - '0'; 
            digitSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, digitsTexture.getSize().y));
            digitSprite.setPosition(currentX, timerY);
            gameWindow.draw(digitSprite);
            currentX += 21; // 
        }


        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
            }
            else if (newBoard.getStatus() == 0 && event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);

                if (debugPositionX <= mousePosition.x && mousePosition.x <= debugEndX && debugPositionY <= mousePosition.y && mousePosition.y <= debugEndY)
                {
                    cout << "hi" << endl;
                    debug = (!debug);
                    cout << debugPositionX << " " << debugPositionY << endl;
                }
                else if (pausePositionX <= mousePosition.x && mousePosition.x <= pauseEndX && pausePositionY <= mousePosition.y && mousePosition.y <= pauseEndY)
                {
                    if (timer.isStarted())
                    {
                        if (timer.isPaused())
                        {
                            timer.resume();
                        }
                        else
                        {
                            timer.pause();
                        }
                    }
                }
                else if (0 <= mousePosition.x && mousePosition.x <= width && 0 <= mousePosition.y && mousePosition.y <= height - 100)
                {
                    int xIndex = mousePosition.x / 32;
                    int yIndex = mousePosition.y / 32;

                    if (!timer.isStarted())
                    {
                        timer.start();
                    }

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        newBoard.openTile(xIndex, yIndex);
                        if (newBoard.isWin())
                        {
                            newBoard.setStatus(1);
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        newBoard.flagTile(xIndex, yIndex);
                    }
                }
            }

            sf::Texture leader;
            leader.loadFromFile("files/images/leaderboard.png");

            sf::Sprite _leader;
            _leader.setTexture(leader);
            _leader.setColor(sf::Color(255, 255, 255, 200));
            _leader.setPosition(numColumns * 32 - 176, (numRows + 0.5) * 32);
            gameWindow.draw(_leader);
        }
        gameWindow.display();
    }

    return 0;
}

void drawDigits(std::string &minutes, sf::Sprite &digitSprite, sf::Texture &digitsTexture, float &currentX, float timerY, sf::RenderWindow &gameWindow)
{
 for (char c : minutes)
        {
            int digit = c - '0'; // Convert char to int
            digitSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, digitsTexture.getSize().y));
            digitSprite.setPosition(currentX, timerY);
            gameWindow.draw(digitSprite);
            currentX += 21; // Move to the next position
        }
}
