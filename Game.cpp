/*
 * EC535 Final Project - Centipede
 * Game: Creates the menu screens and game
 * components and handles logic for moving
 * between levels and ending the game
 */

#include <QApplication>
#include <QTimer>
#include "Game.h"
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"
#include "Button.h"
#include "Dart.h"
#include "Bauhaus.h"
#include "QTextBlockFormat"
#include "QTextCursor"

#include "QtDebug"

// Constructor, displays main menu
Game::Game(QWidget *parent)
{
    showMainMenu();
}

// Create and show main menu
void Game::showMainMenu()
{
    // Create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,SCENE_W,SCENE_H);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCENE_H,SCENE_W);
    scene->setBackgroundBrush(Qt::black);

    // Create the title
    Bauhaus *title = new Bauhaus("centipede");
    title->setPos(36,115);
    scene->addItem(title);

    // Create the play button
    Button* playButton = new Button(QString("Play"));
    int x = SCENE_W/2 - playButton->boundingRect().width()/2;
    int y = 225;
    playButton->setPos(x,y);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // Create the How To Play button
    Button* howButton = new Button(QString("How to Play"));
    x = SCENE_W/2 - howButton->boundingRect().width()/2;
    y = 300;
    howButton->setPos(x,y);
    connect(howButton,SIGNAL(clicked()),this,SLOT(showHowToPlay()));
    scene->addItem(howButton);
}

// Show the "How to Play" screen
void Game::showHowToPlay()
{
    // Create the scene
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,SCENE_W,SCENE_H);
    scene->setBackgroundBrush(Qt::black);

    // Create the title
    Bauhaus *title = new Bauhaus("howToPlay");
    title->setPos(36,10);
    scene->addItem(title);

    // Create the instruction text
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QString instr = QString("When the game begins, a centipede will spawn in at the top of screen and begin navigating down through a field of mushrooms. The object of the game is to eliminate "
                    "all of the centipede's body segments by shooting them. You control the blaster at the bottom of the screen. Use the arrow keys to move the blaster around and space to shoot a dart. "
                    "Shooting a centipede segment will turn it into a mushroom. Shooting a centipede's body segment will split the centipede in two. "
                    "A centipede's head is worth 100 points, and body segments are worth 10. Mushrooms take 4 hits to eliminate and are worth 1 point. "
                    "The game is over if a centipede reaches the bottom of the screen or collides with the blaster.");

    QGraphicsTextItem *instrText = new QGraphicsTextItem(instr);
    instrText->setDefaultTextColor(Qt::white);
    instrText->setTextWidth(SCENE_W/5*4);
    QFont textFont("Helvetica", 9);
    instrText->setFont(textFont);
    int x = SCENE_W/2 - instrText->boundingRect().width()/2;
    int y = 60;
    instrText->setPos(x,y);
    QTextCursor cursor = instrText->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    instrText->setTextCursor(cursor);
    scene->addItem(instrText);

    // Create Main Menu button
    Button* menuButton = new Button(QString("Main Menu"));
    x = SCENE_W/2 - menuButton->boundingRect().width()/2;
    y = 410;
    menuButton->setPos(x,y);
    connect(menuButton,SIGNAL(clicked()),this,SLOT(showMainMenu()));
    scene->addItem(menuButton);
}

// Show "Game Over" screen
void Game::showGameEnd()
{
    // Stop timers
    timer->stop();
    centipedes->stop();

    // Remove items
    this->removeItems();

    // Create scene
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,SCENE_W,SCENE_H);
    scene->setBackgroundBrush(Qt::black);

    // Create the title
    Bauhaus *title = new Bauhaus("gameOver");
    title->setPos(36,115);
    scene->addItem(title);

    // Show final score
    int finalScore = score->getScore();
    QGraphicsTextItem *scoreText = new QGraphicsTextItem("Score: " + QString::number(finalScore));
    scoreText->setDefaultTextColor(Qt::white);
    QFont titleFont("Helvetica",14);
    titleFont.setBold(true);
    scoreText->setFont(titleFont);
    scoreText->setPos(SCENE_W/2 - scoreText->boundingRect().width()/2, 160);
    scene->addItem(scoreText);

    // Create the Play Again button
    Button* playButton = new Button(QString("Play Again"));
    int x = SCENE_W/2 - playButton->boundingRect().width()/2;
    int y = 225;
    playButton->setPos(x,y);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // Create the Main Menu button
    Button* exitButton = new Button(QString("Main Menu"));
    x = SCENE_W/2 - exitButton->boundingRect().width()/2;
    y = 300;
    exitButton->setPos(x,y);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(showMainMenu()));
    scene->addItem(exitButton);
}

void Game::closeGame()
{
    qApp->exit();
    //this->~Game();
}

Game::~Game()
{
//    if (centipedes != nullptr)
//        delete centipedes;
//    if (blaster != nullptr)
//        delete blaster;
//    if (scene != nullptr)
//        delete scene;
//    if (mushrooms != nullptr)
//        delete mushrooms;
}

// Delete game related items
void Game::removeItems()
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

// Start game
void Game::start()
{
    // Set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,SCENE_W,SCENE_H);
    setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    // Create mushroom field
    int num_mushrooms = 25;
    mushrooms = new MushroomField(num_mushrooms,scene);

    // Create centipede
    centipedes = new Centipedes(scene, mushrooms);

    // Create blaster
    blaster = new Blaster(centipedes, mushrooms, scene);
    blaster->setFlag(QGraphicsItem::ItemIsFocusable);
    blaster->setFocus();
    scene->addItem(blaster);
    scene->addItem(blaster->livesText);
    blaster->setPos(SCENE_W/2-10,460);

    // Connect Blaster/Centipede collision to endgame
    connect(blaster,SIGNAL(endGame()),this,SLOT(showGameEnd()));

    // Create Score
    score = new Score(scene);
    scene->addItem(score->scoreText);

    // Set up timer for checking if all centipedes are gone
    timer = new QTimer(); // every time it goes to 0, signal will execute
    connect(timer,SIGNAL(timeout()),this,SLOT(nextLevel()));
    timer->start(20); // 20ms

    show();
}

// Check if all centipedes have been defeated
// If so, move to the next level
void Game::nextLevel()
{
    // Check if there are any centipede segments left in the scene
    bool flag = true;
    QList<QGraphicsItem *> items = scene->items();
    for (int i = 0; i < (int)items.size(); i++) {
        if (typeid(*(items[i])) == typeid(Centipede_Segment)) {
            flag = false;
            break;
        }
    }

    // If the there are no centipedes left, move to the next level
    if (centipedes->getCentipedesSize() == 0 || flag)
    {
        // Create a new centipede
        delete centipedes;
        centipedes = new Centipedes(scene, mushrooms);

        // Create new mushrooms, adding 5 to total
        if (mushrooms != nullptr)
        {
            int n = (int)mushrooms->mushroom_field.size();
            for(int i = 0; i < n; i++)
            {
                scene->removeItem(mushrooms->mushroom_field[i]);
                mushrooms->mushroom_field.pop_back();
            }
          mushrooms->nextMushroom();
          mushrooms->addMushrooms(5);
          mushrooms->drawField();
        }
    }
}


