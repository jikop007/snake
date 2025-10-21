#pragma once
#include <cstdlib>

class Apple {
private:
    int x, y;

public:
    Apple(int w, int h);

    void respawn(int w, int h);

    bool isAt(int x, int y) const {
        return this->x == x && this->y == y;
    }


    int getX() const;
    int getY() const;
};
