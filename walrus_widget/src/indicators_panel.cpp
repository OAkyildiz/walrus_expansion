#include "walrus_widget/indicators_panel.h"

IndicatorsPanel::IndicatorsPanel(QWidget* parent,  QString name, QBoxLayout::Direction dir) : QFrame(parent),
    //indicators_(0),
    names_(0)

{
    indicators_layout_ = new QBoxLayout(dir);
    indicators_layout_->setSpacing(3);
    SetLayoutAlignment();
    setLayout(indicators_layout_);
}

void IndicatorsPanel::addIndicator(BaseIndicator* indic)
{

    indicators_layout_->addWidget(indic, _alignment);
    //indicators_.push_back(indic);
    names_.push_back(indic->name());
}

//void IndicatorsPanel::addIndicator(std::string name, QString image)
//{
//    indicators_dict_[name] = new BaseIndicator(0, QString::fromStdString(name),image);
//    indicators_layout_->addWidget(indicators_dict_[name]);
//    indicators_keys_.push_back(name);
//
//}

void IndicatorsPanel::SetLayoutAlignment()
{
    QBoxLayout::Direction dir = indicators_layout_->direction();

    if (dir == QBoxLayout::LeftToRight )
        _alignment = Qt::AlignLeft;
    else if (dir == QBoxLayout::RightToLeft )
        _alignment = Qt::AlignRight;

    else if (dir == QBoxLayout::TopToBottom )
        _alignment = Qt::AlignTop;
    else if (dir == QBoxLayout::BottomToTop )
        _alignment = Qt::AlignBottom;
}
