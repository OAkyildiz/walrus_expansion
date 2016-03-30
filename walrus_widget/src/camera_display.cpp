#include "walrus_widget/camera_display.h"

#include<QPainter>
//#include<QElapsedTimer>


CameraDisplay::CameraDisplay(QWidget *parent) :
    QWidget(parent),
    large_(false)
{
    image_ = 0;

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    title_ = new QLabel("title",this);
    title_->resize(120,15);
    title_->move(2,2);
    title_->setStyleSheet("QLabel { color : lightgray; }");


}

void CameraDisplay::updateImage(QImage *image) {

  image_ = image;
  repaint();

}

//void CameraDisplay::resizeEvent(QResizeEvent *event){
//    image_->resize(size());
//}

void CameraDisplay::paintEvent(QPaintEvent *event) {
  if (!image_) { return; }
  QPainter painter(this);

  painter.drawImage(rect(), *image_, image_->rect());

}

void CameraDisplay::updateVideoTitle(QString* title){
  title_->setText(*title);

}


bool CameraDisplay::large() const
{
    return large_;
}

void CameraDisplay::setLarge(bool large)
{
    large_ = large;
}

/*QSize CameraDisplay::sizes(int i)
//{
//    if(sizes_.length()<i){
//        return sizes_[i];
//    }
//    else
//        return QSize(0,0);
//}

//boolean CameraDisplay::setSize(int i, QSize size)
//{
//    if(sizes_.length()<i){
//        sizes_[i]=size;
//    }
//    else
//        return false;
//}

//void CameraDisplay::addSize(QSize size)
//{
//    sizes_.push_back(size);
//}
*/

