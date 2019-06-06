#ifndef INKY_H
#define INKY_H
#include "Ghost.h"

class Inky: public Ghost{
public:
    Inky();
    Inky(Game*);
    virtual void normalMode();
};

#endif // INKY_H
