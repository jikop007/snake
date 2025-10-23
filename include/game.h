#pragma once
#include "Snake.h"
#include "Apple.h"
#include <thread>
#include <atomic>

class Game {
private:
    int width, height;
    int score;
    bool gameOver;
    std::atomic<bool> running;

    Snake snake;
    Apple apple;

    std::thread inputThread;

    void draw();
    void logic();
    void inputLoop();

public:
    Game(int w, int h);
    void run();
};
