//
// Created by sophi on 4/18/2025.
//
#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class timer
{
    bool paused = false;
    bool started = false;
    bool ended = false;  
    chrono::high_resolution_clock::time_point start_time;
    chrono::seconds elapsed_time{0};

public:
    timer() {}

    bool isStarted() const
    {
        return started;
    }

    bool isEnded() const
    {
        return ended;
    }

    bool isPaused() const
    {
        return paused;
    }

    void start()
    {
        if (!started)
        {
            // chrono::high_resolution_clock::now(); is the current time from clock
            start_time = chrono::high_resolution_clock::now();
            paused = false;
            started = true;
        }
    }

    void pause()
    {
        // if it's not paused
        if (started && !paused)
        {
            elapsed_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time + elapsed_time);
            paused = true;
        }
    }

    void resume()
    {
        if (started && paused)
        {
            start_time = chrono::high_resolution_clock::now();
            paused = false;
        }
    }

    void reset()
    {
        elapsed_time = chrono::seconds(0);
        started = false;
        paused = false;
        ended = false;
    }

    void end()
    {
        if (started && !ended)
        {
            elapsed_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time + elapsed_time);
            ended = true;
        }
    }

    int get_elapsed_time() const
    {
        auto now = std::chrono::high_resolution_clock::now();

        chrono::seconds total_elapsed = elapsed_time;
        if (started && !ended && !paused)
        {
            total_elapsed = chrono::duration_cast<chrono::seconds>(now - start_time + elapsed_time);
        }
   
        return total_elapsed.count();
    }
};
#endif // TIMER_H
