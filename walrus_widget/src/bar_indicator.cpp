#include "walrus_widget/bar_indicator.h"

BarIndicator::BarIndicator(QString name,
                           QString icon_path,
                           Qt::Orientation orientation):
    BaseIndicator(name,icon_path),
    _orientation(orientation)
{
    level_ = new QProgressBar(this);
    //Progress bar
    level_->setMinimum(0);
    level_->setMaximum(100);
    level_->setTextVisible(true);
    level_->setOrientation(_orientation);

    level_->setValue(0);
}
void BarIndicator::resizeEvent(QResizeEvent *event){

    int w = width()*.96;
    int h = height()*.96;

    if (orientation() == Qt::Vertical){

        label_->resize(w,w);
        label_->move(w,h-w);
        *icon_ = icon_->scaled(label_->size());
        label_->setPixmap(*icon_);

        nobar_->resize(w,w);
        nobar_->move(w,h-w);
        nobar_->setPixmap(nobar_->pixmap()->scaled(size()));

        level_->resize(w*.90,h-w*1.05);
        level_->move(w*0.05,0);
    }

    else if (orientation() == Qt::Horizontal) {

        label_->resize(h,h);
        *icon_ = icon_->scaled(label_->size());
        label_->setPixmap(*icon_);

        nobar_->resize(h,h);
        nobar_->setPixmap(nobar_->pixmap()->scaled(size()));

        level_->resize(w-h*1.05,h*0.90);
        level_->move(h*1.05,h*.05);
    }

}



bool BarIndicator::update(int value)
{
    BaseIndicator::update(value);
    level_->setValue(value);
    // add coloring here
    // add attributes for color direction and limits
}

Qt::Orientation BarIndicator::orientation() const
{
    return _orientation;
}

