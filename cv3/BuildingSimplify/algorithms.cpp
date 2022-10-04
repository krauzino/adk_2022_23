#include "algorithms.h"
#include "sortpointsbyy.h"
#include "sortpointsbyx.h"

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPointF &p1, QPointF &p2, QPointF &q)
{
    //Analyze point and line position
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    // Determinant
    double t = ux*vy - uy*vx;

    // Left half plane
    if (t > 0)
        return 1;

    // Right half plane
    else if (t < 0)
        return 0;

    // On the line
    return -1;

}


double Algorithms::getTwoLinesAngle(QPointF &p1,QPointF &p2,QPointF &p3,QPointF &p4)
{
    //Gets the angle between 2 lines
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    // Dot product
    double dot = ux*vx+uy*vy;

    // Norms u,v
    double nu = sqrt(ux*ux+uy*uy);
    double vu = sqrt(vx*vx+vy*vy);

    return acos(dot/(nu*vu));
}

QPolygonF Algorithms::createCH(QPolygonF &pol)
{
    //Create convex hull using Jarvis algorithm
    QPolygonF ch;

    //Search for pivot
    QPointF q = *std::min_element(pol.begin(), pol.end(), SortPointsByY());

    // Add point to CH
    ch.push_back(q);

    // Search for pivot (x)
    QPointF p = *std::min_element(pol.begin(), pol.end(), SortPointsByX());

    //Create r
    QPointF r(p.x(),q.y());

    // Assign points to r-pjj, q-pj
    QPointF pjj = r;
    QPointF pj = q;

    // Find all points of convex hull
    do {
        // Supplementary variables
        int imax = -1;
        double omax = 0;
    } while (pj!=q);



}
