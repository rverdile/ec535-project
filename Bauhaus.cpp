/*
 * EC535 Final Project - Centipede
 * Bauhaus: Used to display images of text because
 * the font Bauhaus 93 is not available on the stock
 * image provided for this project
 */

#include "Bauhaus.h"


// Create text image
Bauhaus::Bauhaus(QString image)
{
    if (image == "centipede")
        setPixmap(QPixmap(":/images/images/centipede.png"));
    else if (image == "score")
        setPixmap(QPixmap(":/images/images/score.png"));
    else if (image == "howToPlay")
        setPixmap(QPixmap(":/images/images/howToPlay.png"));
    else if (image == "lives")
        setPixmap(QPixmap(":/images/images/lives.png"));
    else if (image == "gameOver")
        setPixmap(QPixmap(":/images/images/gameOver.png"));
}
