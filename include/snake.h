#pragma once
#include <deque>
#include "Direction.h"

class Snake {
private:
    std::deque<std::pair<int, int>> body;
    Direction dir;

public:
    Snake(int startX, int startY);

    void move();
    void grow();
    void setDirection(Direction d);

    bool isAt(int x, int y) const;
    bool hasCollided(int width, int height) const;

    int getHeadX() const;
    int getHeadY() const;
    int getSpeed() const;
    int getTailX() const { return body.back().first; }
    int getTailY() const { return body.back().second; }
};
