#include "Pinky.h"
#include <QBrush>
#include "game.h"
#include <QColor>
#include <QDebug>

Pinky::Pinky()
{

}

Pinky::Pinky(Game *g): Ghost (g){
    speed = 0.1;
    this->setRect(-8,-8,35,35);
    color = new QBrush(QColor(254,127,156));
    this->setBrush(*color);
    dir = LEFT;
    setPos(game->getTileXY(26,29)->pos());
    mode = N;
    currentTile = QPoint(0,0);
    basePos = pos().toPoint();
}

void Pinky::normalMode(){
    destPos = QPoint(int (pacmanPoint.x()), int (pacmanPoint.y()));
    int x = (int (destPos.x()))/GRID_SCALE;
    int y = ((int (destPos.y()))-SCORE_PADDING)/GRID_SCALE;
    if(pacmanDir == UP){
        for(int i = 1; i <= 4; i++)
        if(destPos.y() - i*GRID_SCALE > 0 && destPos.y() - i*GRID_SCALE < GRID_H*GRID_SCALE+SCORE_PADDING &&
                !game->getTileXY(x,y - i)->isWall()){
            destPos = game->getTileXY(x,y - i)->pos().toPoint();
        }
    }
    if(pacmanDir == DOWN){
        for(int i = 1; i <= 4; i++){
        if(destPos.y() + i*GRID_SCALE > 0 && destPos.y() + i*GRID_SCALE < GRID_H*GRID_SCALE+SCORE_PADDING &&
                !game->getTileXY(x,y + i)->isWall()){
            destPos = game->getTileXY(x,y + i)->pos().toPoint();
        }}
    }
    if(pacmanDir == RIGHT){
        for(int i = 1; i <= 4; i++)
        if(destPos.x() + i*GRID_SCALE > 0 && destPos.x() + i*GRID_SCALE < GRID_W*GRID_SCALE &&
                !game->getTileXY(x + i,y)->isWall()){
            destPos = game->getTileXY(x + i,y)->pos().toPoint();
        }
    }
    if(pacmanDir == LEFT){
        for(int i = 1; i <= 4; i++)
        if(destPos.x() - i*GRID_SCALE > 0 && destPos.x() - i*GRID_SCALE < GRID_W*GRID_SCALE &&
                !game->getTileXY(x - i,y)->isWall()){
            destPos = game->getTileXY(x - i, y)->pos().toPoint();
        }
    }

    findPath();
    //printPath();
    followPath();
}
