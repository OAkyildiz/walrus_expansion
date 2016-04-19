#include "walrus_widget/indicatorspanel.h"

IndicatorsPanel::IndicatorsPanel(QWidget* parent, QBoxLayout::Direction dir) : QFrame(parent),
    indicators_keys_(0)
{
    indicators_layout_ = new QBoxLayout(dir);

    indicators_layout_->setSpacing(0);
    setLayout(indicators_layout_);
}

void IndicatorsPanel::addIndicator(Indicator* indic)
{
    std::string std_name = indic->name().toStdString();
    indicators_dict_[std_name] = indic;
    indicators_layout_->addWidget(indic);
    indicators_keys_.push_back(std_name);
}

void IndicatorsPanel::addIndicator(std::string name, QString image)
{
    indicators_dict_[name] = new Indicator(0, QString::fromStdString(name),image);
    indicators_layout_->addWidget(indicators_dict_[name]);
    indicators_keys_.push_back(name);

}

void IndicatorsPanel::resizeEvent(QResizeEvent *event)
{
    if(!indicators_keys_.empty()){
        for(std::vector<std::string>::iterator name = indicators_keys_.begin(); name != indicators_keys_.end(); ++name) {
            //indicators_layout_->removeWidget(indicators_dict_[*name]);
            indicators_dict_[*name]->resize(width(), width());
            //indicators_layout_->addWidget(indicators_dict_[*name]);

        }
    }
}
