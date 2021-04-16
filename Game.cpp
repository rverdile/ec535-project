#include "Game.h"
#include "Centipede.h"
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
    scene->setBackgroundBrush(Qt::black);

    // Create centipede
    centipedes = new Centipedes(scene);

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
    delete centipedes;
    delete blaster;
    delete scene;
}


