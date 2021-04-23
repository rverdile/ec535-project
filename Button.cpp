#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

// Creates button with given text
Button::Button(QString string, QGraphicsItem *parent): QGraphicsRectItem(parent){

    setRect(0,0,250,75);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);

    text = new QGraphicsTextItem(string,this);
    text->setDefaultTextColor(Qt::white);
    QFont textFont("Helvetica",10);
    text->setFont(textFont);
    int x = rect().width()/2 - text->boundingRect().width()/2;
    int y = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(x,y);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
    text->setDefaultTextColor(Qt::black);

}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);
    text->setDefaultTextColor(Qt::white);
}
