#include "game.h"
#include <QApplication>

int sizeField; // 9 16 25
int countMines; // 10 40 120

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Game window;

    return app.exec();
}
