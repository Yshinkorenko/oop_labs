#include "ToroidalUniverse.h"

int ToroidalUniverse::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;
            if (isAlive(nx, ny)) {
                ++count;
            }
        }
    }
    return count;
}
