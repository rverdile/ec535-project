#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <QGraphicsRectItem>
#include <QObject>

class Centipede : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Centipede();
public slots:
    void move();
private:
    bool direction;   // Direction of centipede movement; true=right, false=left
};

#endif // CENTIPEDE_H

