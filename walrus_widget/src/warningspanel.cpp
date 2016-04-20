#include "walrus_widget/warningspanel.h"

WarningsPanel::WarningsPanel(QWidget *parent) : QFrame(parent),
    warnings_keys_(0)
{
    warnings_layout_ = new QHBoxLayout;

    warnings_layout_->setMargin(0);
    warnings_layout_->setSpacing(0);
    setLayout(warnings_layout_);
}

void WarningsPanel::addWarning(std::string name, QString image)
{

    warnings_dict_[name] = new Warning(0,QString::fromStdString(name),image);
    warnings_keys_.push_back(name);

}

void WarningsPanel::showWarning(std::string name)

{

    warnings_layout_->addWidget(warnings_dict_[name]);

    warnings_dict_[name]->update(1);
}

void WarningsPanel::hideWarning(std::string name)
{
    warnings_dict_[name]->update(0);
    //warnings_dict_[name]->hide(); //show() might increase performance, add

    warnings_layout_->removeWidget(warnings_dict_[name]);
}

void WarningsPanel::resizeEvent(QResizeEvent *event){

   if(!warnings_keys_.empty()){
    for(std::vector<std::string>::iterator name = warnings_keys_.begin(); name != warnings_keys_.end(); ++name) {
        warnings_dict_[*name]->resize(height(),height());
        }
    }
}
