#include "Inky.h"
#include <QBrush>
#include <cmath>
#include "game.h"


Inky::Inky()
{

}

Inky::Inky(Game *g): Ghost (g){
    speed = 0.1;
    this->setRect(-8,-8,35,35);
    color = new QBrush(QColor(0,206,209));
    this->setBrush(*color);
    dir = LEFT;
    setPos(game->getTileXY(26,2)->pos());
    mode = N;
    currentTile = QPoint(0,0);
    basePos = pos().toPoint();
}

void Inky::normalMode(){
    destPos = QPoint(int (pacmanPoint.x()), int (pacmanPoint.y()));
    if(int (round(std::sqrt(pow(destPos.x() - x(),2) + pow(destPos.y() - y(),2)))) <= 4*GRID_SCALE)
        destPos = basePos;
    //currentTile = QPoint(0,0);
    update();
    findPath();
    //printPath();
    followPath();
}
