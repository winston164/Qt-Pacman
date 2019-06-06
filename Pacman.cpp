#include "Pacman.h"
#include "game.h"
#include "Ghost.h"
#include <QKeyEvent>
#include <QDebug>

Pacman::Pacman(){

}

Pacman::Pacman(Game *g): GameEntity(g){
    //initial conditins
    speed = 0.15;
    ogSpeed = speed;
    //dir = LEFT;
    dir = RIGHT;
    for (int i  = 0; i < 4; i++)
        keyFlags[i] = 0;


    //set fous
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    //Drawing details
    this->setRect(-8,-8,35,35);
    this->setPos(game->getTileXY(13,23)->pos());
    this->setBrush(Qt::yellow);
    this->setPen(QPen(Qt::yellow));
    game->addItem(this);
}

void Pacman::update(){

    //if out of the map don't interrupt animation
    if((int (x()) >= GRID_W*GRID_SCALE - 20) || int (x()) <= 0){
        return;
    }

    //collition with enemy detection
    for (unsigned i = 1; i < game->entities.size(); i++) {
        QPointF ePos = game->entities.at(i)->pos();
        if((int (ePos.x())) == (int (x()))){
            int d = (int (ePos.y())) - (int (y()));
            if(d > -33 && d < 33){
                if(game->power){
                    game->entities.at(i)->setPos(
                                game->getTileXY(13,11)->pos());
                    game->entities.at(i)->changeDir(LEFT);
                    game->entities.at(i)->update();
                    game->addPoints(200,false);
                }
                else
                game->GameOver();
                return;
            }
        }
        if((int (ePos.y())) == (int (y()))){
            int d = (int (ePos.x())) - (int (x()));
            if(d > -33 && d < 33){
                if(game->power){
                    game->entities.at(i)->setPos(
                                game->getTileXY(13,11)->pos());
                    game->entities.at(i)->changeDir(LEFT);
                    game->entities.at(i)->update();
                    game->addPoints(200,false);

                }
                else
                game->GameOver();
                return;
            }
        }
    }

    //Eating Logic
    if(dir == UP && ((int (y())) - 15)%GRID_SCALE == 0)
        game->getTileXY((int (x()))/GRID_SCALE,
                                          ((int (y())-15)-SCORE_PADDING)/GRID_SCALE)->eat();
    if(dir == DOWN && ((int (y())) + 15)%GRID_SCALE == 0)
        game->getTileXY((int (x()))/GRID_SCALE,
                                          ((int (y())+15)-SCORE_PADDING)/GRID_SCALE)->eat();
    if(dir == RIGHT && ((int (x())) + 15)%GRID_SCALE == 0)
        game->getTileXY((int (x()) + 15)/GRID_SCALE,
                                          ((int (y()))-SCORE_PADDING)/GRID_SCALE)->eat();
    if(dir == LEFT && ((int (x())) - 15)%GRID_SCALE == 0)
        game->getTileXY((int (x()) - 15)/GRID_SCALE,
                                          ((int (y()))-SCORE_PADDING)/GRID_SCALE)->eat();

    //Invert directiron logic
    if(dir == UP && keyFlags[1]) dir = DOWN;
    if(dir == DOWN && keyFlags[0]) dir = UP;
    if(dir == RIGHT && keyFlags[3]) dir = LEFT;
    if(dir == LEFT && keyFlags[2]) dir = RIGHT;


    //if position matches a tile
    if( (int (x()))%GRID_SCALE == 0 && ((int (y())))%GRID_SCALE == 0){

        //Changing directions logic
        if(keyFlags[0] &&
                !(game->getTileXY((int (x()))/GRID_SCALE,
                                  ((int (y()))-SCORE_PADDING)/GRID_SCALE - 1)->isWall()))
            dir = UP;
        if(keyFlags[1] &&
                !(game->getTileXY((int (x()))/GRID_SCALE,
                                  ((int (y()))-SCORE_PADDING)/GRID_SCALE + 1)->isWall()))
            dir = DOWN;
        if(keyFlags[2] &&
                !(game->getTileXY((int (x()))/GRID_SCALE + 1,
                                  ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isWall()))
            dir = RIGHT;
        if(keyFlags[3] &&
                !(game->getTileXY((int (x()))/GRID_SCALE - 1,
                                  ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isWall()))
            dir = LEFT;



        //stop at walls logic
        speed = ogSpeed;
        if(dir == UP &&
                game->getTileXY((int (x()))/GRID_SCALE,
                                ((int (y()))-SCORE_PADDING)/GRID_SCALE - 1)->isWall()){
            speed = 0;
        }
        if(dir == DOWN &&
                game->getTileXY((int (x()))/GRID_SCALE,
                                ((int (y()))-SCORE_PADDING)/GRID_SCALE + 1)->isWall()){
            speed = 0;
        }
        if(int (x()) > 0)
            if(dir == LEFT &&
                    game->getTileXY((int (x()))/GRID_SCALE - 1,
                                    ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isWall()){
                speed = 0;
        }
        if(int (x()) < GRID_W * GRID_SCALE)
            if(dir == RIGHT &&
                    game->getTileXY((int (x()))/GRID_SCALE + 1,
                                    ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isWall()){
                speed = 0;
        }
    }
}

Pacman::~Pacman(){

}

void Pacman::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left){
        keyFlags[3] = true;
    }
    if(event->key() == Qt::Key_Right){
        keyFlags[2] = true;
    }
    if(event->key() == Qt::Key_Up){
        keyFlags[0] = true;
    }
    if(event->key() == Qt::Key_Down){
        keyFlags[1] = true;
    }
}

void Pacman::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left){
        keyFlags[3] = false;
    }
    if(event->key() == Qt::Key_Right){
        keyFlags[2] = false;
    }
    if(event->key() == Qt::Key_Up){
        keyFlags[0] = false;
    }
    if(event->key() == Qt::Key_Down){
        keyFlags[1] = false;
    }
}


