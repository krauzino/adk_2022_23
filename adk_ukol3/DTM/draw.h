#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include "qpoint3d.h"
#include "edge.h"
#include "triangle.h"

class Draw : public QWidget
{
    Q_OBJECT

private:

    std::vector <QPoint3D> points;
    std::vector <Edge> dt;
    std::vector <Edge> contours;
    std::vector <Triangle> triangles;
    double scale;
    double trans_x, trans_y;
    int offset_x, offset_y;
    double minSlope, maxSlope;
    bool isSlope;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    std::vector <QPoint3D> getPoints(){return points;}
    std::vector <Edge> getDT(){return dt;}
    void setPoints(const std::vector <QPoint3D> &points_){points = points_;}
    void setDT(const std::vector <Edge> &dt_){dt = dt_;} 
    void setContours(const std::vector <Edge> &contours_){contours = contours_;}
    void setTriangles(const std::vector<Triangle> &triangles_){triangles = triangles_;}
    void clearContours(){contours.clear();}
    void clearTriangles(){triangles.clear();}
    void clearPoints(){points.clear();}
    void clearDT(){dt.clear();}
    void drawCSVPoints(std::vector<QPoint3D> &points_3d);
    void setCSVPoints(std::vector<QPoint3D> &csv_points){points.insert(points.end(), csv_points.begin(), csv_points.end());}
    void setScale(double &scale_){scale = scale_;}
    void setTrans(double &trans_x_, double &trans_y_){trans_x = trans_x_; trans_y = trans_y_;}
    void setOffsets(int &offset_x_, int &offset_y_){offset_x = offset_x_; offset_y = offset_y_;}
    double getScale(){return scale;}
    double getTransX(){return trans_x;}
    double getTransY(){return trans_y;}
    int getDeltaX(){return offset_x;}
    int getDeltaY(){return offset_y;}
    void setMinSlope(double min){minSlope = min;}
    void setMaxSlope(double max){maxSlope = max;}
    void switchSlope(){isSlope =! isSlope;}

signals:

public slots:
};

#endif // DRAW_H
