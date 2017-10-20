#include "qt_interpreter.hpp"

QtInterpreter::QtInterpreter(QObject * parent) : QObject(parent) {
    interp = Interpreter();
}

QGraphicsItem * QtInterpreter::makeGraphic(Expression * exp) {
    if (exp->type == typeArc) {
        auto arc = new QGraphicsArcItem(exp);
        return arc;
    }
    else if (exp->type == Line) {
        auto line = new QGraphicsLineItem(std::get<0>(exp->start), 
                    std::get<1>(exp->start), std::get<0>(exp->centEnd), 
                    std::get<1>(exp->centEnd));
        return line;
    }
    // (exp.type == Point)
    auto point = new QGraphicsEllipseItem(std::get<0>(exp->start),std::get<1>(exp->start),2,2);
    return point;
}

void QtInterpreter::preLoadInterpreter(std::string filename) {
    std::ifstream file(filename);
    bool parseOkay = interp.parse(file);
    if (parseOkay) {
        Expression result;
        try {
            result = interp.eval();
        }
        catch (InterpreterSemanticError msg) {
            emit error(QString(msg.what()));
            std::string error = "Error";
            result = Expression(error);
        }
        if ((result.type != None || result.children.size() != 0) && result.stringValue != "Error") {
            //std::cout << "(" << result.stringValue << ")" << std::endl;
            //emit info(QString::fromStdString("(" + result.stringValue + ")"));
            //Create and emit any graphics that need to be made
            for (auto i : result.children) {
                if (i->children.size() != 0) {
                    for (auto j : i->children) {
                        emit drawGraphic(makeGraphic(j));
                    }
                }
                else {
                    emit drawGraphic(makeGraphic(i));
                }
            }
        }
    }
    else {
        emit error(QString("Error: could not parse expression"));
    }
}

void QtInterpreter::parseAndEvaluate(QString entry){
    std::string input = entry.toStdString();
    std::istringstream file(input);
    bool parseOkay = interp.parse(file);
    if (parseOkay) {
        Expression result;
        try {
            result = interp.eval();
        }
        catch (InterpreterSemanticError msg) {
            emit error(QString(msg.what()));
            std::string error = "Error";
            result = Expression(error);
        }
        if ((result.type != None || result.children.size() != 0) && result.stringValue != "Error") {
            std::cout << "(" << result.stringValue << ")" << std::endl;
            emit info(QString::fromStdString("(" + result.stringValue + ")"));
            //Create and emit any graphics that need to be made
            for (auto i : result.children) {
                if (i->children.size() != 0) {
                    for (auto j : i->children) {
                        emit drawGraphic(makeGraphic(j));
                    }
                }
                else {
                    emit drawGraphic(makeGraphic(i));
                }
            }
        }
    }
    else {
        emit error(QString("Error: could not parse expression"));
    }
} 