#include "Clyde.h"
#include <QBrush>
#include "game.h"
#include <cmath>

Clyde::Clyde()
{

}

Clyde::Clyde(Game *g): Ghost (g){
    speed = 0.1;
    this->setRect(-8,-8,35,35);
    color = new QBrush(QColor(255,140,0));
    this->setBrush(*color);
    dir = UP;
    setPos(game->getTileXY(2,29)->pos());
    mode = N;
    currentTile = QPoint(0,0);
    basePos = pos().toPoint();
}

void Clyde::normalMode(){
    destPos = QPoint(int (pacmanPoint.x()), int (pacmanPoint.y()));
    if(int (round(std::sqrt(pow(destPos.x() - x(),2) + pow(destPos.y() - y(),2)))) <= 4*GRID_SCALE)
        destPos = basePos;
    //currentTile = QPoint(0,0);
    update();
    findPath();
    //printPath();
    followPath();
}
