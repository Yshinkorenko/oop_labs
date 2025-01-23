#ifndef BASE_UNIVERSE_H
#define BASE_UNIVERSE_H

#include <vector>
#include <iostream>

class BaseUniverse {
protected:
    int width;
    int height;
    std::vector<bool> cells; 

public:
    virtual ~BaseUniverse() = default;

    BaseUniverse(int w, int h)
        : width(w), height(h), cells(w * h, false) {}

    bool isAlive(int x, int y) const;
    void setAlive(int x, int y);
    void setDead(int x, int y);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    virtual int countNeighbors(int x, int y) const = 0;

    virtual void print(std::ostream& os) const;

    
    void resize(int w, int h);
};

#endif 
