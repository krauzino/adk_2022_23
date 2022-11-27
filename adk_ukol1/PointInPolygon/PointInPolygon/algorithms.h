#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include <vector>
#include <draw.h>

class Algorithms
{
public:
    Algorithms(){};

    int getPointLinePosition(QPointF &p1, QPointF &p2, QPointF &q);
    double getTwoLinesAngle(QPointF &p1,QPointF &p2,QPointF &p3,QPointF &p4);
    int getPointAndPolygonPosition(QPointF &q, std::vector<QPointF> &pol); // Ray Crossing
    int getPosWinding(QPointF &q, std::vector<QPointF> &pol); // Winding Number
    std::vector<QPoint> getLocalCoordinates(QPointF &q, std::vector<QPointF> &pol);
    int processPols(QPointF &q, std::vector<QPolygon> &pols, QString &alg, std::vector<int> &res);
};

#endif // ALGORITHMS_H
