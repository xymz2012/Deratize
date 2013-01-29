#include <QtCore/QCoreApplication>
#include "warehouse.h"

void print_result(QPoint bomb1, QPoint bomb2)
{
    static int sum = 0;
    qDebug() << sum++ << ":" << bomb1.y()+1 << bomb1.x()+1
        << bomb2.y()+1 << bomb2.x()+1;
}

void deratize(const WareHouse& wh)
{
    //进行初步判断,老鼠数量过多,空格子过少,或者没有老鼠
    if (wh.candidate_template.size()*2 < wh.mouse.size() ||
        wh.not_wall.size() < 2)
    {
        qDebug() << "-1";
        return;
    }
    if (wh.mouse.size() <= 0)
    {
        print_result(wh.not_wall[0], wh.not_wall[1]);
        return;
    }

    //寻找能消灭指定mice的炸弹的位置
    QVector<QSet<QPoint>> all;
    foreach (QPoint mice, wh.mouse)
    {
        QSet<QPoint> temp = wh.explosion_range(mice);
        all << temp; 
    }

    //bomb1 可以炸到 mouse[0]的老鼠
    foreach (QPoint bomb1, all[0])
    {
        //剔除mouse中,bomb1能消灭的老鼠.
        //得到的mouse_by_bomb2为bomb2需要消灭的老鼠
        QVector<QSet<QPoint>*> mouse_by_bomb2;
        for (int n=1; n<all.size(); n++)
        {
            if (!all[n].contains(bomb1))
                mouse_by_bomb2.append(&all[n]);
        }

        //bomb1 可以消灭所有老鼠
        if (mouse_by_bomb2.size() == 0)
        {
            foreach (QPoint bomb2, wh.not_wall)
            {
                if(bomb2 != bomb1)
                {
                    print_result(bomb1, bomb2);
                    return;
                }
            }
        }
        
        //mouse_by_bomb2的交集,得到的即为可用的解
        QSet<QPoint> valid_bomb2 = *mouse_by_bomb2[0];
        for (int n=1; n<mouse_by_bomb2.size(); n++)
        {
            valid_bomb2 &= *mouse_by_bomb2[n];
        }

        foreach (QPoint bomb2, valid_bomb2)
        {
            print_result(bomb1, bomb2);
            return;
        }
    }
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
    qDebug()<<elapsed<<"ms";

    QCoreApplication app(argc, argv);
    app.exec();
    return 0;
}
