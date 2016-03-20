#include "walrus_widget/battery_panel.h"

BatteryPanel::BatteryPanel(QWidget* parent) : QFrame(parent)
{
    layout_ = new QHBoxLayout() ;
    layout_->setSpacing(0);

    battery1_ = new BatteryIndicator();
    battery2_ = new BatteryIndicator();
    battery3_ = new BatteryIndicator();
    battery4_ = new BatteryIndicator();

    layout_->addWidget(battery1_);
    layout_->addWidget(battery2_);
    layout_->addWidget(battery3_);
    layout_->addWidget(battery4_);

    setLayout(layout_);

}

BatteryPanel::~BatteryPanel(){
    delete battery1_;
    delete battery2_;
    delete battery3_;
    delete battery4_;

}

void BatteryPanel::resizeEvent(QResizeEvent *event){


    battery1_->resize(width()*0.75/4, height()*0.75);
    battery2_->resize(width()*0.75/4, height()*0.75);
    battery3_->resize(width()*0.75/4, height()*0.75);
    battery4_->resize(width()*0.75/4, height()*0.75);
}
