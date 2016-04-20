
#include "walrus_widget/battery_indicator.h"

BatteryIndicator::BatteryIndicator(QWidget *parent, QString name) :
    BarIndicator(parent,name, Indicators::Battery1, Qt::Horizontal)

{

}


void BatteryIndicator::repaintEvent(QPaintEvent * event)
{
    int side = qMin(width(), height());
//    QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
//                         side, QRegion::Ellipse);
//    setMask(maskedRegion);
    //label->setPixmap(*_icon_);

}

void BatteryIndicator::resizeEvent(QResizeEvent *event)
{
    *icon_ = icon_->scaled(size());

    label_->resize(width(),height());
    label_->setPixmap(*icon_);

    nobar_->resize(width(),height());
    nobar_->setPixmap(nobar_->pixmap()->scaled(size()));

    level_->resize(width()*0.85,height());
    level_->move(width()*0.05,0);

   //setMask(maskedRegion);
}


