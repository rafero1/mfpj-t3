#include "graphview.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include <string>
#include <iostream>

GraphView::GraphView(QWidget *parent) : QGraphicsView (parent)
{
    init();
}

void GraphView::init()
{
    twoVecMode = false;

    cX = int(width()/2);
    cY = int(height()/2);

    cornerTopRight    = QPoint(cX+cX/2, cY/2);
    cornerTopLeft     = QPoint(cX/2,    cY/2);
    cornerBottomLeft  = QPoint(cX/2,    cY+cY/2);
    cornerBottomRight = QPoint(cX+cX/2, cY+cY/2);

    sideCenterRight   = QPoint(cX+cX/2, cY);
    sideCenterLeft    = QPoint(cX/2,    cY);
    sideCenterTop     = QPoint(cX,      cY/2);
    sideCenterBottom  = QPoint(cX,      cY+cY/2);

    min = cornerTopLeft.rx();
    max = cornerBottomRight.ry();
}

double GraphView::normalize(int value)
{
    return (value - min)/max-min;
}

int GraphView::scale(double value)
{
    return int((value-(-1.0)) / (1.0-(-1.0)) * (max -min) + (min));
}

double GraphView::descale(double value)
{
    //return ((value-min) / (max-min)) * (1 -(-1.0)) + (-1.0);
    return (value-min) / (max-min) * (1.0 -(-1.0)) + (-1.0);
}

void GraphView::drawUnitSquare()
{
    // Linha vertical
    scene()->addLine(cX, 0, cX, scene()->height());

    // Linha horizontal
    scene()->addLine(0, cY, scene()->width(), cY);

    // Quadrado
    scene()->addRect(cornerTopLeft.rx(), cornerTopLeft.ry(), cX, cY);
}

void GraphView::reset()
{
    // reseta a cena
    scene()->clear();
    drawUnitSquare();
    vec1 = Vec2();
    vec2 = Vec2();
    vecCount = 0;
}

