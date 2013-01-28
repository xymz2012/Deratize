#include "warehouse.h"

uint qHash(const QPoint &point)  
{
    return point.x()*10000 + point.y();
}

WareHouse::WareHouse(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    //read header
    QString line = in.readLine();
    QStringList head = line.split(" ");
    Q_ASSERT(head.size() == 3);
    bool bOk = true;
    this->n = head[0].toInt(&bOk); Q_ASSERT(bOk);
    this->m = head[1].toInt(&bOk); Q_ASSERT(bOk);
    this->d = head[2].toInt(&bOk); Q_ASSERT(bOk);

    //read matrix
    while (!in.atEnd())
    {
        QString line = in.readLine().toLower();
        Q_ASSERT (line.size() == this->m);
        this->matrix << line;
    }
    Q_ASSERT (this->matrix.size() == n);

    //preset some data
    for (int r=0; r<n; r++)
    {
        for (int c=0; c<m; c++)
        {
            QChar val = this->matrix[r][c];
            QPoint pos = QPoint(c, r);
            if (val == 'x')
                this->wall << pos;
            if (val == 'r')
                this->mouse << pos;
            if (val != 'x')
                this->not_wall << pos;
        }
    }

    //template
    for (int dis=this->d; dis>=0; dis--)
    {
        for (int c=0; c<=dis; c++)
        {
            int r = dis - c;
            this->candidate_template << QPoint(c,r);//[r,c]
            this->candidate_template << QPoint(-r,c);//[c,-r]
            this->candidate_template << QPoint(-c,-r);//[-r,-c]
            this->candidate_template << QPoint(r,-c);//[-c,r]
        }
    }

    file.close();
}

WareHouse::~WareHouse()
{

}

QChar WareHouse::matrix_at( QPoint pos )
{
    return this->matrix[pos.y()][pos.x()];
}

QSet<QPoint> WareHouse::explosion_range( QPoint bomb_pos )
{
    QSet<QPoint> candidate = explosion_range_without_wall(bomb_pos);
    QSet<QPoint> elect;
    QSet<QPoint> walkable = candidate;
    //walkable.remove()
    return elect;
      //  elect = Set.new
        //walkable = Set.new(candidate)
}

QSet<QPoint> WareHouse::explosion_range_without_wall( QPoint bomb_pos )
{
    QSet<QPoint> range;
    foreach (QPoint pos , this->candidate_template)
    {
        QPoint trans_pos = bomb_pos + pos;
        if (QRect(0,0,m,n).contains(trans_pos))
            range<<trans_pos;
    }
    return range;
}
