#include "game.h"
#include "centipede.h"

Game::Game(QWidget *parent)
{
    // Set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // Create centipede
    centipede = new Centipede();
    centipede->addToScene(scene);

    show();
}

Game::~Game()
{
    delete centipede;
}


