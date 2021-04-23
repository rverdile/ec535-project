#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "Blaster.h"
#include "Dart.h"
#include "Mushroom.h"
#include "Game.h"

extern Game * game;

Blaster::Blaster(Centipedes * centipedes, MushroomField * mushroom_field)
{
    this->centipedes = centipedes;
    this->mushroom_field = mushroom_field;
    setPixmap(QPixmap(":/images/images/blaster.png"));

    // connects timeout() function of timer to collisionCheck slot of blaster
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute
    connect(timer,SIGNAL(timeout()),this,SLOT(collisionCheck()));
    timer->start(5); // 5ms

    // connect checkScore timer
    connect(timer,SIGNAL(timeout()),this,SLOT(checkScore()));
    timer->start(5); // 5ms
}

void Blaster::keyPressEvent(QKeyEvent *event)
{
    mov_x = 0;
    mov_y = 0;

    if(event->key() == Qt::Key_Left) {
        if(pos().x() > 0)
        {
            mov_x -= speed;
        }
    }
    else if(event->key() == Qt::Key_Right) {
        if(pos().x()+32 < 800)
        {
            mov_x += speed;
        }
    }
    if(event->key() == Qt::Key_Up) {

        if(pos().y() > 550)
        {
            mov_y -= speed;
        }
    }
    else if(event->key() == Qt::Key_Down) {
        if(pos().y()+32 < 700)
        {
            mov_y += speed;
        }
    }
    if(event->key() == Qt::Key_Space)
    {
        //create a dart
        Dart * dart = new Dart();
        QObject::connect(dart, &Dart::collision, centipedes, &Centipedes::collision_check);
        QObject::connect(dart, &Dart::mushroomCollision, mushroom_field, &MushroomField::dartCollision);
        dart->setPos(x(),y());
        scene()->addItem(dart);
    }

    setPos((x()+mov_x),(y()+mov_y));
}

void Blaster::collisionCheck()
{

    QList<QGraphicsItem *> colliding_items = collidingItems();
    // Check for collision with centipede
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid (Centipede_Segment)) {
            if(lives == 0 && isInvulnerable == 0)
                emit endGame();
            else if(lives > 0)
            {
                lives--;
                isInvulnerable = 1;
                setPixmap(QPixmap(":/images/images/shielded_blaster.png"));
                QTimer::singleShot(TIME_INVULNERABLE,this,SLOT(endInvulnerability()));
                this->setPos(450,660);
            }
        }
    }
}

void Blaster::checkScore()
{
    //converted score: score - n*NEW_LIFE_SCORE, where n = interval
    //(n=0:(0,12000), n=1:(12000,24000),...)
    long converted_score = (game->score->getScore()) - score_int_idx*NEW_LIFE_SCORE;
    qDebug() << this->lives;
    if(converted_score > NEW_LIFE_SCORE)
    {
        score_int_idx++;
        lives++;
    }
}

void Blaster::endInvulnerability()
{
    isInvulnerable = 0;
    setPixmap(QPixmap(":/images/images/blaster.png"));
}
