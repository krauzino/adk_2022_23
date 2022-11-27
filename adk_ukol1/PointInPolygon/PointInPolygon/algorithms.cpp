#include <cmath>
#include "algorithms.h"

int Algorithms::getPointLinePosition(QPointF &p1, QPointF &p2, QPointF &q)
{
    // Analyze point and line position
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
    // Gets the angle between two lines
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

int Algorithms::getPointAndPolygonPosition(QPointF &q, std::vector<QPointF> &pol)
{
    // Ray Crossing
    // Analyzes point and polygon position using Ray Crossing algorithm
    int k = 0, n = pol.size();

    double xir = pol[0].x() - q.x();
    double yir = pol[0].y() - q.y();

    // Process all vertices
    for (int i = 1; i <= n; i++)
    {
        // Reduces coordinates
        double x2ir = pol[i%n].x() - q.x();
        double y2ir = pol[i%n].y() - q.y();

        // Suitable segment
        if ((y2ir > 0) && (yir <=0) || (yir >0) && (y2ir <=0))
        {

            // Compute intersection
            double xm = (x2ir*yir - xir*y2ir)/(y2ir - yir);

            // Point is in the right half plane
            if (xm > 0)
                k++;
        }

        // Assign values
        xir = x2ir;
        yir = y2ir;
    }

    // Return amount of intersections
    return k%2;
}

int Algorithms::getPosWinding(QPointF &q, std::vector<QPointF> &pol)
{
    // Winding Number
    // Analyzes point and polygon position using Winding Number algorithm
    int n = pol.size();
    double omega_sum = 0;

    // Process all vertices
    for (int i = 0; i < n; i++)
    {
        // Computes angle between two lines
        double omega = getTwoLinesAngle(pol[i], q, pol[(i+1)%n], q);

        // Gets position of point and line
        int position = getPointLinePosition(q, pol[i], pol[(i+1)%n]);

        // If point is on the line
        if (position == -1)
        {
            // Coordinates of bounding box
            double xmin = 0, xmax = 0, ymin = 0, ymax = 0;

            // Tolerance
            double eps = 12;

            // Make bounding box
            if (pol[i].x() <= pol[(i+1)%n].x())
            {
                xmin = pol[i].x();
                xmax = pol[(i+1)%n].x();
            }
            else
            {
                xmin = pol[(i+1)%n].x();
                xmax = pol[i].x();
            }

            if (pol[i].y() <= pol[(i+1)%n].y())
            {
                ymin = pol[i].y();
                ymax = pol[(i+1)%n].y();
            }
            else
            {
                ymin = pol[(i+1)%n].y();
                ymax = pol[i].y();
            }

            // Point on the line
            if ((q.x() >= (xmin - eps)) && (q.x() <= (xmax + eps)) && (q.y() >= (ymin - eps)) && (q.y() <= (ymax + eps)))
                return -1;
        }

        // Point is in the left half plane
        if (position == 1)
            omega_sum += omega;

        // Point is in the right half plane
        else
            omega_sum -= omega;
    }

    // Point is inside the polygon
    double eps = 1.0e-4;
    if (fabs(fabs(omega_sum) - 2*M_PI) < eps)
        return 1;

    // Point is outside the polygon
    return 0;
}

std::vector<QPoint> Algorithms::getLocalCoordinates(QPointF &q, std::vector<QPointF> &pol)
{
    int n = pol.size();
    int x, y;
    std::vector<QPoint> v;

    // Process all vertices
    for (int i = 0; i < n; i++)
    {
        // Compute local coordinates
        x = pol[i].x() - q.x();
        y = pol[i].y() - q.y();

        // Create point from coordinates
        QPoint p(x,y);

        // Add point to vector
        v.push_back(p);
    }
    return v;
}


int Algorithms::processPols(QPointF &q, std::vector<QPolygon> &pols, QString &alg, std::vector<int> &res)

{
    // Stores position of point to vector
    std::vector<QPointF> points;
    int pos;
    int result = 0;
    std::vector<int> positions;

    // Process all polygons
    for (QPolygonF pol : pols)
    {
        // Empty vector of points
        points.clear();

        // Gets points from polygons
        for (QPointF point : pol)
        {
            points.push_back(point);
        }

        // Winding Number algorithm
        if (alg == "Winding Number")
        {
            pos = this->getPosWinding(q, points);
            res.push_back(pos);
        }
        // Ray Crossing algorithm
        else if (alg == "Ray Crossing")
        {
            pos = this->getPointAndPolygonPosition(q, points);
            res.push_back(pos);
        }

        // Store position of a point
        positions.push_back(pos);
    }

    return result;
}
