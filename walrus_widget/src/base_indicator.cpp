#include "walrus_widget/base_indicator.h"


BaseIndicator::BaseIndicator(QString name, QString icon_path):
    QWidget(0),
    name_(name)
{
    label_= new QLabel(this);
    nobar_= new QLabel(label_);
    icon_= new QPixmap( icon_path );
    nobar_icon_ = new QPixmap( Indicators::NoBar );
    valueUpdated(0);
}

void BaseIndicator::valueUpdated(int value)
{
    double old_val = this->value();
    if ( old_val != value )
        if (value == BaseIndicator::ERROR_VALUE){ //define ERROR_VALUE
            nobar_->show();
        }
        else
            nobar_->hide(); /* assuming hide() already cheacks for visible,
                            but the top if should handle that anyways */
        update(value);
}

QString BaseIndicator::name() const
{
    return name_;
}

int BaseIndicator::value() const
{
    return _value;
}

void BaseIndicator::setValue(int value)
{
    _value = value;
}

QPixmap *BaseIndicator::icon() const
{
    return icon_;
}

void BaseIndicator::setIcon(QPixmap *icon)
{
    icon_ = icon;
}

void BaseIndicator::resizeEvent(QResizeEvent *event)
{
    label_->resize(size());
    *icon_= icon()->scaled( size(),Qt::KeepAspectRatio );
    label_->setPixmap(*icon_);

    nobar_->resize(size());
    nobar_->setPixmap(nobar_icon_->scaled( size(),Qt::KeepAspectRatio) );
}
