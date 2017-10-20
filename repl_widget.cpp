#include "repl_widget.hpp"

REPLWidget::REPLWidget(QWidget * parent): QWidget(parent) {
   //Create label for the repl input
   QLabel * label = new QLabel("vtscript>  ");
   
   //Initialize textbox, hook up textbox to function
   //That emits input
   input = new QLineEdit(this);
   QObject::connect(input, &QLineEdit::returnPressed,
		   this, &REPLWidget::enterInput);
    
   
   //Format layout, add widgets
   auto layout = new QHBoxLayout;

   layout->addWidget(label);
   layout->addWidget(input);
   setLayout(layout);
   
   //Set up start for history of commands
   historyLocation = 0;
   history = {};
   
};

void REPLWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Up) {
        if (historyLocation >= 1) {
            QString pastCommand = history.at(historyLocation-1);
            input->clear();
            input->insert(pastCommand);
            if (historyLocation != 0) {
                historyLocation--;
            }
        }
    }
    else if (e->key() == Qt::Key_Down) {
        if (historyLocation < history.size()) {
            input->clear();
            if (historyLocation != history.size()-1) {
                QString recentCommand = history.at(historyLocation+1);
                input->insert(recentCommand);
            }
            historyLocation++;
        }
    }
}

void REPLWidget::enterInput() {   
    //Emit input, clear textbox
    emit lineEntered(input->text());
        //Increment history location
        
    historyLocation++;
    //Add command to history
    history.push_back(input->text());
    input->clear();
}