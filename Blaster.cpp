#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "Blaster.h"
#include "Dart.h"
#include "Mushroom.h"

Blaster::Blaster(Centipedes * centipedes, MushroomField * mushroom_field)
{
    this->centipedes = centipedes;
    this->mushroom_field = mushroom_field;
    setPixmap(QPixmap(":/images/images/blaster.png"));
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
