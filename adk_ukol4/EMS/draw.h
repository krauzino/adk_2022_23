#ifndef DRAW_H
#define DRAW_H

#include <QWidget>

class Draw : public QWidget
{ 
    Q_OBJECT

private:
    bool draw_element;
    std::vector<QPointF> element, barrier, displaced, displaced2, pointsElement, pointsBarrier;
    double scale;
    double trans_x, trans_y;
    int offset_x, offset_y;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void switchDrawnElement(){draw_element =! draw_element;}
    std::vector<QPointF>getElement(){return pointsElement;}
    std::vector<QPointF>getBarrier(){return pointsBarrier;}
    std::vector<QPointF>getDisplaced(){return displaced;}
    void setElement(std::vector<QPointF> &element_){element = element_;}
    void setBarrier(std::vector<QPointF> &barrier_){barrier = barrier_;}
    void setDisplaced(std::vector<QPointF> &displaced_){displaced = displaced_;}
    void setDisplaced2(std::vector<QPointF> &displaced2_){displaced2 = displaced2_;}

    void drawCSVPointsElement(std::vector<QPointF> &pointsElement);
    void drawCSVPointsBarrier(std::vector<QPointF> &pointsBarrier);
    void setCSVPointsElement(std::vector<QPointF> &csv_points){pointsElement.insert(pointsElement.end(), csv_points.begin(), csv_points.end());}
    void setCSVPointsBarrier(std::vector<QPointF> &csv_points){pointsBarrier.insert(pointsBarrier.end(), csv_points.begin(), csv_points.end());}
    double getScale(){return scale;}
    double getTransX(){return trans_x;}
    double getTransY(){return trans_y;}
    int getDeltaX(){return offset_x;}
    int getDeltaY(){return offset_y;}
    void setScale(double &scale_){scale = scale_;}
    void setTrans(double &trans_x_, double &trans_y_){trans_x = trans_x_; trans_y = trans_y_;}
    void setOffsets(int &offset_x_, int &offset_y_){offset_x = offset_x_; offset_y = offset_y_;}

    void clearElement(){element.clear();}
    void clearBarrier(){barrier.clear();}
    void clearDisplaced(){displaced.clear();}
    void clearDisplaced2(){displaced2.clear();}
    void clearPointsElement(){pointsElement.clear();}
    void clearPointsBarrier(){pointsBarrier.clear();}

signals:

public slots:
};

#endif // DRAW_H
