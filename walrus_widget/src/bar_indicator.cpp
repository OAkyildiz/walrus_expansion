#include "walrus_widget/bar_indicator.h"
#include "walrus_widget/styles.h"

BarIndicator::BarIndicator(QWidget *parent, QString icon_path, Qt::Orientation orientation) :
    QWidget(parent)
{
    _orientation = orientation;

    icon_ = new QPixmap(icon_path);
    level_ = new QProgressBar(this);
    label_ = new QLabel(this);

    nobar_ = new QLabel(label_);
    nobar_->setPixmap(QPixmap(Indicators::NoBar));

    //Progress bar
    level_->setMinimum(0);
    level_->setMaximum(100);
    level_->setTextVisible(true);
    level_->setOrientation(orientation);

    //level_->setValue();

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

void BarIndicator::valueUpdated(double value)
{
    double old_val = level_->value();
    if ( old_val != value )
        if (value == -1){ //define ERROR_VALUE
            nobar_->show();
            level_->setValue(0.0);
        }
        else
            level_->setValue(value);
            nobar_->hide(); // assuming hide() already cheacks for visible

}

Qt::Orientation BarIndicator::orientation() const
{
    return _orientation;
}

void BarIndicator::setOrientation(Qt::Orientation orientation)
{
    _orientation = orientation;
}
