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

std::vector<ScoreEntry> board;
class leaderBoard
{
public:
    leaderBoard();
    void addScore(int score);
    void displayScores();
    void saveScoresToFile(const std::string &filename);

    void loadScoresFromFile(const std::string &filename)
    {
        string boardFile = "files/leaderboard.txt";
        ifstream input(boardFile);
    
        while (getline(input, number))
        {
            int num = stoi(number);
            board.push_back(num);
        }
    }
};
