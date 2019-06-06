#ifndef PINKY_H
#define PINKY_H
#include "Ghost.h"

class Pinky: public Ghost{
public:
    Pinky();
    Pinky(Game *);
    virtual void normalMode();
};

#endif // PINKY_H
