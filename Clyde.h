#ifndef CLYDE_H
#define CLYDE_H
#include "Ghost.h"

class Clyde: public Ghost{
public:
    Clyde();
    Clyde(Game *);
    virtual void normalMode();
};

#endif // CLYDE_H
