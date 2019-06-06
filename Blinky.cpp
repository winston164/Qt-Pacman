#include "Blinky.h"
#include "game.h"
#include <QBrush>

Blinky::Blinky()
{

}

Blinky::Blinky(Game *g): Ghost (g){
    speed = 0.1;
    this->setRect(-8,-8,35,35);
    color = new QBrush(Qt::red);
    this->setBrush(*color);
    dir = RIGHT;
    setPos(game->getTileXY(1,1)->pos());
    mode = N;
    currentTile = QPoint(0,0);
    basePos = pos().toPoint();
}

void Blinky::normalMode(){
    destPos = QPoint(int (pacmanPoint.x()), int (pacmanPoint.y()));
    findPath();
    //printPath();
    followPath();
}
