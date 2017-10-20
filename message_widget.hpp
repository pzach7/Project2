#ifndef MESSAGE_WIDGET_HPP
#define MESSAGE_WIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QPalette>
#include <memory>

class MessageWidget: public QWidget{
  Q_OBJECT

public:
    // Default construct a MessageWidget displaying no text
    MessageWidget(QWidget * parent = nullptr);
    ~MessageWidget();

public slots:
    // a public slot accepting an informational message to display, clearing any error formatting
    void info(QString message);

    // a public slot accepting an error message to display as selected text highlighted with a red background.
    void error(QString message);
    
private:
    QLineEdit * display;
};

#endif
