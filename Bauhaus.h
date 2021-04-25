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
