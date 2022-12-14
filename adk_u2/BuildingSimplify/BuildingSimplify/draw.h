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
    std::vector<QPointF> points;
    std::vector<QPolygonF> buildings, chs, ers;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void clearAll();
    void setCH(QPolygonF &ch_){chs.push_back(ch_);}
    void setMAER(QPolygonF &er_){ers.push_back(er_);} // MAER - Minimum Area Enclosing Rectangle
    void clearCH(){chs.clear();}
    void clearMAER(){ers.clear();}
    std::vector<QPointF> getPoints(){return points;}
    std::vector<QPolygonF> getPolygons(){return buildings;}
    void drawPolygons(std::vector<QPolygonF> &polygons, double &xtrans, double &ytrans, double &xratio, double &yratio);
    QPolygonF transformPolygon(QPolygonF &polygon, double &xtrans, double &ytrans, double &xratio, double &yratio);

signals:

public slots:
};

#endif // DRAW_H
