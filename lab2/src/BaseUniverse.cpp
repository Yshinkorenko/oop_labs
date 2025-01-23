#include "BaseUniverse.h"
#include <stdexcept>
#include <iomanip>

bool BaseUniverse::isAlive(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return cells[y * width + x];
}

void BaseUniverse::setAlive(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return; 
    }
    cells[y * width + x] = true;
}

void BaseUniverse::setDead(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    cells[y * width + x] = false;
}

void BaseUniverse::print(std::ostream& os) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            os << (isAlive(x, y) ? "*" : ".");
        }
        os << "\n";
    }
}

void BaseUniverse::resize(int w, int h) {
    width = w;
    height = h;
    cells.assign(w * h, false);
}
