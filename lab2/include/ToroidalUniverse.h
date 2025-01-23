#ifndef TOROIDAL_UNIVERSE_H
#define TOROIDAL_UNIVERSE_H

#include "BaseUniverse.h"

class ToroidalUniverse : public BaseUniverse {
public:
    ToroidalUniverse(int w, int h)
        : BaseUniverse(w, h) {}

    int countNeighbors(int x, int y) const override;
};

#endif 
