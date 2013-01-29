#include <QtCore/QCoreApplication>
#include "warehouse.h"

void deratize(const WareHouse& wh)
{
    //���г����ж�
    if (wh.candidate_template.size()*2 < wh.mouse.size())
    {
        qDebug() << "-1";
        return;
    }

    //Ѱ��������ָ��mice��ը����λ��
    QVector<QSet<QPoint>> all;
    QSet<QPoint> bomb_set;
    foreach (QPoint mice, wh.mouse)
    {
        QSet<QPoint> xx = wh.explosion_range(mice);
        all << xx;
        bomb_set += xx;
    }

    QList<QPoint> bomb_list = bomb_set.toList();

    //�������е�ը����,�ж����Ƿ���������������
    for (int i=0; i<bomb_list.size(); i++)
    {
        QPoint bomb1 = bomb_list[i];

        //�޳�all��,bomb1�����������,�õ�ms_on_bomb2Ϊը��2��Ҫ���������
        QVector<QSet<QPoint>*> ms_on_bomb2;
        for (int n=0; n<all.size(); n++)
        {
            QSet<QPoint>* ps = &all[n];
            if (!ps->contains(bomb1))
                ms_on_bomb2.append(ps);
        }

        //����bomb2
        for (int j=i+1; j<bomb_list.size(); j++)
        {
            //�ж�bomb2 �Ƿ�������ms_on_bomb2�е���������
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

            //���������������������,��ӡ������
            if (cover == true)
            {
                qDebug() << bomb1.y()+1 << bomb1.x()+1
                    << bomb2.y()+1 << bomb2.x()+1;
                return;
            }
        }
    }

    //δ���ҵ����ʵ�ը����
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
