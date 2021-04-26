/*
 * EC535 Final Project - Centipede
 * Blaster: Display and control blaster that
 * the user uses to shoot centipedes and mushrooms
 */

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "Blaster.h"
#include "Dart.h"
#include "Mushroom.h"
#include "Game.h"
#include "Bauhaus.h"

extern Game * game;

Blaster::Blaster(Centipedes * centipedes, MushroomField * mushroom_field, QGraphicsScene * myscene)
{
    // Set variables
    this->centipedes = centipedes;
    this->mushroom_field = mushroom_field;
    this->myscene = myscene;
    setPixmap(QPixmap(":/images/images/blaster.png"));

    // Connect timeout() function of timer to collisionCheck slot of blaster
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute
    connect(timer,SIGNAL(timeout()),this,SLOT(collisionCheck()));
    timer->start(5); // 5ms

    // Connect checkScore timer
    connect(timer,SIGNAL(timeout()),this,SLOT(checkScore()));
    timer->start(5); // 5ms

    placeLivesText();

}

// Handler for key presses
void Blaster::keyPressEvent(QKeyEvent *event)
{
    mov_x = 0;
    mov_y = 0;

    // Move blaster left
    if(event->key() == Qt::Key_Left) {
        if(pos().x() > 0)
        {
            mov_x -= speed;
        }
    }
    // Move blaster right
    else if(event->key() == Qt::Key_Right) {
        if(pos().x()+20 < 272)
        {
            mov_x += speed;
        }
    }
    // Move blaster up
    if(event->key() == Qt::Key_Up) {

        if(pos().y()-speed > 432)
        {
            mov_y -= speed;
        }
    }
    // Move blaster down
    else if(event->key() == Qt::Key_Down) {
        if(pos().y()+20 < 480)
        {
            mov_y += speed;
        }
    }
    // Shoot a dart
    if(event->key() == Qt::Key_Space)
    {
        // Create a dart
        Dart * dart = new Dart();

        // Set up collision signals for both centipedes and mushrooms
        QObject::connect(dart, &Dart::collision, game->centipedes, &Centipedes::collision_check);
        QObject::connect(dart, &Dart::mushroomCollision, mushroom_field, &MushroomField::dartCollision);

        dart->setPos(x(),y());
        scene()->addItem(dart);
    }

    setPos((x()+mov_x),(y()+mov_y));
}

// Check for and handle collisions with centipede
void Blaster::collisionCheck()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // Check for collision with centipede
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid (Centipede_Segment)) {

            // End the game if the centipede hits the blaster and no lives left
            if(lives == 0 && isInvulnerable == 0)
                emit endGame();

            // If there are lives left, remove a life and shield the blaster
            else if(lives > 0)
            {
                lives--;
                myscene->removeItem(livesText);
                placeLivesText();
                isInvulnerable = 1;
                setPixmap(QPixmap(":/images/images/shielded_blaster.png"));
                QTimer::singleShot(TIME_INVULNERABLE,this,SLOT(endInvulnerability()));
                this->setPos(SCENE_W/2-10,460);
            }
        }
    }
}

// Check the score, adding a life if NEW_LIFE_SCORE is exceeded
void Blaster::checkScore()
{
    //converted score: score - n*NEW_LIFE_SCORE, where n = interval
    //(n=0:(0,12000), n=1:(12000,24000),...) where NEW_LIFE_SCORE = 12000
    long converted_score = (game->score->getScore()) - score_int_idx*NEW_LIFE_SCORE;

    if(converted_score > NEW_LIFE_SCORE)
    {
        score_int_idx++;
        lives++;

        myscene->removeItem(livesText);
        placeLivesText();
    }
}

// Blaster is no longer invulnerable
void Blaster::endInvulnerability()
{
    isInvulnerable = 0;
    setPixmap(QPixmap(":/images/images/blaster.png"));
}

// Add the lives text to the screen
void Blaster::placeLivesText()
{
    // Draw "Lives:"
    Bauhaus *livesLabel = new Bauhaus("lives");
    livesLabel->setPos(FULL_W-100,5);
    myscene->addItem(livesLabel);

    // Write the number of lives
    livesText = new QGraphicsTextItem(QString::number(lives));
    livesText->setDefaultTextColor(Qt::white);
    QFont titleFont("Helvetica",14);
    titleFont.setBold(true);
    livesText->setFont(titleFont);
    livesText->setPos(FULL_W - 32,2);
    myscene->addItem(livesText);
}
