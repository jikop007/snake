#include "Apple.h"
#include <ctime>

Apple::Apple(int w, int h) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    respawn(w, h);
}

void Apple::respawn(int w, int h) {
    x = rand() % (w - 2) + 1;
    y = rand() % (h - 2) + 1;
}

int Apple::getX() const { return x; }
int Apple::getY() const { return y; }
