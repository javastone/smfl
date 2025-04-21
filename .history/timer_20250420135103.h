//
// Created by sophi on 4/18/2025.
//
#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class timer {
    bool timing = false;
    bool paused = false;
    bool started = false;  // Flag to indicate if the timer has started. 
    chrono::high_resolution_clock::time_point start_time;
    chrono::seconds elapsed_time{0};
public:
    timer() {}

    bool isStarted() const {
        return started;
    }

    bool isPaused() const {
        return paused;
    }

    void start() {
        //if it's not timing
        if (!started) {
            //chrono::high_resolution_clock::now(); is the current time from clock
            start_time = chrono::high_resolution_clock::now();
            elapsed_time = chrono::seconds(0);
            timing = true;
            paused = false;
            started = true;
        }
    }

    void pause() {
        //if it's not paused
        if (timing && !paused) {
            elapsed_time = chrono::duration_cast<chrono::seconds>(start_time - chrono::high_resolution_clock::now() + elapsed_time);
            timing = false;
            paused = true;
        }
    }

    void resume() {
        if (!timing && paused) {
            start_time = chrono::high_resolution_clock::now();
            timing = true;
            paused = false;
        }
    }

    void reset() {
        elapsed_time = chrono::seconds(0);
        started = false;
        timing = false;
        paused = false;
    }

    pair<int, int> get_elapsed_time() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = elapsed_time;
        if (timing) {
            elapsed += chrono::duration_cast<chrono::seconds>(now - start_time);
        }

        auto total_seconds = elapsed.count();
        int minutes = chrono::duration_cast<chrono::minutes>(elapsed).count();
        int seconds = total_seconds % 60;

        cout << minutes << " minutes " << seconds << " seconds" << endl;
        return make_pair(minutes, seconds);
    }
};
#endif //TIMER_H

