#include <QKeyEvent>
#include <QGraphicsScene>
#include "Mushroom.h"
#include "Dart.h"

#include <QDebug>

Mushroom::Mushroom()
{
    setPixmap(QPixmap(":/images/images/mushroom_4hp.png"));
}

int Mushroom::getHealth()
{
    return this->health;
}

bool Mushroom::decrementHealth()
{
    this->health--;

    if(this->health > 0)
    {

        if(health == 3)
            setPixmap(QPixmap(":/images/images/mushroom_3hp.png"));
        else if(health == 2)
            setPixmap(QPixmap(":/images/images/mushroom_2hp.png"));
        else if(health == 1)
            setPixmap(QPixmap(":/images/images/mushroom_1hp.png"));
        return false;
    }
    else
    {
       scene()->removeItem(this);
       return true;
    }
}

bool Mushroom::is_shot()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid (Dart))
        {
            return true;
        }
    }
    return false;
}

MushroomField::MushroomField(int num_mushrooms, QGraphicsScene * myscene)
{

    this->num_mushrooms = num_mushrooms;
    this->myscene = myscene;

    srand((unsigned) time(NULL));

    for(int i = 0; i < num_mushrooms; i++) {

        int x_rand = rand() % FIELD_W/25;
        int y_rand = rand() % FIELD_H/25;

        binary_field[x_rand][y_rand] = 1;

    }

    for(int i = 0; i < FIELD_W/25; i++)
    {
        for(int j = 0; j < FIELD_H/25; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*25,50+j*25);
                mushroom_field.push_back(mushroom);

            }
        }
    }

    for(size_t i = 0; i < mushroom_field.size(); i++) {
        myscene->addItem(mushroom_field[i]);
    }
}

void MushroomField::dartCollision()
{
    for(size_t i = 0; i < mushroom_field.size(); i++)
    {
        if(mushroom_field[i]->is_shot())
        {
            if (mushroom_field[i]->decrementHealth()) {

                // Remove from binary field if mushroom is gone
                int x = mushroom_field[i]->x()/25;
                int y = mushroom_field[i]->y()/25;
                binary_field[x][y] = 0;
            }
        }
    }
}
