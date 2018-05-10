#include <QCoreApplication>
#include "CGameLoop.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CGameLoop mainloop;
    mainloop.GameStart();

    return a.exec();
}
