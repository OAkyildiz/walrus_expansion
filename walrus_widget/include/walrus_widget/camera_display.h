#ifndef CAMERA_DISPLAY_H
#define CAMERA_DISPLAY_H

#include <QWidget>
#include <QImage>
#include <QLabel>

#include <vector>

class CameraDisplay : public QWidget {
  Q_OBJECT
public:
  CameraDisplay(QWidget* parent = 0);

  bool large() const;
  void setLarge(bool large);

//  QSize sizes(int i);
//  void setSize(int i, QSize size);
//  void addSize(QSize size);


public  Q_SLOTS:
  void updateImage(QImage* image);
  void updateVideoTitle(QString* title);
private:

protected:

  QLabel* title_;
  QImage* image_;
  bool large_;
  //std::vector<QSize> sizes_;

  //void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent* event);

};


#endif // CAMERA_DISPLAY_H
