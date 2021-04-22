#include "Game.h"
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"
#include "Button.h"
#include "Dart.h"

Game::Game(QWidget *parent)
{
    showMainMenu();
}

void Game::showMainMenu()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,700);
    scene->setBackgroundBrush(Qt::black);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Centipede"));
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("Bauhaus 93",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bx = this->width()/2 - playButton->boundingRect().width()/2;
    int by = 400;
    playButton->setPos(bx,by);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);
}

Game::~Game()
{
    if (centipedes)
        delete centipedes;
    if (blaster)
        delete blaster;
    if (scene)
        delete scene;
    if (mushrooms)
        delete mushrooms;
}

void Game::start()
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

    // Create Score
    score = new Score(scene);
    scene->addItem(score->scoreText);

    show();
}


