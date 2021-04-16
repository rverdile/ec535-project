#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "Blaster.h"
#include "Dart.h"

Blaster::Blaster()
{
    setPixmap(QPixmap(":/images/blaster.png"));
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

        if(pos().y() > 530)
        {
            mov_y -= speed;
        }
    }
    else if(event->key() == Qt::Key_Down) {
        if(pos().y()+32 < 600)
        {
            mov_y += speed;
        }
    }
    if(event->key() == Qt::Key_Space)
    {
        //create a dart
        Dart * dart = new Dart();
        dart->setPos(x(),y());
        scene()->addItem(dart);
    }

    setPos((x()+mov_x),(y()+mov_y));
}
