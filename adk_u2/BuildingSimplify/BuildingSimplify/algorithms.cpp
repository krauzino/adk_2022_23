#include "algorithms.h"

#include <cmath>
#include "sortpointsbyy.h"
#include "sortpointsbyx.h"

Algorithms::Algorithms()
{

}

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
    // Get the angle between two lines
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    // Dot product
    double dot = ux*vx + uy*vy;

    // Norms u,v
    double nu = sqrt(ux*ux + uy*uy);
    double vu = sqrt(vx*vx + vy*vy);

    return acos(dot/(nu*vu));
}


QPolygonF Algorithms::createCH(std::vector <QPointF> &points)
{
    // Create convex hull using Jarvis algorithm
    QPolygonF ch;

    // Search for pivot (y)
    QPointF q = *std::min_element(points.begin(), points.end(), SortPointsByY());

    // Add point to CH
    ch.push_back(q);

    // Search for pivot (x)
    QPointF p = *std::min_element(points.begin(), points.end(), SortPointsByX());

    // Create r
    QPointF r(0,q.y());

    // Assign points to r-pjj, q-pj
    QPointF pjj = r;
    QPointF pj = q;

    // Find all points of convex hull
    do
    {
        // Supplementary variables
        int imax = -1;
        double ommax = 0;

        // Browse all points of polygon
        for(int i = 0; i < points.size(); i++)
        {
            // Measure angle
            double om = getTwoLinesAngle(pj, pjj, pj, points[i]);

            // Update maximum
            if (om > ommax)
            {
                ommax = om;
                imax = i;
            }
        }

        // Point added to convex hull
        ch.push_back(points[imax]);

        // Update vertices
        pjj = pj;
        pj = points[imax];

    } while (pj != q);

    return ch;
}


std::vector <QPointF> Algorithms::rotate(std::vector <QPointF> &points, double sig)
{
    // Rotate polygon by angle
    std::vector <QPointF> points_r;

    // Process all vertices
    for(int i = 0; i < points.size(); i++)
    {
        // Rotate coordinates
        double xr = cos(sig)*points[i].x() - sin(sig)*points[i].y();
        double yr = sin(sig)*points[i].x() + cos(sig)*points[i].y();

        // Create point
        QPointF pr(xr, yr);

        // Add points to polygon
        points_r.push_back(pr);
    }

    return points_r;
}


double Algorithms::getArea(std::vector <QPointF> &points)
{
    // Compute polygon area using LH method
    int n = points.size();
    double area = 0;

    // Process all points
    for (int i = 0; i < n; i++)
        area += points[i].x()*(points[(i+1)%n].y() - points[(i-1+n)%n].y());

    return 0.5*fabs(area);
}


std::tuple<std::vector<QPointF>, double> Algorithms::minMaxBox(std::vector <QPointF> &points)
{
    // Create min-max box and compute its area
    QPointF px_min = *std::min_element(points.begin(), points.end(), SortPointsByX());
    QPointF px_max = *std::max_element(points.begin(), points.end(), SortPointsByX());
    QPointF py_min = *std::min_element(points.begin(), points.end(), SortPointsByY());
    QPointF py_max = *std::max_element(points.begin(), points.end(), SortPointsByY());

    // Min-max box vertices
    QPointF v1(px_min.x(),py_min.y());
    QPointF v2(px_max.x(),py_min.y());
    QPointF v3(px_max.x(),py_max.y());
    QPointF v4(px_min.x(),py_max.y());

    // Create min-max box polygon
    std::vector<QPointF> mmb;
    mmb.push_back(v1);
    mmb.push_back(v2);
    mmb.push_back(v3);
    mmb.push_back(v4);

    // Compute area of min-max box
    double area = getArea(mmb);

    return {mmb, area};
}


QPolygonF Algorithms::minAreaEnclosingRectangle(std::vector <QPointF> &points)
{
    // Create minimum area enclosing rectangle
    QPolygonF ch = createCH(points);

    // Initialize min-max box
    double sigma_min = 0;
    auto [mmb_min, area_min] = minMaxBox(points);

    // Process all segments of CH
    int n = ch.size();
    for(int i = 0; i < n; i++)
    {
        // Compute direction sigma
        double dx = ch[(i+1)%n].x() - ch[i].x();
        double dy = ch[(i+1)%n].y() - ch[i].y();
        double sigma = atan2(dy, dx);

        // Rotate polygon by -sigma
        std::vector<QPointF> points_r = rotate(points, -sigma);

        // Find new MMB
        auto [mmb,area] = minMaxBox(points_r);

        // Update min MMB
        if(area <= area_min)
        {
            mmb_min = mmb;
            area_min = area;
            sigma_min = sigma;
        }
    }

    // Convert MMB to MAER (minimum area enclosing rectangle)
    std::vector<QPointF> er = rotate(mmb_min, sigma_min);

    // Resized rectangle with same area
    std::vector<QPointF> err = resizeRectangle(points, er);

    // Create polygon
    QPolygonF er_pol;
    er_pol.push_back(err[0]);
    er_pol.push_back(err[1]);
    er_pol.push_back(err[2]);
    er_pol.push_back(err[3]);
    return er_pol;
}


