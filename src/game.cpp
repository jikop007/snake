#include <iostream>
#include <thread>
#include <unistd.h>
#include <ncurses.h>
#include "game.h"

using namespace std;

Game::Game(int w, int h)
    : width(w), height(h), score(0), gameOver(false), running(true),
      snake(w / 2, h / 2), apple(w, h) {}

void Game::run() {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    inputThread = thread(&Game::input, this);

    while (!gameOver) {
        draw();
        logic();
        usleep(snake.getSpeed() * 1000);
    }

    running = false;
    inputThread.join();

    draw();

    mvprintw(height + 1, 0, "Game Over! Final Score: %d", score);
    mvprintw(height + 2, 0, "Press any key to exit");
    refresh();

    nodelay(stdscr, FALSE);
    getch();

    endwin();
}

void Game::input() {
    while (running) {
        int ch = getch();
        if (ch != ERR) {
            switch (ch) {
                case 'w': snake.setDirection(Direction::up); break;
                case 's': snake.setDirection(Direction::down); break;
                case 'a': snake.setDirection(Direction::left); break;
                case 'd': snake.setDirection(Direction::right); break;
                case 27:
                    gameOver = true;
                    running = false;
                    break;
            }
        }
        usleep(1000);
    }
}

void Game::draw() {
    clear();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                mvaddch(y, x, 'H');
            else if (snake.isAt(x, y))
                mvaddch(y, x, 'O');
            else if (apple.isAt(x, y))
                mvaddch(y, x, 'A');
        }
    }

    mvprintw(height, 0, "Score: %d", score);
    refresh();
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
