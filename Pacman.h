#ifndef PACMAN_H
#define PACMAN_H
#include "GameEntity.h"


class Pacman: public GameEntity{
public:
    Pacman();
    Pacman(Game *);
    virtual void update();
    virtual ~Pacman();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
private:
    bool keyFlags[4];
    double ogSpeed;
};

#endif // PACMAN_H
