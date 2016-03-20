#include "walrus_widget/camera_display.h"

#include<QPainter>
//#include<QElapsedTimer>


CameraDisplay::CameraDisplay(QWidget *parent) : QWidget(parent) {
  image_ = 0;

  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//  label_ = new QLabel("hi");
//  label_->resize(40,100);

//  label_->show();
  //label_->move(20,605);
  //image_ = new QImage(size(), QImage::Format_RGB32);
  //setAutoFillBackground(false);
  //setAttribute(Qt::WA_NoSystemBackground, true);
  //setAttribute(Qt::WA_PaintOnScreen, true);
}

void CameraDisplay::updateImage(QImage *image) {

//  QElapsedTimer tim = QElapsedTimer();
//  tim.start();

  image_ = image;
  //image_->setPixmap(QPixmap::fromImage(*image));
  repaint();

//  int millis = tim.elapsed();
//  label_->setText("a: " +QString::number(millis));


}

//void CameraDisplay::resizeEvent(QResizeEvent *event){
////    image_->resize(size());
//}

void CameraDisplay::paintEvent(QPaintEvent *event) {
  if (!image_) { return; }
  QPainter painter(this);

  //QElapsedTimer tim = QElapsedTimer();

  //tim.start();
  painter.drawImage(rect(), *image_, image_->rect());
  //label_->setText("a: " +QString::number(tim.elapsed()));

}


