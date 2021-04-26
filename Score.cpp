/*
 * EC535 Final Project - Centipede
 * Score: Updates and displays current score
 */

#include <QFont>
#include "Score.h"
#include "Bauhaus.h"

#include <QDebug>

// Constructor, draws current score
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

// Score accessor
long Score::getScore()
{
    return this->score;
}

// Add ten points when centipede body segment shot
void Score::tailIncrease()
{
    score += 10;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

// Add 100 points when centipede head shot
void Score::headIncrease()
{
    score += 100;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

// Add 1 point when mushroom shot
void Score::mushIncrease()
{
    score += 1;
    scene->removeItem(scoreText);
    scoreText = new QGraphicsTextItem(QString::number(score));
    formatText();
    scene->addItem(scoreText);
}

// Format score text
void Score::formatText()
{
    scoreText->setDefaultTextColor(Qt::white);
    QFont titleFont("Helvetica",14);
    titleFont.setBold(true);
    scoreText->setFont(titleFont);
    scoreText->setPos(110,2);
}
