#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

static void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

Game::Game(int w, int h)
    : width(w), height(h), score(0), gameOver(false), running(true),
      snake(w / 2, h / 2), apple(w, h) {}

void Game::run() {
    system("cls");
    hideCursor();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                std::cout << "H";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }

    setCursorPosition(apple.getX(), apple.getY());
    std::cout << "A";

    setCursorPosition(0, height);
    std::cout << "Score: " << score;

    inputThread = std::thread(&Game::inputLoop, this);

    while (!gameOver) {
        logic();
        Sleep(snake.getSpeed());
    }

    running = false;
    inputThread.join();
    setCursorPosition(0, height + 2);
    std::cout << "\nGame Over! Final score: " << score << std::endl;
}

void Game::inputLoop() {
    while (running) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'w': snake.setDirection(Direction::UP); break;
                case 's': snake.setDirection(Direction::DOWN); break;
                case 'a': snake.setDirection(Direction::LEFT); break;
                case 'd': snake.setDirection(Direction::RIGHT); break;
                case 27: gameOver = true; running = false; break;
            }
        }
        Sleep(10);
    }
}

void Game::logic() {
    int oldTailX = snake.getTailX();
    int oldTailY = snake.getTailY();

    snake.move();

    int headX = snake.getHeadX();
    int headY = snake.getHeadY();

    setCursorPosition(headX, headY);
    std::cout << "O";

    setCursorPosition(oldTailX, oldTailY);
    std::cout << " ";

    if (snake.getHeadX() == apple.getX() && snake.getHeadY() == apple.getY()) {
        snake.grow();
        apple.respawn(width, height);
        setCursorPosition(apple.getX(), apple.getY());
        std::cout << "A";
        score += 1;
        setCursorPosition(7, height);
        std::cout << score << " ";
    }

    if (snake.hasCollided(width, height))
        gameOver = true;
}