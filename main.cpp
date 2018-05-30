#include <QCoreApplication>
#include "CGameLoop.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CGameLoop game;
    game.gameStart();

    return a.exec();
}




