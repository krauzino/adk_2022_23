#ifndef SORTPOINTSBYX_H
#define SORTPOINTSBYX_H

#include <QtGui>

class SortPointsByX
{
public:
    SortPointsByX();
    bool operator () (QPointF &p, QPointF &q)
    {
        return p.x() < q.x() || (p.x() == q.x()) && (p.y() < q.y());
    }
};

#endif // SORTPOINTSBYX_H
