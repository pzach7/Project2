#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <vector>
#include <QKeyEvent>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>

class REPLWidget: public QWidget{
  Q_OBJECT

public:
    // Default construct a REPLWidget
    REPLWidget(QWidget * parent = nullptr);

public slots:
    void enterInput();
    
protected:
    void keyPressEvent(QKeyEvent *e);
    
signals:
    // A signal that sends the current edited text as a QString when the return key is pressed.
    void lineEntered(QString);
    
private:
    QLineEdit * input;
    unsigned int historyLocation;
    std::vector<QString> history;
};

#endif