#include <QKeyEvent>
#include <QGraphicsScene>
#include "Mushroom.h"
#include "Dart.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

int mush_id = 1;

Mushroom::Mushroom()
{
    getMushroomImage();
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
        getMushroomImage();
        return false;
    }
    else
    {
       scene()->removeItem(this);
       game->score->mushIncrease();
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

void Mushroom::getMushroomImage()
{
    if(mush_id == 1)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_1hp.png"));
        }
    }
    else if(mush_id == 2)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/green_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/green_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/green_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/green_mush_1hp.png"));
        }
    }
    else if(mush_id == 3)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/red_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/red_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/red_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/red_mush_1hp.png"));
        }
    }
}

MushroomField::MushroomField(int num_mushrooms, QGraphicsScene * myscene)
{
    mush_id = 1;
    this->num_mushrooms = num_mushrooms;
    this->myscene = myscene;

    srand((unsigned) time(NULL));

    for(int i = 0; i < num_mushrooms; i++) {

        int x_rand = rand() % FIELD_W/16;
        int y_rand = rand() % FIELD_H/16;

        binary_field[x_rand][y_rand] = 1;

    }

    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
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
                int x = mushroom_field[i]->x()/16;
                int y = mushroom_field[i]->y()/16;
                binary_field[x][y-2] = 0;

                //qDebug() << "Mushroom deleted: " << x << y-2;
            }
        }
    }
}

void MushroomField::drawField()
{
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
                mushroom_field.push_back(mushroom);
                myscene->addItem(mushroom);

            }
        }
    }
}

void MushroomField::addMushrooms(int num)
{
    // Clear out binary field in blaster area
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = FIELD_H/16; j < FULL_H/16; j++)
        {
            binary_field[i][j] = 0;
        }
    }

    srand((unsigned) time(NULL));

    for(int i = 0; i < num; i++) {

        int x_rand = rand() % FIELD_W/16;
        int y_rand = rand() % FIELD_H/16;

        binary_field[x_rand][y_rand] = 1;

    }

    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
                mushroom_field.push_back(mushroom);
                myscene->addItem(mushroom);

            }
        }
    }
}

void MushroomField::nextMushroom()
{
    if(mush_id == 1)
    {
        mush_id = 2;
    }
    else if(mush_id == 2)
    {
        mush_id = 3;
    }
    else if(mush_id == 3)
    {
        mush_id = 1;
    }
}
