#include "walrus_widget/iter_indicator.h"



IterIndicator::IterIndicator(QString name, QString icon_path):
    BaseIndicator(name,icon_path),
    _size(0),
    _error_index(0),
    images_(_size)
{
   if (icon_path != Indicators::Placeholder)
       addImage(icon_path);
       valueUpdated(0);
}

void IterIndicator::addImage(QString resource)
{

    QPixmap* img = new QPixmap(resource);

    images_.push_back(img);
    _size++;
}

void IterIndicator::addImage(QPixmap* pixmap)
{

    images_.push_back(pixmap);
    _size++;


}

void IterIndicator::setErrorIndex(int err){
    if (err<_size)
        _error_index = err;

}

bool IterIndicator::update(int value)
{
    if (value == BaseIndicator::ERROR_VALUE)
        _value = _error_index;
    _value = value;
    icon_ = images_[_value];

}

void IterIndicator::resizeEvent(QResizeEvent * event){

     label_->resize( size());
     icon_ = images_[_value];
    *icon_ = icon_->scaled(size(), Qt::KeepAspectRatio);
     label_->setPixmap(*icon_);

    for(int i = 0; i =! _size; i++) {
        /* std::cout << *it; ... */
        *images_[i] = images_[i]->scaled(size(), Qt::KeepAspectRatio);
        }
}



