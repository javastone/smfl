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
        return getTimeString() + ", " + name;
    }
};

class leaderBoard
{
    std::vector<ScoreEntry> board;

public:
    leaderBoard();
    void addScore(int score);
    void displayScores();
    void saveScoresToFile(const std::string &filename){
        std::ofstream output(filename);
        for (const auto &entry : board)
        {
            output << entry.toString() << std::endl;
        }
    }

    void loadScoresFromFile(const std::string &filename)
    {
        string boardFile = "files/leaderboard.txt";
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
                saveScoresToFile("files/leaderboard.txt");
                return;
            }
        }

        if (board.size() < 5)
        {
            board.push_back(ScoreEntry(name, minutes, seconds));
            saveScoresToFile("files/leaderboard.txt");
        }
    }
};

#endif // LEADERBOARD_H
