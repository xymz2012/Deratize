#include <QtCore/QCoreApplication>
#include "warehouse.h"

int main(int argc, char *argv[])
{
    WareHouse wh("../input2.txt");

    wh.explosion_range(QPoint(3,3));
}
