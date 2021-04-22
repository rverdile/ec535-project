#include "Game.h"
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"
#include "Button.h"
#include "Dart.h"
#include "QTextBlockFormat"
#include "QTextCursor"

#include "QtDebug"

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

    // Create the title
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Centipede"));
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("Bauhaus 93",50);
    titleText->setFont(titleFont);
    int x = this->width()/2 - titleText->boundingRect().width()/2;
    int y = 150;
    titleText->setPos(x,y);
    scene->addItem(titleText);

    // Create the play button
    Button* playButton = new Button(QString("Play"));
    x = this->width()/2 - playButton->boundingRect().width()/2;
    y = 350;
    playButton->setPos(x,y);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // Create the How To Play button
    Button* howButton = new Button(QString("How to Play"));
    x = this->width()/2 - howButton->boundingRect().width()/2;
    y = 450;
    qDebug() << x << y;
    howButton->setPos(x,y);
    connect(howButton,SIGNAL(clicked()),this,SLOT(showHowToPlay()));
    scene->addItem(howButton);
}

void Game::showHowToPlay()
{
    qDebug() << "here";
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,700);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,700);
    scene->setBackgroundBrush(Qt::black);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("How To Play"));
    titleText->setDefaultTextColor(Qt::white);
    QFont titleFont("Bauhaus 93",30);
    titleText->setFont(titleFont);
    int x = this->width()/2 - titleText->boundingRect().width()/2;
    int y = 80;
    titleText->setPos(x,y);
    scene->addItem(titleText);

    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QString instr = QString("When the game begins, a centipede will spawn in at the top of screen and begin navigating down through a field of mushrooms. The object of the game is to eliminate "
                    "all of the centipede's body segments by shooting them. You control the blaster at the bottom of the screen. Use the arrow keys to move the blaster around and space to shoot a dart. "
                    "Shooting a centipede segment will turn it into a mushroom. Shooting a centipede's body segment will split the centipede in two. "
                    "A centipede's head is worth 100 points, and body segments are worth 10. Mushrooms take 4 hits to eliminate and are worth 1 point. "
                    "Beat the game by completely eliminating the centipede before it gets to the bottom of the screen.");

    QGraphicsTextItem *instrText = new QGraphicsTextItem(instr);
    instrText->setDefaultTextColor(Qt::white);
    instrText->setTextWidth(this->width()/4*3);
    QFont textFont("Helvetica", 10);
    instrText->setFont(textFont);
    x = this->width()/2 - instrText->boundingRect().width()/2;
    y = 180;
    instrText->setPos(x,y);
    QTextCursor cursor = instrText->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    instrText->setTextCursor(cursor);
    scene->addItem(instrText);


    // Return to main menu
    Button* menuButton = new Button(QString("Return to Main Menu"));
    x = this->width()/2 - menuButton->boundingRect().width()/2;
    y = 500;
    menuButton->setPos(x,y);
    connect(menuButton,SIGNAL(clicked()),this,SLOT(showMainMenu()));
    scene->addItem(menuButton);
}

Game::~Game()
{
    if (centipedes != nullptr)
        delete centipedes;
    if (blaster != nullptr)
        delete blaster;
    if (scene != nullptr)
        delete scene;
    if (mushrooms != nullptr)
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


