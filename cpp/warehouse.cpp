#include "warehouse.h"

WareHouse::WareHouse(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    Q_ASSERT(file.exists());

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

QSet<QPoint> WareHouse::explosion_range( QPoint bomb_pos ) const
{
    QSet<QPoint> candidate = explosion_range_without_wall(bomb_pos) - this->wall;
    QSet<QPoint> elect;
    QSet<QPoint> walkable = candidate;

    while (true)
    {
        if (candidate.isEmpty())
            break;

        QPoint sp = bomb_pos, ep = *candidate.begin();
        
        QVector<QPoint> path = a_star(sp, ep, walkable);
        
        if (path.isEmpty())
        {
            candidate.remove(ep);
            candidate.remove(sp);
            elect << sp;
            continue;
        }
        else
        {
            for (int step=0; step<path.size(); step++)
            {
                QPoint pos = path[step];
                candidate.remove(pos);
                if (step <= this->d)
                    elect << pos;
            }
        }
    }
    
    return elect;
}

QSet<QPoint> WareHouse::explosion_range_without_wall( QPoint bomb_pos ) const
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

class ANode{
public:
    ANode(int _g=0, int _h=0, QPoint _d=QPoint())
    {
        g=_g; h=_h; d = _d;
    }
    int g; int h; QPoint d;
};

QVector<QPoint> WareHouse::a_star( QPoint sp, QPoint ep, QSet<QPoint> walkable) const 
{
    //trick: exchange sp and ep
    QPoint temp = sp;
    sp = ep; ep = temp;

    //init g and h
    QMap<QPoint, ANode> nodes;
    foreach (QPoint pos, walkable)
    {
        int g = this->n * this->m;
        int h = abs(pos.x() - ep.x()) + abs(pos.y() - ep.y());
        nodes[pos] = ANode(g,h);
    }

    //searching
    QSet<QPoint> open_list, close_list;
    nodes[sp].g = 0;
    open_list << sp;
    while (!open_list.isEmpty())
    {
        //find the min item(key, node) in open_list
        QPoint key;
        ANode node = ANode(this->m * this->n);
        foreach (QPoint k, open_list)
        {
            int step1 = nodes[k].g + nodes[k].h;
            int step2 = node.g + node.h;
            if (step1 < step2)
            {
                key = k;
                node = nodes[k];
            }
        }

        //handle (key,node)
        int r=key.y(), c = key.x();
        open_list.remove(key);
        close_list << key;
        if (key == ep)
            break;

        //neighbor
        QPoint dirs[4] = {QPoint(0,1),QPoint(0,-1),QPoint(1,0),QPoint(-1,0)};
        for (int i=0; i<4; i++)
        {
            QPoint next_d = dirs[i];
            int nr = r + next_d.y(), nc = c + next_d.x();
            QPoint nkey = QPoint(nc,nr);
            
            //ignore
            if ( (!walkable.contains(nkey)) || close_list.contains(nkey) )
                continue;
            int next_g = node.g + 1;
            ANode* next_node = &nodes[nkey];

            //already in openlist
            if (open_list.contains(nkey))
            {
                if (next_g < next_node->g)
                {
                    next_node->g = next_g;
                    next_node->d = next_d;
                }
            }
            //not in openlist
            else
            {
                next_node->g = next_g;
                next_node->d = next_d;
                open_list << nkey;
            }
        }
    }

    //return path from close list
    if (!close_list.contains(ep))
        return QVector<QPoint>();
    else{
        QPoint pos = ep;
        ANode node = nodes[pos];
        QVector<QPoint> ret;
        while (true)
        {
            ret << pos;
            if (pos == sp)
                break;
            pos -= node.d;
            node = nodes[pos];
        }
        return ret;
    }
}

uint qHash(const QPoint &point)  
{
    return point.x()*10000 + point.y();
}

bool operator<(const QPoint& lhs, const QPoint& rhs)
{
    if (lhs.x() < rhs.x())
        return true;
    else if (lhs.x() == rhs.x())
        return lhs.y() < rhs.y();
    else
        return false;
}
