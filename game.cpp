#include "game.h"
#include "centipede.h"
#include "Blaster.h"

Game::Game(QWidget *parent)
{
    // Set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    scene->setBackgroundBrush(Qt::white);

    // Create centipede
    centipede = new Centipede();
    centipede->addToScene(scene);

    // Create blaster
    blaster = new Blaster();
    blaster->setFlag(QGraphicsItem::ItemIsFocusable);
    blaster->setFocus();
    scene->addItem(blaster);
    blaster->setPos(400,500);



    show();
}

Game::~Game()
{
    delete centipede;
    delete blaster;
    delete scene;
}


