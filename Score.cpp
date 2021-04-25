#include <QFont>
#include "Score.h"
#include "Bauhaus.h"

#include <QDebug>

Score::Score(QGraphicsScene *scene){
    score = 0;

    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    this->scene = scene;
    scene->addItem(scoreText);

    // Create the title
    Bauhaus *scoreLabel = new Bauhaus("score");
    scoreLabel->setPos(30,5);
    scene->addItem(scoreLabel);
}

long Score::getScore()
{
    return this->score;
}

void Score::tailIncrease()
{
    score += 10;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::headIncrease()
{
    score += 100;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::mushIncrease()
{
    score += 1;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

void Score::formatText()
{
    scoreText->setDefaultTextColor(Qt::white);
    QFont titleFont("Helvetica",14);
    titleFont.setBold(true);
    scoreText->setFont(titleFont);
    scoreText->setPos(110,2);
}
