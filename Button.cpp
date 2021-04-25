#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

// Creates button with given text
Button::Button(QString string, QGraphicsItem *parent): QGraphicsRectItem(parent){

    setRect(0,0,130,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);

    text = new QGraphicsTextItem(string,this);
    text->setDefaultTextColor(Qt::white);
    QFont textFont("Helvetica",9);
    text->setFont(textFont);
    int x = rect().width()/2 - text->boundingRect().width()/2;
    int y = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(x,y);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
