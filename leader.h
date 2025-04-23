//
// Created by sophi on 4/21/2025.
//

#ifndef LEADER_H
#define LEADER_H
#include <string>

struct leader {
    string name;
    string time;

    leader(){}
    leader(string n, string t) : name(n) , time(t) {}

    leader(string data) {
        auto commaPos = data.find(',');
        name = data.substr(commaPos + 2);
        time = data.substr(0, commaPos);
    }
};

#endif //LEADER_H
