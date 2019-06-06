#ifndef GHOST_H
#define GHOST_H
#include "GameEntity.h"
#include "Tile.h"

enum Mode{N,S,SC};
//modes: N(normal) S(scatter) SC(Scared)

class Ghost: public GameEntity{
public:
    Ghost();
    Ghost(Game *);
    void setMode(Mode);
    virtual void update();
    virtual void normalMode();
    virtual ~Ghost();
    void printPath();


protected:
    void findPath();
    void followPath();
    QList<QGraphicsEllipseItem *> pathPoints;
    QPoint findNeighbor(direction dir, const QPoint &p);
    QPoint destPos;
    QPoint basePos;
    QPoint currentTile;
    QPointF pacmanPoint;
    QList<QPoint> path;
    Mode mode;
};

#endif // GHOST_H
