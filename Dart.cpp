#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Dart.h"
#include "game.h"


Dart::Dart()
{
    // draw the rect
    setPixmap(QPixmap(":/images/dart.png"));

    // connect
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute

    // connects timeout() function of timer to move slot of this bullet
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(20); // 20ms
}

void Dart::move()
{
    // move bullet up
    setPos(x(),y()-10);

    if(pos().y() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
