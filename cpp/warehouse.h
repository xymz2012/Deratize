#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QtCore>
#include <QVector>

class WareHouse 
{
public:
    WareHouse(QString path);
    ~WareHouse();

    QChar matrix_at(QPoint pos);

    QSet<QPoint> explosion_range(QPoint bomb_pos);

    QSet<QPoint> explosion_range_without_wall(QPoint bomb_pos);

    QVector<QPoint> a_star(QPoint sp, QPoint ep, QSet<QPoint> walkable);

    int m;
    int n;
    int d;
    QVector<QString> matrix;
    QVector<QPoint> not_wall;
    QSet<QPoint> wall;
    QSet<QPoint> mouse;
    QSet<QPoint> candidate_template;
};

bool operator<(const QPoint& lhs, const QPoint& rhs);
uint qHash(const QPoint &point);

#endif // WAREHOUSE_H