std::vector <QPointF> Algorithms::resizeRectangle(std::vector <QPointF> &points, std::vector <QPointF> &er)
{
    // Resize rectangle to have the same area as the building
    // Area of building
    double areaB = getArea(points);

    if (areaB == 0)
        areaB = 1;

    // Area of enclosing rectangle
    double areaR = getArea(er);

    if (areaR == 0)
        areaR = 1;

    // Compute k
    double k = areaB/areaR;

    // Center of rectangle
    double xc = (er[0].x() + er[1].x() + er[2].x() + er[3].x())/4;
    double yc = (er[0].y() + er[1].y() + er[2].y() + er[3].y())/4;

    // 4 vectors
    double u1x = er[0].x() - xc;
    double u1y = er[0].y() - yc;
    double u2x = er[1].x() - xc;
    double u2y = er[1].y() - yc;
    double u3x = er[2].x() - xc;
    double u3y = er[2].y() - yc;
    double u4x = er[3].x() - xc;
    double u4y = er[3].y() - yc;

    // New coordinates of resized rectangle
    QPointF v1r(xc + sqrt(k)*u1x, yc + sqrt(k)*u1y);
    QPointF v2r(xc + sqrt(k)*u2x, yc + sqrt(k)*u2y);
    QPointF v3r(xc + sqrt(k)*u3x, yc + sqrt(k)*u3y);
    QPointF v4r(xc + sqrt(k)*u4x, yc + sqrt(k)*u4y);

    // Create new rectangle
    std::vector<QPointF> err;
    err.push_back(v1r);
    err.push_back(v2r);
    err.push_back(v3r);
    err.push_back(v4r);

    return err;
}


QPolygonF Algorithms::wallAverage(std::vector <QPointF> &points)
{
    // Initial direction
    double sigma1 = atan2(points[1].y() - points[0].y(), points[1].x() - points[0].x());

    // Average remainder
    double rAver = 0;
    double sumW  = 0;

    // Compute direction differences
    int n = points.size();
    for (int i = 0; i < n; i++)
    {
        // Direction
        double dxi = points[(i+1)%n].x() - points[i].x();
        double dyi = points[(i+1)%n].y() - points[i].y();
        double sigmai = atan2(dyi, dxi);

        // Direction differencies
        double d_sigmai = sigmai - sigma1;

        // Correct the quadrant
        if (d_sigmai < 0)
            d_sigmai += 2*M_PI;

        // Remainder
        double ki = round(2*d_sigmai/M_PI);
        double ri = d_sigmai - ki*(M_PI/2);

        // Length of a segment
        double leni = sqrt(dxi*dxi + dyi*dyi);

        // Weighted average, remainder
        rAver += leni*ri;
        sumW  += leni;
    }

    // Weighted average
    rAver /= sumW;

    // New direction
    sigma1 += rAver;

    // Rotate by -sigma
    std::vector<QPointF> points_r = rotate(points, -sigma1);

    // Find new MMB
    auto [mmb,area] = minMaxBox(points_r);

    // Convert min MMB to MAER
    std::vector<QPointF> er = rotate(mmb, sigma1);

    // Resized rectangle with the same area
    std::vector<QPointF> err = resizeRectangle(points, er);

    // Create polygon
    QPolygonF er_pol;
    er_pol.push_back(err[0]);
    er_pol.push_back(err[1]);
    er_pol.push_back(err[2]);
    er_pol.push_back(err[3]);

    return er_pol;
}


QPolygonF Algorithms::longestEdge(std::vector <QPointF> &points)
{
    // Create enclosing rectangle
    int n = points.size();
    std::vector<std::pair<double, double>> len_angle;

    // Length of each edge
    for(int i = 0; i < n; i++)
    {
        // Direction of edge
        double dxi = points[(i+1)%n].x() - points[i].x();
        double dyi = points[(i+1)%n].y() - points[i].y();
        double sigmai = atan2(dyi,dxi);

        // Length of edge
        double leni = sqrt(dxi*dxi + dyi*dyi);

        if (sigmai < 0)
            sigmai += 2*M_PI;
        len_angle.push_back(std::make_pair(leni, sigmai));
    }

    // Order lengths of edges
    std::sort(len_angle.begin(), len_angle.end());

    // Direction of longest edge
    double sigma1 = len_angle.back().second;

    // Rotate by -sigma
    std::vector<QPointF> points_r = rotate(points, -sigma1);

    // Find new MMB
    auto [mmb, area] = minMaxBox(points_r);

    // Convert MMB to MAER
    std::vector<QPointF> er = rotate(mmb, sigma1);

    // Resized rectangle with the same area
    std::vector<QPointF> err = resizeRectangle(points, er);

    // Create polygon
    QPolygonF er_pol;
    er_pol.push_back(err[0]);
    er_pol.push_back(err[1]);
    er_pol.push_back(err[2]);
    er_pol.push_back(err[3]);

    return er_pol;
}
