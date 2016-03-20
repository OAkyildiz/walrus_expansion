#include "walrus_widget/console.h"
#include <QGridLayout>


Console::Console(QWidget *parent,  qnode::QNode* qnode) : QFrame(parent)
{
   message_box_ = new QTextEdit() ;
   message_box_->setDisabled(true);

   scroll_ = new QScrollBar();


   input_ = new QLineEdit();



   QGridLayout* console_layout_ = new QGridLayout();

   console_layout_->addWidget(message_box_,0,0);
   console_layout_->addWidget(scroll_,0,1);
   console_layout_->addWidget(input_,1,0,1,2);


   console_layout_->setSpacing(0);
   console_layout_->setMargin(0);

   setLayout(console_layout_);
   setWindowOpacity(0.4);
}
Console::~Console(){

}
