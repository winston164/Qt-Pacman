#ifndef BLINKY_H
#define BLINKY_H
#include "Ghost.h"

class Blinky: public Ghost{
public:
    Blinky();
    Blinky(Game *);
    virtual void normalMode();
};

#endif // BLINKY_H
