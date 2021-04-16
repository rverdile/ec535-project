#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Dart.h"
#include "Game.h"
#include "Centipede.h"

#include <QDebug>

Dart::Dart()
{
    // draw the rect
    setPixmap(QPixmap(":/images/images/dart.png"));

    // connect
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute

    // connects timeout() function of timer to move slot of this bullet
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(20); // 20ms
}

void Dart::move()
{
    // Check for collision with centipede
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid (Centipede_Segment)) {

            // Tell centipedes that there's been a collision
            emit collision();

            // Remove dart if it collides with centipede
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // move bullet up
    setPos(x(),y()-10);

    if(pos().y() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
