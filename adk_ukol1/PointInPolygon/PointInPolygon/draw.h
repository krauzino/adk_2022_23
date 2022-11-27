#ifndef DRAW_H
#define DRAW_H
#include <QWidget>
#include <vector>
#include <iostream>

class Draw : public QWidget
{
    Q_OBJECT

private:
    bool mode;
    QPointF q;
    QPolygonF pol;
    std::vector<QPolygon> polygons;
    std::vector<QPoint> vertices;
    std::vector<int> polygonRes;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void clearScreen();
    QPolygonF getPolygon(){return pol;}
    QPointF getPoint(){return q;}
    std::vector<QPoint> getVertices(){return vertices;}
    std::vector<QPolygon> getPolygons(){return polygons;}
    void pushPolygon(QPolygon &pol){polygons.push_back(pol);}
    void drawVertices();
    void drawPolygons(std::vector<QPolygon> &pols);
    void addResults(std::vector<int> &results);
    void paintPolygon();
signals:

public slots:
};

#endif // DRAW_H
