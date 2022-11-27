#include <QtGui>
#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    mode = true;
    q.setX(-100);
    q.setY(-100);
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    // Get x,y coordinate
    double x = event->pos().x();
    double y = event->pos().y();
    q.setX(x);
    q.setY(y);

    // Repaint screen
    repaint();
}

void Draw::paintEvent(QPaintEvent *event)
{
    //Draw polygon
    QPainter painter(this);

    //Start draw
    painter.begin(this);

    //Draw polygon
    painter.drawPolygon(pol);

    // Color
    QBrush highlight;
    highlight.setColor(Qt::blue);
    highlight.setStyle(Qt::CrossPattern);
    QPainterPath path;

    // Draw all polygons
    for (int i = 0; i < polygons.size(); i++)
    {
        painter.drawPolygon(polygons[i]);
    }

    // Highlight polygons with point inside
    for(int i = 0; i < polygonRes.size(); i++)
    {
        if (polygonRes[i] != 0)
        {
            path.addPolygon(polygons[i]);
            painter.fillPath(path, highlight);
            painter.drawPolygon(polygons[i]);
        }
    }

    // Draw point
    double r = 3; // px
    painter.drawEllipse(q.x()-r, q.y()-r, 2*r, 2*r);

    // End draw
    polygonRes.clear();
    painter.end();

}

void Draw::drawPolygons(std::vector<QPolygon> &pols)
{
    // Draw polygons
    vertices.clear();
    polygons.clear();
    for (QPolygon pol : pols)
        polygons.push_back(pol);
    repaint();
}

void Draw::addResults(std::vector<int> &results)
{
    // Add results to set highlighted polygons
    for (int result : results) polygonRes.push_back(result);
}

void Draw::clearScreen()
{
    // Clear screen
    pol.clear();
    repaint();
}
