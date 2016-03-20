#ifndef CAMERA_DISPLAY_H
#define CAMERA_DISPLAY_H

#include <QWidget>
#include <QImage>
#include <QLabel>


class CameraDisplay : public QWidget {
  Q_OBJECT
public:
  CameraDisplay(QWidget* parent = 0);

public  Q_SLOTS:
  void updateImage(QImage* image);

private:

protected:

  QLabel* label_;
  QImage* image_;

  //void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent* event);

};


#endif // CAMERA_DISPLAY_H
