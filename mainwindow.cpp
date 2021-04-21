#include "mainwindow.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

Game * game;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("Centipede"));
    game = new Game();
    setCentralWidget(game);
    game->show();
}

MainWindow::~MainWindow()
{
    delete game;
}

