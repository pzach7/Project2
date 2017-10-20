#include "qgraphics_arc_item.hpp"

QGraphicsArcItem::QGraphicsArcItem (QGraphicsEllipseItem * parent): QGraphicsEllipseItem(parent) {
    //Just like, give it random stuff. you should never use this
    startAngle = 57.2958 * 3.14 * 16;
    rect = QRectF(0, 0, 10, 0);
}

QGraphicsArcItem::QGraphicsArcItem(Expression * arc) {
    //Find Radius to calculate bounding rectangle
    double radius = std::sqrt(pow(std::get<0>(arc->centEnd) - std::get<0>(arc->start),2) + 
                                pow(std::get<1>(arc->centEnd) - std::get<1>(arc->start),2));
                                
    //Bounding rectangle
    rect = QRectF(std::get<0>(arc->centEnd) - radius, std::get<1>(arc->centEnd) - radius, 
        radius * 2, radius * 2);
    
    //Convert to degrees
    //Arcs in Qpaint are measured in 1/16th of a degree, so multiply by 16
    startAngle = 57.2958 * atan2((std::get<1>(arc->start) - std::get<1>(arc->centEnd))*-1,
                        (std::get<0>(arc->start) - std::get<0>(arc->centEnd))) * 16;
 
    spanAngle = (57.2958 * 16 * arc->angle);

    
    this->setRect(rect);
    this->setStartAngle(startAngle);
    this->setSpanAngle(spanAngle);
}

void QGraphicsArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->drawArc( rect, startAngle, spanAngle );
}