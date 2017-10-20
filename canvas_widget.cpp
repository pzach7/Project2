#include "canvas_widget.hpp"

CanvasWidget::CanvasWidget(QWidget * parent): QWidget(parent) {
    scene = new QGraphicsScene(this);
 
    view = new QGraphicsView(this);
    view->setScene(scene);
    //Make Read-only
    view->setInteractive(false);
    
    //Add view to layout
    auto layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}

//Adds given item to display
void CanvasWidget::addGraphic(QGraphicsItem * item){
    scene->addItem(item);
    scene->update();
}