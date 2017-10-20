#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include "interpreter.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <QObject>
#include <QString>
#include <QGraphicsItem>
#include "qgraphics_arc_item.hpp"

class QtInterpreter : public QObject {
  Q_OBJECT

public:
    // Default construct an QtInterpreter with the default environment and an empty AST
    QtInterpreter(QObject * parent = nullptr);
    
    QGraphicsItem * makeGraphic(Expression * exp);

    void preLoadInterpreter(std::string filename);
    
public slots:
    // a public slot that accepts and expression string and parses/evaluates it
    void parseAndEvaluate(QString entry);  

signals:
    // a signal emitting a graphic to be drawn as a pointer
    void drawGraphic(QGraphicsItem * item);

    // a signal emitting an informational message
    void info(QString message);

    // a signal emitting an error message
    void error(QString message);
    
private:
    Interpreter interp;
};

#endif