#include <QHBoxLayout>

#include "walrus_widget/battery_indicator.h"


BatteryIndicator::BatteryIndicator(QWidget *parent) :
    QWidget(parent)

{
    //Progress bar
    QString bat_img_path = QString("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/battery/h-battery1.png");
    battery_icon_ = new QPixmap(bat_img_path);


    level_ = new QProgressBar(this);
    icon_ = new QLabel(this);


    //level_->resize(icon_->size());
    level_->setMinimum(0);
    level_->setMaximum(100);
    level_->setTextVisible(true);
    level_->setValue(37);

    //Batterry image





    //ser-tlevel
}

BatteryIndicator::~BatteryIndicator(){
    delete level_;
}

void BatteryIndicator::repaintEvent(QPaintEvent * event)
{
    int side = qMin(width(), height());
//    QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
//                         side, QRegion::Ellipse);
//    setMask(maskedRegion);
    //icon_->setPixmap(*battery_icon_);

}

void BatteryIndicator::resizeEvent(QResizeEvent *event)
{
    *battery_icon_ = battery_icon_->scaled(size());
    icon_->resize(width(),height());
    level_->resize(width()*0.85,height());
    level_->move(width()*0.05,0);

    icon_->setPixmap(*battery_icon_);

   //setMask(maskedRegion);
}
