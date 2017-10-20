#ifndef CANVAS_WIDGET_HPP
#define CANVAS_WIDGET_HPP

#include <QWidget>
#include <QList>
#include <QDebug>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "qgraphics_arc_item.hpp"

class CanvasWidget: public QWidget {
  Q_OBJECT

public:
    // Default construct a CanvasWidget
    CanvasWidget(QWidget * parent = nullptr);

public slots:
    // A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
    // object derived from QGraphicsItem to draw
    void addGraphic(QGraphicsItem * item);
    
private:
    QGraphicsScene * scene;
    QGraphicsView * view;
};

#endif