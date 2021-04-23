#include <QFont>
#include "Score.h"

#include <QDebug>

Score::Score(QGraphicsScene *scene){
    score = 0;

    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
    formatText();
    this->scene = scene;
    scene->addItem(scoreText);
}

long Score::getScore()
{
    return this->score;
}

void Score::tailIncrease()
{
    score += 10;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::headIncrease()
{
    score += 100;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::mushIncrease()
{
    score += 1;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString("SCORE: ") +  QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::formatText()
{
    scoreText->setDefaultTextColor(Qt::white);
    QFont titleFont("Bauhaus 93",20);
    scoreText->setFont(titleFont);
    scoreText->setPos(30,0);
}
