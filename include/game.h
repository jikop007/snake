#pragma once
#include "snake.h"
#include "apple.h"
#include <thread>
#include <atomic>

using namespace std;

class Game {
private:
    int width, height;
    int score;

    bool gameOver;
    atomic<bool> running;
    
    Snake snake;
    Apple apple;

    thread inputThread;

    void draw();
    void input();
    void logic();

public:
    Game(int w, int h);

    void run();
};