#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QtGui>
#include <vector>

class Draw : public QWidget
{
    Q_OBJECT

private:
    QPolygonF building;
    QPolygonF ch;
    QPolygonF er;
    std::vector<QPointF> points;
    std::vector<QPolygonF> polygons, chs, ers;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    QPolygonF getCH(){return ch;}
    QPolygonF getMAER(){return er;}
    QPolygonF getBuild(){return building;}
    void setCH(QPolygonF &ch_){ch=ch_;}
    void setMinimumAreaEnclosingRectangle(QPolygonF &er_){er=er_;}
    void clearAll();
    QPolygonF transformPolygon(QPolygonF &pol, double &x_trans, double &y_trans, double &x_ratio, double &y_ratio);
    void drawPolygons(std::vector<QPolygonF> &pols, double &x_trans, double &y_trans, double &x_ratio, double &y_ratio);
    std::vector<QPolygonF> getPolygons(){return polygons;}

signals:

public slots:
};

#endif // DRAW_H
