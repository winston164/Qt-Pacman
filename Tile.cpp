#include "Tile.h"
#include  "game.h"
#include <QPen>

Tile::Tile(){

}

Tile::Tile(Game *g){
        //blank tile

        game = g;
        Eaten = true;
        Wall = false;
        PowerPallet = false;
        Node = false;
}

void Tile::setPallet(bool power){
    Eaten = false;
    if(power){
        PowerPallet =true;
        pallet = new QGraphicsEllipseItem(0,0,20,20);
    }else{
        pallet = new QGraphicsEllipseItem(6,6,6,6);
    }
        pallet->setBrush(Qt::white);
        pallet->setPen(QPen(Qt::white));
        pallet->setPos(this->pos());
        game->addItem(pallet);
}

void Tile::setNode(QString s){
    Node = true;
    //setRect(0,0,20,20);
    //setBrush(Qt::green);
    //game->addItem(this);
    //QGraphicsTextItem * text = new QGraphicsTextItem(s);
    //text->setFont(QFont("Arial"));
    //text->setPos(x(),y());
    //game->addItem(text);
}

void Tile::eat(){
    if(Eaten || Wall){
        return;
    }
    if(PowerPallet){
        game->addPoints(50, true);
        game->powerPallet();
    }else {
        game->addPoints(10, true);
    }
        game->removeItem(pallet);
        delete pallet;
        Eaten = true;
}

void Tile::setWall(){
    Wall = true;
}

bool Tile::isWall(){
    return Wall;
}

bool Tile::isNode(){
    return Node;
}