void GraphView::drawVectors()
{
    QPen p (Qt::blue);
    p.setWidth(2);

    if (vec1.notNull())
    {
        qDebug() << "vec1.x: " << vec1.x << " vec1.y: " << vec1.y;

        // transforma os doubles em valores int novamente para desenhar
        int x = scale(vec1.x);
        int y = scale(-vec1.y); // lembra que no Qt o y é positivo pra baixo

        // desenha linha do vetor na cena
        scene()->addLine(cX, cY, x, y, p);
        scene()->addEllipse(x-5, y-5, 10, 10, p, QBrush(Qt::blue));

        // desenha linha do vetor normalizado na cena
        p.setColor(Qt::darkBlue);
        Vec2 pav = vec1.pseudoangleVec();
        scene()->addLine(cX, cY, scale(pav.x), scale(-pav.y), p);
        scene()->addEllipse(scale(pav.x)-5, scale(-pav.y)-5, 10, 10, p, QBrush(Qt::darkBlue));

        // texto
        std::string sx = std::to_string(vec1.x);
        std::string sy = std::to_string(-vec1.y);
        QString text;
        text.append("x: ");
        text.append(QString::fromStdString(sx));
        text.append("\ny: ");
        text.append(QString::fromStdString(sy));
        QGraphicsTextItem* gText = scene()->addText(text);
        gText->setPos(x+10, y);
    }

    if (vec2.notNull())
    {
        qDebug() << "vec2.x: " << vec2.x << " vec2.y: " << vec2.y;

        // transforma os doubles em valores int novamente para desenhar
        int x = scale(vec2.x);
        int y = scale(-vec2.y); // lembra que no Qt o y é positivo pra baixo

        // desenha linha do vetor na cena
        p.setColor(Qt::green);
        scene()->addLine(cX, cY, x, y, p);
        scene()->addEllipse(x-5, y-5, 10, 10, p, QBrush(Qt::green));

        // desenha linha do vetor normalizado na cena
        p.setColor(Qt::darkGreen);
        Vec2 pav = vec2.pseudoangleVec();
        scene()->addLine(cX, cY, scale(pav.x), scale(-pav.y), p);
        scene()->addEllipse(scale(pav.x)-5, scale(-pav.y)-5, 10, 10, p, QBrush(Qt::darkGreen));

        // texto
        std::string sx = std::to_string(vec2.x);
        std::string sy = std::to_string(-vec2.y);
        QString text;
        text.append("x: ");
        text.append(QString::fromStdString(sx));
        text.append("\ny: ");
        text.append(QString::fromStdString(sy));
        QGraphicsTextItem* gText = scene()->addText(text);
        gText->setPos(x+10, y);
    }

    if (!twoVecMode)
    { // Um vetor
        p.setColor(Qt::red);

        // pseudo-angulo
        double pa = vec1.pseudoangle();
        qDebug() << "pseudo-angulo: " << pa;
        int i = vec1.oct();

        QLine l (sideCenterRight, sideCenterRight);
        if (i > 1)
        {
            l.setPoints(sideCenterRight, cornerTopRight);
            scene()->addLine(l, p);
        }
        if (i > 2)
        {
            l.setPoints(cornerTopRight, sideCenterTop);
            scene()->addLine(l, p);
        }
        if (i > 3)
        {
            l.setPoints(sideCenterTop, cornerTopLeft);
            scene()->addLine(l, p);
        }
        if (i > 4)
        {
            l.setPoints(cornerTopLeft, sideCenterLeft);
            scene()->addLine(l, p);
        }
        if (i > 5)
        {
            l.setPoints(sideCenterLeft, cornerBottomLeft);
            scene()->addLine(l, p);
        }
        if (i > 6)
        {
            l.setPoints(cornerBottomLeft, sideCenterBottom);
            scene()->addLine(l, p);
        }
        if (i > 7)
        {
            l.setPoints(sideCenterBottom, cornerBottomRight);
            scene()->addLine(l, p);
        }
        Vec2 pav = vec1.pseudoangleVec();
        l.setPoints(l.p2(), QPoint(scale(pav.x), scale(-pav.y)));
        scene()->addLine(l, p);

        // texto
        int x = scale(vec1.x);
        int y = scale(-vec1.y);
        std::string pseudoText = std::to_string(pa);
        QString text;
        text.append("angulo: ");
        text.append(QString::fromStdString(pseudoText));
        QGraphicsTextItem* gText = scene()->addText(text);
        gText->setPos(x+10, y-12);
    } else
    { // Dois vetores
        p.setColor(Qt::red);

        // pseudo-angulo entre vetores
        if (vecCount == 2)
        {
            qDebug() << "pseudo-angulo vec1: " << vec1.pseudoangle();
            qDebug() << "pseudo-angulo vec2: " << vec2.pseudoangle();
            double pa = vec2.pseudoangleBetween(vec1);
            qDebug() << "pseudo-angulo entre vetores: " << pa;

            // texto
            int x = scale(vec2.x);
            int y = scale(-vec2.y);
            std::string pseudoText = std::to_string(pa);
            QString text;
            text.append("angulo: ");
            text.append(QString::fromStdString(pseudoText));
            QGraphicsTextItem* gText = scene()->addText(text);
            gText->setPos(x+10, y-12);
        }
    }
}

void GraphView::mousePressEvent(QMouseEvent *e)
{
    double mx = e->pos().x();
    double my = e->pos().y();
    Vec2 vec (descale(mx), -descale(my));
    qDebug() << "mouse x: " << mx << " mouse y: " << my;

    if (!twoVecMode)
    {
        reset();
        vec1 = vec;
    }
    else
    {
        if (vecCount == 0)
        {
            vec1 = vec;
        }
        else if(vecCount == 1)
        {
            vec2 = vec;
        }
        else if (vecCount == 2)
        {
            reset();
            vec1 = vec;
        }

    }
    vecCount++;
    drawVectors();
}
