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

    // Add as a new vertex
    building.push_back(p);

    // Repaint screen
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{
    // Draw polygon
    QPainter painter(this);

    // Start draw
    painter.begin(this);

    // Draw polygon
    painter.drawPolygon(building);

    // Draw convex hull
    painter.setPen(Qt::red);
    painter.drawPolygon(ch);

    // Draw minimum area enclosing rectangle
    painter.setPen(Qt::green);
    painter.drawPolygon(er);

    // Draw polygons loaded from file - for each cycle
    for (QPolygonF polygon : Draw::buildings)
    {
        painter.setBrush(Qt::yellow);
        painter.drawPolygon(polygon);
    }

    // End draw
    painter.end();
}


void Draw::clearAll()
{
    // Clear all structures
    building.clear();
    er.clear();
    ch.clear();
    points.clear();
    buildings.clear();
    chs.clear();
    ers.clear();

}


QPolygonF Draw::transformPolygon(QPolygonF &pol, double &x_trans, double &y_trans, double &x_ratio, double &y_ratio)
{
    // Transform x,y of polygon by basic transformation based on minmax box of dataset
    // x_min, x_max, y_min, y_max - minmax box
    QPolygonF polygonTransformed;

    // For each point in polygon cycle
    for (QPointF p : pol)
    {
        // Translation with offset
        double dx = p.x()-x_trans;
        double dy = p.y()-y_trans;

        // Scale m
        double x0 = dx/x_ratio;
        double y0 = dy/y_ratio;

        QPointF point(x0, y0);
        polygonTransformed << point;
    }

    // Compute transformation key
    return polygonTransformed;
}


void Draw::drawPolygons(std::vector<QPolygonF> &pols, double &x_trans, double &y_trans, double &x_ratio, double &y_ratio)
{
    // Draw vector of polygons by pushing back to a polygons vector
    QPolygonF transformedPolygon;

    Draw::buildings.clear();
    for (QPolygonF pol : pols)
    {
        transformedPolygon = transformPolygon(pol, x_trans, y_trans, x_ratio, y_ratio);
        Draw::buildings.push_back(transformedPolygon);
    }

    repaint();
}

