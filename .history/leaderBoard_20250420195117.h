#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <numeric>
using namespace std;

#include <tuple>

struct ScoreEntry
{
    std::string name;
    int totalSeconds;

    ScoreEntry(const std::string &playerName, int playerMinutes, int playerSeconds)
        : name(playerName), totalSeconds(playerMinutes * 60 + playerSeconds) {}

    ScoreEntry(const std::string &data)
    {
        auto commaPos = data.find(',');
        auto colonPos = data.find(':');
        int minutes = std::stoi(data.substr(0, colonPos));
        int seconds = std::stoi(data.substr(colonPos + 1, commaPos - colonPos - 1));
        name = data.substr(commaPos + 2);
        totalSeconds = minutes * 60 + seconds;
    }

    std::string getTimeString() const
    {
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        return (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
               (seconds < 10 ? "0" : "") + std::to_string(seconds);
    }

    std::string toString() const
    {
        return getTimeString() + ",   " + name;
    }
};

class leaderBoard
{
    int width, height;
    sf::Font font;
    std::vector<ScoreEntry> board;

    const std::string boardFile = "files/leaderboard.txt";

public:
    leaderBoard(int w, int h, sf::Font f)
    {
        width = w;
        height = h;
        font = f;
        loadScoresFromFile();
    }

    void saveScoresToFile()
    {
        std::ofstream output(boardFile);
        for (int i = 0; i < board.size(); i++)
        {
            output << i << ".  " << board.at(i).toString() << std::endl;
        }
    }

    void loadScoresFromFile()
    {
        ifstream input(boardFile);

        std::string line;
        while (std::getline(input, line))
        {
            board.push_back(ScoreEntry(line));
        }
    }

    void addToBoard(string name, int minutes, int seconds)
    {
        int totalSeconds = minutes * 60 + seconds;
        for (auto it = board.begin(); it != board.end(); ++it)
        {
            if (totalSeconds < it->totalSeconds)
            {
                board.insert(it, ScoreEntry(name, minutes, seconds));
                if (board.size() > 5)
                {
                    board.pop_back();
                }
                saveScoresToFile();
                return;
            }
        }

        if (board.size() < 5)
        {
            board.push_back(ScoreEntry(name, minutes, seconds));
            saveScoresToFile();
        }
    }

    void drawLeaderBoard()
    {

        sf::RenderWindow leaderWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

        sf::Text title;
        title.setFont(font);
        title.setString("LEADERBOARD");
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width / 2.0f,
                        titleRect.top + titleRect.height / 2.0f);
        title.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 150));

        while (leaderWindow.isOpen())
        {
            sf::Event event;
            while (leaderWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    leaderWindow.close();
                }
            }

            leaderWindow.clear(sf::Color::Blue);
            leaderWindow.draw(title);
            for (int i = 0; i < board.size(); i++)
            {
                sf::Text scoreText;
                scoreText.setFont(font);
                scoreText.setString(i + ".  " + board[i].toString());
                scoreText.setCharacterSize(20);
                scoreText.setFillColor(sf::Color::White);
                scoreText.setStyle(sf::Text::Bold);
                sf::FloatRect scoreRect = scoreText.getLocalBounds();
                scoreText.setOrigin(scoreRect.left + scoreRect.width / 2.0f,
                                    scoreRect.top + scoreRect.height / 2.0f);
                scoreText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 75 + (i * 30)));
                leaderWindow.draw(scoreText);
            }
            leaderWindow.display();
        }
    }
};

#endif // LEADERBOARD_H
