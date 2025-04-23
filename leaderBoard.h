//
// Created by sophi on 4/22/2025.
//

#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

#include "leader.h"

class leaderboard {
    int width;
    int height;
    vector<leader> data;
    sf::Font font;
public:
    leaderboard(){};
    leaderboard(int w, int h, sf::Font f) : width(w), height(h), font(f) {}
    void readData() {
        string leaderFile = "files/leaderboard.txt";
        ifstream input(leaderFile);
        string record;
        while (getline(input, record)) {
            leader leader(record);
            data.push_back(leader);
        }
    }

    string toString() {
        string buildString = "";
        for (int i = 0; i < data.size(); i++) {
            buildString += to_string(i + 1) + ".\t" + data.at(i).time + "\t" + data.at(i).name + "\n\n";
        }
        return buildString;
    }

    void writeToFile() {
        ofstream output("files/leaderboard.txt", ios::out | ios::trunc);
        for (int i = 0; i < data.size(); i++) {
            output<<data.at(i).time<<", "<<data.at(i).name << endl;
        }
    }

    vector<leader> addToLeader(string name, string time) {
        readData();
        leader newLeader(time + ", " + name);
        bool inserted = false;

        int newRecordIndex = -1;
        for (int i = 0; i < data.size(); i++) {
            if (time < data.at(i).time) 
            { 
                newRecordIndex = i;
                data.insert(data.begin() + i, newLeader);
                inserted = true;
                break;
            }
        }

        if (data.size() > 5) {
            data.pop_back(); 
        }

        writeToFile();
        if(newRecordIndex != -1) {
            data.at(newRecordIndex).name = name + "*";
        } 
        return data;
    }

    void leaderWindow()
    {
        sf::RenderWindow leaderWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

        sf::Text title;
        title.setFont(font);
        title.setString("LEADERBOARD");
        title.setCharacterSize(20);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width / 2.0f,
                        titleRect.top + titleRect.height / 2.0f);
        title.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 120));

        sf::Text leaders;
        leaders.setFont(font);
        leaders.setString(toString());
        leaders.setCharacterSize(18);
        leaders.setFillColor(sf::Color::White);
        leaders.setStyle(sf::Text::Bold);
        sf::FloatRect leaderRect = leaders.getLocalBounds();
        leaders.setOrigin(leaderRect.left + leaderRect.width / 2.0f,
                        leaderRect.top + leaderRect.height / 2.0f);
        leaders.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 20));

        while (leaderWindow.isOpen()) {
            sf::Event event;
            while (leaderWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                {
                    leaderWindow.close();
                    return;
                }
            }
            leaderWindow.clear(sf::Color::Blue);
            leaderWindow.draw(title);
            leaderWindow.draw(leaders);
            leaderWindow.display();
        }
    }
};
#endif //LEADERBOARD_H
