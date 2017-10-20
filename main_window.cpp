#include "main_window.hpp"

MainWindow::MainWindow(QWidget * parent): QWidget(parent) {
    repl = new REPLWidget(this);
    canvas = new CanvasWidget(this);
    messagebox = new MessageWidget(this);
    interp = new QtInterpreter(this);
    
    //Set up connections between Qt Interpreter and widget
    QObject::connect(repl, &REPLWidget::lineEntered,
		   interp, &QtInterpreter::parseAndEvaluate);
    QObject::connect(interp, &QtInterpreter::drawGraphic,
		   canvas, &CanvasWidget::addGraphic);
    QObject::connect(interp, &QtInterpreter::info,
		   messagebox, &MessageWidget::info);
    QObject::connect(interp, &QtInterpreter::error,
		   messagebox, &MessageWidget::error);
    
    //Add widgets to layout
    auto layout = new QVBoxLayout;
    layout->addWidget(messagebox);
    layout->addWidget(canvas);
    layout->addWidget(repl);
    
    //Set layout
    setLayout(layout);
    
    //Set size of windows
    setMinimumSize(800,600);
}

MainWindow::~MainWindow() {
    delete messagebox;
}

MainWindow::MainWindow(std::string filename, QWidget * parent): QWidget(parent){
    repl = new REPLWidget(this);
    canvas = new CanvasWidget(this);
    messagebox = new MessageWidget(this);
    interp = new QtInterpreter(this);
    
    //Set up connections between Qt Interpreter and widget
    QObject::connect(repl, &REPLWidget::lineEntered,
		   interp, &QtInterpreter::parseAndEvaluate);
    QObject::connect(interp, &QtInterpreter::drawGraphic,
		   canvas, &CanvasWidget::addGraphic);
    QObject::connect(interp, &QtInterpreter::info,
		   messagebox, &MessageWidget::info);
    QObject::connect(interp, &QtInterpreter::error,
		   messagebox, &MessageWidget::error);
    
    //Add widgets to layout
    auto layout = new QVBoxLayout;
    layout->addWidget(messagebox);
    layout->addWidget(canvas);
    layout->addWidget(repl);
    
    //Set layout
    setLayout(layout);
    
    //Set size of windows
    setMinimumSize(800,600);
    
    interp->preLoadInterpreter(filename);
}