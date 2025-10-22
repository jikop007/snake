#include <iostream>
#include <conio.h>
#include <windows.h>
#include "game.h"

using namespace std;

Game::Game(int w, int h)
    : width(w), height(h), score(0), gameOver(false), running(true),
      snake(w / 2, h / 2), apple(w, h) {}

void Game::run() {
    inputThread = thread(&Game::input, this);

    while (!gameOver) {
        draw();
        logic();
        Sleep(snake.getSpeed());
    }

    running = false;
    inputThread.join();
    cout << "\nGame Over! Score: " << score << endl;
}

void Game::input() {
    while (running) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'w': snake.setDirection(Direction::up); break;
                case 's': snake.setDirection(Direction::down); break;
                case 'a': snake.setDirection(Direction::left); break;
                case 'd': snake.setDirection(Direction::right); break;
                case 27: gameOver = true; running = false; break;
            }
        }
        Sleep(1);
    }
}

void Game::draw() {
    system("cls");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                cout << "H";
            else if (snake.isAt(x, y))
                cout << "O";
            else if (apple.isAt(x, y))
                cout << "A";
            else
                cout << " ";
        }
        cout << "\n";
    }
    cout << "Score: " << score << endl;
}

void Game::logic() {
    snake.move();

    if (snake.getHeadX() == apple.getX() && snake.getHeadY() == apple.getY()) {
        snake.grow();
        apple.respawn(width, height);
        score += 1;
    }

    if (snake.hasCollided(width, height))
        gameOver = true;
}