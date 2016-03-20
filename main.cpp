#include "pointgame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PointGame w;
    w.show();

    return a.exec();
}
