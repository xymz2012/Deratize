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
    //���г����ж�,������������,�ո��ӹ���,����û������
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

    //Ѱ��������ָ��mice��ը����λ��
    QVector<QSet<QPoint>> all;
    foreach (QPoint mice, wh.mouse)
    {
        QSet<QPoint> temp = wh.explosion_range(mice);
        all << temp; 
    }

    //bomb1 ����ը�� mouse[0]������
    foreach (QPoint bomb1, all[0])
    {
        //�޳�mouse��,bomb1�����������.
        //�õ���mouse_by_bomb2Ϊbomb2��Ҫ���������
        QVector<QSet<QPoint>*> mouse_by_bomb2;
        for (int n=1; n<all.size(); n++)
        {
            if (!all[n].contains(bomb1))
                mouse_by_bomb2.append(&all[n]);
        }

        //bomb1 ����������������
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
        
        //mouse_by_bomb2�Ľ���,�õ��ļ�Ϊ���õĽ�
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
