#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

#include <vec2.h>

class GraphView : public QGraphicsView
{
public:
    GraphView(QWidget *parent);

    bool twoVecMode = false;
    Vec2 vec1;
    Vec2 vec2;
    int vecCount = 0;

    int max;
    int min;

    int cX;
    int cY;
    
    QPoint cornerTopRight;
    QPoint cornerTopLeft;
    QPoint cornerBottomLeft;
    QPoint cornerBottomRight;

    QPoint sideCenterRight;
    QPoint sideCenterTop;
    QPoint sideCenterLeft;
    QPoint sideCenterBottom;

    void init();

    void drawUnitSquare();
    void drawVectors();

    void reset();

    double normalize(int value);
    int scale(double value);
    double descale(double value);

protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif // GRAPHVIEW_H
