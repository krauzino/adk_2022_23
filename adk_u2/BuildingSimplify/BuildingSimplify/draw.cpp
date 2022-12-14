#include "draw.h"
#include "mainform.h"

#include <QtGui>
#include <QFileDialog>
#include <iostream>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::mousePressEvent(QMouseEvent *event)
{
    // Get x,y coordinate
    double x = event->pos().x();
    double y = event->pos().y();

    // Create new point
    QPointF p(x, y);

    // Add as new vertex
    building.push_back(p);

    // Repaint screen
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{
    // Draw polygon
    // Start draw
    QPainter painter(this);
    painter.begin(this);

    // Draw polygon
    painter.drawPolygon(building);

    // Draw polygons loaded from file
    for (QPolygonF polygon : Draw::buildings)
    {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        painter.drawPolygon(polygon);
    }

    // Draw convex hull
    painter.setPen(Qt::red);
    painter.setBrush(Qt::NoBrush);
    if (chs.size() > 0)
        for (QPolygonF CHs : chs)
            painter.drawPolygon(CHs)   ;

    // Draw enclosing rectangle
    painter.setPen(Qt::green);
    painter.setBrush(Qt::NoBrush);
    if (ers.size() > 0)
        for (QPolygonF ERs : ers)
            painter.drawPolygon(ERs);

    // End draw
    painter.end();
}


void Draw::clearAll()
{
    // Clear all
    building.clear();
    points.clear();
    buildings.clear();
    chs.clear();
    ers.clear();
}


void Draw::drawPolygons(std::vector<QPolygonF> &polygons, double &xtrans, double &ytrans, double &xratio, double &yratio)
{
    // Draw vector of polygons
    QPolygonF transPolygon;

    Draw::buildings.clear();
    for (QPolygonF pol : polygons)
    {
        transPolygon = transformPolygon(pol, xtrans, ytrans, xratio, yratio);
        Draw::buildings.push_back(transPolygon);
    }

    repaint();
}


QPolygonF Draw::transformPolygon(QPolygonF &polygon, double &xtrans, double &ytrans, double &xratio, double &yratio)
{
    // Transform x,y of polygon
    QPolygonF transPolygon;

    // Go through all points in polygon
    for (QPointF p : polygon)
    {
        // Translation
        double dx = p.x() - xtrans;
        double dy = p.y() - ytrans;

        // Scale m
        double x0 = dx/xratio;
        double y0 = dy/yratio;

        QPointF point(x0, y0);
        transPolygon << point;
    }

    // Compute transformation key
    return transPolygon;
}

