#include <QtCore/QCoreApplication>
#include "warehouse.h"

void deratize(const WareHouse& wh)
{
    //进行初步判断
    if (wh.candidate_template.size()*2 < wh.mouse.size())
    {
        qDebug() << "-1";
        return;
    }

    //寻找能消灭指定mice的炸弹的位置
    QVector<QSet<QPoint>> all;
    QSet<QPoint> bomb_set;
    foreach (QPoint mice, wh.mouse)
    {
        QSet<QPoint> xx = wh.explosion_range(mice);
        all << xx;
        bomb_set += xx;
    }

    QList<QPoint> bomb_list = bomb_set.toList();

    //遍历所有的炸弹对,判断其是否能消灭所有老鼠
    for (int i=0; i<bomb_list.size(); i++)
    {
        QPoint bomb1 = bomb_list[i];

        //剔除all中,bomb1能消灭的老鼠,得到ms_on_bomb2为炸弹2需要消灭的老鼠
        QVector<QSet<QPoint>*> ms_on_bomb2;
        for (int n=0; n<all.size(); n++)
        {
            QSet<QPoint>* ps = &all[n];
            if (!ps->contains(bomb1))
                ms_on_bomb2.append(ps);
        }

        //遍历bomb2
        for (int j=i+1; j<bomb_list.size(); j++)
        {
            //判断bomb2 是否能消灭ms_on_bomb2中的所有老鼠
            bool cover = true;
            QPoint bomb2 = bomb_list[j];
            for (int n=0; n<ms_on_bomb2.size(); n++)
            {
                QSet<QPoint>* mouse = ms_on_bomb2[n];
                if (!mouse->contains(bomb2))
                {
                    cover = false;
                    break;
                }
            }

            //满足消灭所有老鼠的条件,打印并返回
            if (cover == true)
            {
                qDebug() << bomb1.y()+1 << bomb1.x()+1
                    << bomb2.y()+1 << bomb2.x()+1;
                return;
            }
        }
    }

    //未能找到合适的炸弹对
    qDebug()<<"-1";
}

int main(int argc, char *argv[])
{
    Q_ASSERT(argc == 2);
    WareHouse wh(argv[1]);

    QTime time;
    time.start();

    deratize(wh);

    int elapsed = time.elapsed();
    //qDebug()<<elapsed<<"ms";

    return 0;
}
