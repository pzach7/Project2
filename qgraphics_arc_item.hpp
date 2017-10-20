#ifndef QGRAPHICS_ARC_ITEM_HPP
#define QGRAPHICS_ARC_ITEM_HPP

#include <QGraphicsEllipseItem>
#include <QDebug>
#include <cmath>
#include <QPainter>
#include <QRectF>
#include <tuple>
#include "expression.hpp"

class QGraphicsArcItem : public QGraphicsEllipseItem {
  //Q_OBJECT

public:
    QGraphicsArcItem(QGraphicsEllipseItem * parent = nullptr);
    
    QGraphicsArcItem(Expression * arc);
  
    //CHANGE
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr);
    
private:
    double spanAngle;
    double startAngle;
    QRectF rect;
};

#endif