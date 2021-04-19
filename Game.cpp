#include "Game.h"
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"

Game::Game(QWidget *parent)
{
    // Set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,700);
    scene->setBackgroundBrush(Qt::black);

    // Create mushroom field
    int num_mushrooms = 50;
    mushrooms = new MushroomField(num_mushrooms,scene);

    // Create centipede
    centipedes = new Centipedes(scene, mushrooms);

    // Create blaster
    blaster = new Blaster(centipedes, mushrooms);
    blaster->setFlag(QGraphicsItem::ItemIsFocusable);
    blaster->setFocus();
    scene->addItem(blaster);
    blaster->setPos(450,660);

    show();
}

Game::~Game()
{
    delete centipedes;
    delete blaster;
    delete scene;
    delete mushrooms;
}


