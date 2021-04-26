/*
 * EC535 Final Project - Centipede
 * Bauhaus: Used to display images of text because
 * the font Bauhaus 93 is not available on the stock
 * image provided for this project
 */

#ifndef BAUHAUS_H
#define BAUHAUS_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Bauhaus: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT // macro for signals and slots
public:
    Bauhaus(QString);
};


#endif // BAUHAUS_H
