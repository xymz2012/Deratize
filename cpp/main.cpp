#include <QtCore/QCoreApplication>
#include "warehouse.h"

int main(int argc, char *argv[])
{
    Q_ASSERT(argc == 2);
    WareHouse wh(argv[1]);

    //Ѱ��������ָ��mice��ը����λ��
    QVector<QSet<QPoint>> all;
    foreach (QPoint mice, wh.mouse)
    {
        all << wh.explosion_range(mice);
    }

    //�������е�ը����,�ж����Ƿ���������������
    for (int i=0; i<wh.not_wall.size(); i++)
    {
        QPoint bomb1 = wh.not_wall[i];

        //�޳�all��,bomb1�����������,�õ�ms_on_bomb2Ϊը��2��Ҫ���������
        QVector<QSet<QPoint>*> ms_on_bomb2;
        for (int n=0; n<all.size(); n++)
        {
            QSet<QPoint>* ps = &all[n];
            if (!ps->contains(bomb1))
                ms_on_bomb2.append(ps);
        }

        //����bomb2
        for (int j=i+1; j<wh.not_wall.size(); j++)
        {
            //�ж�bomb2 �Ƿ�������ms_on_bomb2�е���������
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

            //���������������������,��ӡ������
            if (cover == true)
            {
                qDebug() << bomb1.y()+1 << bomb1.x()+1
                    << bomb2.y()+1 << bomb2.x()+1;
                return 0;
            }
        }
    }

    //δ���ҵ����ʵ�ը����
    qDebug()<<"-1";
    return 0;
}
