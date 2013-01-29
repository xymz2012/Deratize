#include <QtCore/QCoreApplication>
#include "warehouse.h"

int main(int argc, char *argv[])
{
    Q_ASSERT(argc == 2);
    WareHouse wh(argv[1]);

    //寻找能消灭指定mice的炸弹的位置
    QVector<QSet<QPoint>> all;
    foreach (QPoint mice, wh.mouse)
    {
        all << wh.explosion_range(mice);
    }

    //遍历所有的炸弹对,判断其是否能消灭所有老鼠
    for (int i=0; i<wh.not_wall.size(); i++)
    {
        QPoint bomb1 = wh.not_wall[i];

        //剔除all中,bomb1能消灭的老鼠,得到ms_on_bomb2为炸弹2需要消灭的老鼠
        QVector<QSet<QPoint>*> ms_on_bomb2;
        for (int n=0; n<all.size(); n++)
        {
            QSet<QPoint>* ps = &all[n];
            if (!ps->contains(bomb1))
                ms_on_bomb2.append(ps);
        }

        //遍历bomb2
        for (int j=i+1; j<wh.not_wall.size(); j++)
        {
            //判断bomb2 是否能消灭ms_on_bomb2中的所有老鼠
            bool cover = true;
            QPoint bomb2 = wh.not_wall[j];
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
                return 0;
            }
        }
    }

    //未能找到合适的炸弹对
    qDebug()<<"-1";
    return 0;
}
