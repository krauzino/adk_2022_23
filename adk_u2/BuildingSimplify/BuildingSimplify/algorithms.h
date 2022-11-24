#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <tuple>

class Algorithms
{
public:
    Algorithms();
    int getPointLinePosition(QPointF &p1, QPointF &p2, QPointF &q);
    double getTwoLinesAngle(QPointF &p1,QPointF &p2,QPointF &p3,QPointF &p4);
    std::vector <QPointF> resizeMinAreaEnclosingRectangle(std::vector <QPointF> &points, std::vector <QPointF> &rec);
    QPolygonF minAreaEnclosingRectangle(std::vector <QPointF> &points);
    QPolygonF createCH(std::vector <QPointF> &points);
    std::vector <QPointF> rotate(std::vector <QPointF> &points, double sig);
    double getArea(std::vector <QPointF> &points);
    std::tuple<std::vector<QPointF>, double> minMaxBox(std::vector <QPointF> &points);
    std::vector <QPointF> resizeRectangle(std::vector <QPointF> &points, std::vector <QPointF> &rec);
    QPolygonF wallAverage(std::vector <QPointF> &points);
    QPolygonF longestEdge(std::vector <QPointF> &points);
};

#endif // ALGORITHMS_H
