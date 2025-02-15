#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>
#include <list>
#include "qpoint3d.h"
#include "edge.h"
#include "triangle.h"

class Algorithms
{
public:
    Algorithms();
    int getPointLinePosition(const QPoint3D &p1,const QPoint3D &p2,const QPoint3D &q);
    double getTwoLinesAngle(const QPoint3D &p1,const QPoint3D &p2,const QPoint3D &p3,const QPoint3D &p4);
    int getNearestPoint(const QPoint3D &p, const std::vector<QPoint3D> &points);
    int getDelaunayPoint(const QPoint3D &p1, const QPoint3D &p2,const std::vector<QPoint3D> &points);
    std::vector<Edge> createDT(const std::vector<QPoint3D> &points);
    void updateAEL(const Edge &e, std::list<Edge> &ael);
    QPoint3D getContourPoint(const QPoint3D &p1, const QPoint3D &p2, double z);
    std::vector<Edge> createContourLines(const std::vector<Edge> &dt, double zmin, double zmax, double dz);
    double computeSlope(const QPoint3D &p1, const QPoint3D &p2, const QPoint3D &p3);
    std::vector<Triangle> analyzeSlope(const std::vector<Edge> &dt);
    double computeAspect(const QPoint3D &p1, const QPoint3D &p2,const QPoint3D &p3);
    std::vector<Triangle> analyzeAspect(const std::vector<Edge> &dt);
    static std::vector<QPoint3D> transformPoints(std::vector<QPoint3D> &points_3d, double &trans_x, double &trans_y, double &scale, int &offset_x, int &offset_y);
    static double getMinSlope(std::vector<Triangle> &triangles);
    static double getMaxSlope(std::vector<Triangle> &triangles);
};

#endif // ALGORITHMS_H
