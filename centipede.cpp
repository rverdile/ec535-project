#include "centipede.h"
#include <QTimer>

#include <QDebug>

Centipede::Centipede()
{
    // Draw
    setRect(0,0,50,10);
    setPos(0,100);

    // Connect to timer
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Start timer
    timer->start(50);

    // Centipede direction is initially right
    direction = true;

    qDebug() << "Starting centipede";
}

// Move the centipede
void Centipede::move()
{
    // Moving right
    if (direction) {
        if (pos().x()<750)
            setPos(x()+10, y());
        else {
            setPos(x(), y()+10);
            direction = false;
        }
    }
    // Moving left
    else {
        if (pos().x() > 0)
            setPos(x()-10, y());
        else {
            setPos(x(), y()+10);
            direction = true;
        }
    }
}
