#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QtCore>

class WareHouse 
{
public:
    WareHouse(QString path);
    ~WareHouse();

    //����bomb_pos��ը��,�ܲ����������и��ӵ�λ��
    QSet<QPoint> explosion_range(QPoint bomb_pos) const;

    //explosion_range ������ǽ�����صİ汾
    QSet<QPoint> explosion_range_without_wall(QPoint bomb_pos) const;

    //A*Ѱ·�㷨,sp���,ep�յ�,walkableѰ·���ߵĸ���
    QVector<QPoint> a_star(QPoint sp, QPoint ep, QSet<QPoint> walkable) const;

    //matrix[r][c],(r,c)�˸��ӵ�״̬
    QVector<QString> matrix;
    //���з�ǽ�ڸ��ӵļ���
    //QVector<QPoint> not_wall;
    //����ǽ�ڸ��ӵļ���
    QSet<QPoint> wall;
    //����������ӵļ���
    QSet<QPoint> mouse;
    //ը����(0,0)����ը,�ܲ����������и���(����������ĸ���)
    QSet<QPoint> candidate_template;

    int m;
    int n;
    int d;
};

bool operator<(const QPoint& lhs, const QPoint& rhs);
uint qHash(const QPoint &point);

#endif // WAREHOUSE_H
