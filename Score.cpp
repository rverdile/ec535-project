#include <QFont>
#include "Score.h"

#include <QDebug>

Score::Score(){
    score = 0;

    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
    scoreText->setDefaultTextColor(Qt::white);
    QFont titleFont("Helvetica",24);
    scoreText->setFont(titleFont);
    scoreText->setPos(30,0);
}

void Score::tailIncrease()
{
    score += 10;
    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
}

void Score::headIncrease()
{
    score += 100;
    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
}
