#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QtCore>
#include <QVector2D>

class WareHouse 
{
public:
    WareHouse(QString path);
    ~WareHouse();

    QChar matrix_at(QPoint pos);

    QSet<QPoint> explosion_range(QPoint bomb_pos);

    QSet<QPoint> explosion_range_without_wall(QPoint bomb_pos);

private:
    int m;
    int n;
    int d;
    QVector<QString> matrix;
    QSet<QPoint> not_wall;
    QSet<QPoint> wall;
    QSet<QPoint> mouse;
    QSet<QPoint> candidate_template;
};

#endif // WAREHOUSE_H
