#include "walrus_widget/indicator.h"



Indicator::Indicator(QWidget *parent=0, QString name = QString(), QString def_image_path = QString()):
    QLabel(parent),
    name_(name),
    images_(0)
{
    setMargin(0);
    if( def_image_path != QString() ) { //test that
        QPixmap* def_img = new QPixmap(def_image_path);
        images_.push_back(def_img);
        current_ = 0;
        switchImage(0);

    }
    else
        current_ = -1;
}

int Indicator::addImage(QString resource)
{

    QPixmap img = QPixmap(resource).scaled(size());

    images_.push_back(&img);
    return images_.size();
}


void Indicator::switchImage(int sel)
{
    setPixmap(*images_[sel]);
    current_ = sel;

}

QString Indicator::name() const
{
    return name_;
}


void Indicator::resizeEvent(QResizeEvent * event){
    for(std::vector<QPixmap*>::iterator pix = images_.begin(); pix != images_.end(); ++pix) {
        /* std::cout << *it; ... */
        **pix =(*pix)->scaledToWidth(width());
    }
    if (current_ != -1){
        switchImage(current_);
    }
}

