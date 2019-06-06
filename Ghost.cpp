#include "Ghost.h"
#include "game.h"
#include <QList>
#include <cmath>
#include <QDebug>

Ghost::Ghost()
{

}

Ghost::Ghost(Game *g): GameEntity (g), pathPoints(){
    speed = 0.1;
    this->setRect(-8,-8,35,35);
    color = new QBrush(Qt::red);
    this->setBrush(*color);
    dir = RIGHT;
    mode = N;
    currentTile = QPoint(0,0);
    basePos = pos().toPoint();
    game->addItem(this);
}

void Ghost::setMode(Mode m){
    mode = m;
    if(mode == SC){
        path.clear();
        printPath();
        this->setBrush(QBrush(Qt::blue));
        if(dir == UP) dir = DOWN;
        else
        if(dir == DOWN) dir = UP;
        else
        if(dir == RIGHT) dir = LEFT;
        else
        if(dir == LEFT) dir = RIGHT;
        currentTile = QPoint(0,0);
    }else {
        findPath();
        printPath();
        this->setBrush(*color);
    }


}

void Ghost::update(){
    //don't interrupt teleport animation
    if(((int (x()) >= GRID_W*GRID_SCALE - 20) || int (x()) <= 0)){
        return;
    }

    //Find pacman point if at specific tile and not out of bounds
    QPointF g = game->entities.at(0)->pos();
    if( !((int (g.x()) >= GRID_W*GRID_SCALE - 20) || int (g.x()) <= 0)
            && (int (g.x()))%GRID_SCALE == 0 && ((int (g.y())))%GRID_SCALE == 0){
        pacmanPoint = g;
    }

    if((int (x()))%GRID_SCALE == 0 && ((int (y())))%GRID_SCALE == 0){
        if(currentTile == QPoint(int (x()),int (y()))){
            return;
        }else {
            currentTile = QPoint(int (x()),int (y()));
        }

        if(mode == N){
            this->normalMode();
        }

        if(mode == S){
            destPos = basePos;
            findPath();
            followPath();
        }
        if(mode == SC){
            if(game->getTileXY((int (x()))/GRID_SCALE,
                               ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isNode()){
                std::vector<QPoint> neighbors;
                QPoint auxP;
                auxP = findNeighbor(UP,pos().toPoint());
                if(!auxP.isNull() && dir != DOWN)
                    neighbors.push_back(auxP);
                auxP = findNeighbor(DOWN,pos().toPoint());
                if(!auxP.isNull() && dir != UP)
                    neighbors.push_back(auxP);
                auxP = findNeighbor(RIGHT,pos().toPoint());
                if(!auxP.isNull() && dir != LEFT)
                    neighbors.push_back(auxP);
                auxP = findNeighbor(LEFT,pos().toPoint());
                if(!auxP.isNull() && dir != RIGHT)
                    neighbors.push_back(auxP);
                srand(time(NULL));
                unsigned r = (unsigned (rand()))%neighbors.size();
                destPos = neighbors.at(r);
                findPath();
                followPath();
            }
        }
    }
}

void Ghost::normalMode(){
    destPos = QPoint(int (pacmanPoint.x()), int (pacmanPoint.y()));
    findPath();
    printPath();
    followPath();
}

Ghost::~Ghost(){

}

//finds the closest path from the current position to certain point
//only call when at a certain tile position and the destination position is stablished
void Ghost::findPath(){
    //structure for A*
    struct node{
        QPoint pos;
        int weight;
        int netWeight;
        struct node *prev;
    };

    //one queue for the elements to search
    QList<struct node *> priQueue;
    std::vector<struct node *> allNodes;
    std::vector<QPoint> neighbors;

    struct node * first = new struct node;
    *first = {pos().toPoint(), 0, 0, nullptr};
    allNodes.push_back(first);
    priQueue.push_back(first);


    while (priQueue.first()->pos != destPos) {
        //find neighbor points of the first elemnt
        struct node * first = priQueue.first();
        if(!priQueue.empty())
        priQueue.pop_front();
        neighbors.clear();
        QPoint auxP;
        auxP = findNeighbor(UP,first->pos);
        if(!auxP.isNull() && (first->prev != nullptr || dir != DOWN))
            neighbors.push_back(auxP);
        auxP = findNeighbor(DOWN,first->pos);
        if(!auxP.isNull() && (first->prev != nullptr || dir != UP))
            neighbors.push_back(auxP);
        auxP = findNeighbor(RIGHT,first->pos);
        if(!auxP.isNull() && (first->prev != nullptr || dir != LEFT))
            neighbors.push_back(auxP);
        auxP = findNeighbor(LEFT,first->pos);
        if(!auxP.isNull() && (first->prev != nullptr || dir != RIGHT))
            neighbors.push_back(auxP);

        //process all neighbors and add to priority queue
        for (unsigned i = 0; i < neighbors.size(); i++) {

            //if it is the original node or the position is not the same as prev node then..
            if(first->prev == nullptr ||
                    first->prev->pos != neighbors.at(i)){

                //create node from current position
                struct node *auxN = new struct node;
                *auxN = {neighbors.at(i), first->weight+1, 0, first};
                auxN->netWeight = auxN->weight +
                       int (round(std::sqrt(pow(destPos.x() - neighbors.at(i).x(),2) + pow(destPos.y() - neighbors.at(i).y(),2))));
                allNodes.push_back(auxN);

                //place node in priority queue depending on its net weight
                int auxPos = 0;
                int queueS = priQueue.size();
                while (auxPos < queueS && auxN->netWeight > priQueue.at(auxPos)->netWeight) auxPos++;
                priQueue.insert(auxPos, auxN);
            }
        }
        //repeat until the first element in the queue is the destination node
    }
    //at this point the first element of the queue is the destination node
    //the nodes are linked backwads so to make the path list we have to build it backwards

    struct node *nodeP = priQueue.first();
    if(!path.empty())
    path.clear();
    while (nodeP->prev != nullptr) {
        path.push_front(nodeP->pos);
        nodeP = nodeP->prev;
    }
    for(unsigned i = 0; i < allNodes.size(); i++) delete allNodes.at(i);

}

//Call when inside specific tile
void Ghost::followPath(){
    if(path.empty() && !game->getTileXY((int (x()))/GRID_SCALE,
                                           ((int (y()))-SCORE_PADDING)/GRID_SCALE)->isNode()){
        return;
    }else
    if(path.empty()){
        std::vector<QPoint> neighbors;
        QPoint auxP;
        auxP = findNeighbor(UP,pos().toPoint());
        if(!auxP.isNull() && dir != DOWN)
            neighbors.push_back(auxP);
        auxP = findNeighbor(DOWN,pos().toPoint());
        if(!auxP.isNull() && dir != UP)
            neighbors.push_back(auxP);
        auxP = findNeighbor(RIGHT,pos().toPoint());
        if(!auxP.isNull() && dir != LEFT)
            neighbors.push_back(auxP);
        auxP = findNeighbor(LEFT,pos().toPoint());
        if(!auxP.isNull() && dir != RIGHT)
            neighbors.push_back(auxP);
        unsigned r = (unsigned (rand()))%neighbors.size();
        path.push_back(neighbors.at(r));
    }

    if(int (x()) < path.first().x()){
        dir = RIGHT;
    }
    if(int (x()) > path.first().x()){
        dir = LEFT;
    }
    if(int (y()) < path.first().y()){
        dir = DOWN;
    }
    if(int (y()) > path.first().y()){
        dir = UP;
    }
    if(!path.isEmpty())
    path.pop_front();
}

void Ghost::printPath(){
    for (int i  = 0; i < pathPoints.size(); i++) {
        game->removeItem(pathPoints.at(i));
        delete pathPoints.at(i);
    }
    pathPoints.clear();

    QGraphicsEllipseItem *el;
    for (int i = 0; i < path.size();i++) {
        el = new QGraphicsEllipseItem(0,0,10,10);
        el->setPos(path.at(i));
        el->setBrush(*color);
        game->addItem(el);
        pathPoints.push_back(el);
    }
}

QPoint Ghost::findNeighbor(direction dir, const QPoint &p){
    Tile *t;
    if(dir == UP){
        t = game->getTileXY(p.x()/GRID_SCALE,
                        (p.y()-SCORE_PADDING)/GRID_SCALE - 1);
    }
    if(dir == DOWN){
        t = game->getTileXY(p.x()/GRID_SCALE,
                        (p.y()-SCORE_PADDING)/GRID_SCALE + 1);
    }
    if(dir == RIGHT){
        t = game->getTileXY(p.x()/GRID_SCALE + 1,
                        (p.y()-SCORE_PADDING)/GRID_SCALE);
    }
    if(dir == LEFT){
        t = game->getTileXY(p.x()/GRID_SCALE - 1,
                        (p.y()-SCORE_PADDING)/GRID_SCALE);
    }
    if(t->isWall()){
        return QPoint(0,0);
    }

    return t->pos().toPoint();
}

