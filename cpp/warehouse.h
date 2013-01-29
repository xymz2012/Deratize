#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QtCore>

class WareHouse 
{
public:
    WareHouse(QString path);
    ~WareHouse();

    //返回bomb_pos的炸弹,能波及到的所有格子的位置
    QSet<QPoint> explosion_range(QPoint bomb_pos) const;

    //explosion_range 不考虑墙壁因素的版本
    QSet<QPoint> explosion_range_without_wall(QPoint bomb_pos) const;

    //A*寻路算法,sp起点,ep终点,walkable寻路可走的格子
    QVector<QPoint> a_star(QPoint sp, QPoint ep, QSet<QPoint> walkable) const;

    //matrix[r][c],(r,c)此格子的状态
    QVector<QString> matrix;
    //所有非墙壁格子的集合
    //QVector<QPoint> not_wall;
    //所有墙壁格子的集合
    QSet<QPoint> wall;
    //所有老鼠格子的集合
    QSet<QPoint> mouse;
    //炸弹在(0,0)处爆炸,能波及到的所有格子(包括负坐标的格子)
    QSet<QPoint> candidate_template;

    int m;
    int n;
    int d;
};

bool operator<(const QPoint& lhs, const QPoint& rhs);
uint qHash(const QPoint &point);

#endif // WAREHOUSE_H
