#pragma once
#include <deque>
#include "direction.h"

using namespace std;

class Snake {
private:
    deque<pair<int, int>> body;
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
};
