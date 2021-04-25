#include "mainwindow.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <QtDebug>

Game * game;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("Centipede"));
    game = new Game();
    setCentralWidget(game);
    game->show();

    // Rotate for touchscreen
    game->rotate(270);
}

MainWindow::~MainWindow()
{
    delete game;
}

