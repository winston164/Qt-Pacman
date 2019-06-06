#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include <QGraphicsEllipseItem>
enum direction {UP, DOWN, RIGHT, LEFT};

class Game;
class GameEntity: public QGraphicsEllipseItem{
public:
    GameEntity();
    GameEntity(Game *);
    virtual void move();
    virtual void update();
    void changeDir(direction);
    void changeSpeed(double);
    virtual ~GameEntity();
protected:
    Game * game;
    QBrush * color;
    direction dir;
    double speed;
};

#endif // GAMEENTITY_H
