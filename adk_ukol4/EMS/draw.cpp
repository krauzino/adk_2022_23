#include "draw.h"
#include "algorithms.h"
#include <QtGui>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    draw_element = true;
}


void Draw::mousePressEvent(QMouseEvent *event)
{

    // Get x,y coordinates
    double x = event->pos().x();
    double y = event->pos().y();

    // Create new point
    QPointF p(x,y);

    // Add point to the element
    if (draw_element)
        element.push_back(p);

    // Add point to the barrier
    else
        barrier.push_back(p);

    // Repaint
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{
    // Draw line
    QPainter painter(this);

    // Start draw
    painter.begin(this);

    // Draw element from loaded file
    painter.setPen(Qt::blue);
    for(int i = 0; (i < pointsElement.size()-1) && (pointsElement.size() > 1) ; i++)
        painter.drawLine(pointsElement[i].x(),pointsElement[i].y(),pointsElement[i+1].x(),pointsElement[i+1].y());

    // Draw barrier from loaded file
    painter.setPen(Qt::red);
    for(int i = 0; (i < pointsBarrier.size()-1) && (pointsBarrier.size() > 1) ; i++)
        painter.drawLine(pointsBarrier[i].x(),pointsBarrier[i].y(),pointsBarrier[i+1].x(),pointsBarrier[i+1].y());

    // Draw displaced
    painter.setPen(Qt::green);
    for(int i = 0; (i < displaced.size()-1) && (displaced.size() > 1); i++)
        painter.drawLine(displaced[i].x(),displaced[i].y(),displaced[i+1].x(),displaced[i+1].y());

    // Draw displaced2
    painter.setPen(Qt::yellow);
    for(int i = 0; (i < displaced2.size()-1) && (displaced2.size() > 1); i++)
        painter.drawLine(displaced2[i].x(),displaced2[i].y(),displaced2[i+1].x(),displaced2[i+1].y());

    // End draw
    painter.end();
}


void Draw::drawCSVPointsElement(std::vector<QPointF> &pointsElement)
{
    // Get transformation parameters
    double trans_x = getTransX();
    double trans_y = getTransY();
    double scale = getScale();
    int delta_x = getDeltaX();
    int delta_y = getDeltaY();

    // Draw vector of points of element
    std::vector<QPointF> transformedPoints = Algorithms::transformPoints(pointsElement, trans_x, trans_y, scale, delta_x, delta_y);
    Draw::setCSVPointsElement(transformedPoints);

    repaint();
}


void Draw::drawCSVPointsBarrier(std::vector<QPointF> &pointsBarrier)
{
    //Get transformation parameters
    double trans_x = getTransX();
    double trans_y = getTransY();
    double scale = getScale();
    int delta_x = getDeltaX();
    int delta_y = getDeltaY();

    // Draw vector of points of barrier
    std::vector<QPointF> transformedPoints = Algorithms::transformPoints(pointsBarrier, trans_x, trans_y, scale, delta_x, delta_y);
    Draw::setCSVPointsBarrier(transformedPoints);

    repaint();
}
