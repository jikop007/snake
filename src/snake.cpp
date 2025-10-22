#include <cmath>
#include "snake.h"

using namespace std;

Snake::Snake(int startX, int startY)
    : dir(Direction::stop)
{
    for (int i = 0; i < 5; ++i)
        body.push_back({ startX - i, startY });
}

void Snake::setDirection(Direction d) {
    if ((dir == Direction::up && d == Direction::down) ||
        (dir == Direction::down && d == Direction::up) ||
        (dir == Direction::left && d == Direction::right) ||
        (dir == Direction::right && d == Direction::left))
        return;

    dir = d;
}

void Snake::move() {
    if (dir == Direction::stop) return;

    int x = body.front().first;
    int y = body.front().second;

    switch (dir) {
        case Direction::up:    y--; break;
        case Direction::down:  y++; break;
        case Direction::left:  x--; break;
        case Direction::right: x++; break;
        default: break;
    }

    body.push_front({ x, y });
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
}

bool Snake::isAt(int x, int y) const {
    for (auto &segment : body)
        if (segment.first == x && segment.second == y)
            return true;
    return false;
}

bool Snake::hasCollided(int width, int height) const {
    int headX = getHeadX();
    int headY = getHeadY();

    if (headX <= 0 || headY <= 0 || headX >= width - 1 || headY >= height - 1)
        return true;

    for (size_t i = 1; i < body.size(); ++i)
        if (body[i] == body[0])
            return true;

    return false;
}

int Snake::getHeadX() const { return body.front().first; }
int Snake::getHeadY() const { return body.front().second; }

int Snake::getSpeed() const {
    int length = static_cast<int>(body.size());
    if (length <= 10) return 600;
    if (length >= 30) return 300;

    double t = 600 - (length - 10) * (300.0 / 20.0);
    return static_cast<int>(t);
}
