#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "qt_interpreter.hpp"

#include <QWidget>
#include <QLayout>

class MainWindow: public QWidget{
  Q_OBJECT

public:
    // Default construct a MainWindow
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

    // Default construct a MainWidow, using filename as the script file to attempt to preload
    MainWindow(std::string filename, QWidget * parent = nullptr);

private:
    REPLWidget * repl;
    CanvasWidget * canvas;
    MessageWidget * messagebox;
    QtInterpreter * interp;
};

#endif