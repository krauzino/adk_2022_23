#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <tuple>
#include "matrix.h"
#include <QtGui>

class Algorithms
{
public:
    Algorithms();

    double getEuclDistance(double x1, double y1, double x2, double y2);
    std::tuple<double, double, double> getPointLineDistance(double x, double y, double x1, double y1, double x2, double y2);
    std::tuple<double, double, double> getPointLineSegmentDistance(double x, double y, double x1, double y1, double x2, double y2);
    std::tuple<int, double, double, double> getNearestLineSegmentPoint(double xq, double yq, Matrix &X, Matrix &Y);
    Matrix createA(double alfa, double beta, double gamma, double h, int n);
    std::vector<QPointF> minEnergySpline1Element1Barrier(std::vector<QPointF> element,std::vector<QPointF> barrier, double alfa, double beta, double gamma, double lambda, double dmin, int iter);
    std::tuple<std::vector<QPointF>, std::vector<QPointF>> minEnergySpline2Elements(std::vector<QPointF> element1, std::vector<QPointF> element2, double alfa, double beta, double gamma, double lambda, double dmin, int iter);
    double getEx(double x, double y, double xn, double yn, double dmin);
    double getEy(double x, double y, double xn, double yn, double dmin);
    static std::vector<QPointF> transformPoints(std::vector<QPointF> &points, double &trans_x, double &trans_y, double &scale, int &offset_x, int &offset_y);
};

#endif // ALGORITHMS_H
