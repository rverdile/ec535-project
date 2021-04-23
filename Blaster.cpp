#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "Blaster.h"
#include "Dart.h"
#include "Mushroom.h"

Blaster::Blaster(Centipedes * centipedes, MushroomField * mushroom_field)
{
    this->centipedes = centipedes;
    this->mushroom_field = mushroom_field;
    setPixmap(QPixmap(":/images/images/blaster.png"));

    // connects timeout() function of timer to collisionCheck slot of blaster
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute
    connect(timer,SIGNAL(timeout()),this,SLOT(collisionCheck()));
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
            qDebug() << "COLLISION";
            emit endGame();
        }
    }
}
