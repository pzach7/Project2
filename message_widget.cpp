#include "message_widget.hpp"

MessageWidget::MessageWidget(QWidget * parent): QWidget(parent) {
   QLabel * label = new QLabel("Message: ");
   display = new QLineEdit(this);
   display->setReadOnly(true);
   
   auto layout = new QHBoxLayout;

   layout->addWidget(label);
   layout->addWidget(display);
   setLayout(layout);
};

MessageWidget::~MessageWidget(){
    delete display;
}

void MessageWidget::info(QString message){
    QPalette palette = QPalette();
    display->setPalette(palette);
    
    display->setText(message);
}

    // a public slot accepting an error message to display as selected text highlighted with a red background.
void MessageWidget::error(QString message){
    QPalette palette = QPalette(Qt::red);
    palette.setColor(QPalette::Highlight,Qt::red);
    display->setPalette(palette);
    
    display->setText(message);
    display->selectAll();
}