/*
 * EC535 Final Project - Centipede
 * Button: Create buttons for use on
 * menu pages
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Button(QString name, QGraphicsItem* parent=NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
