/*
 *
 *
 *
 * /
#include <ros/ros.h>
#include <stdlib.h>     /* getenv */

#include <QWidget>
#include <QApplication>
//#include <QOpenGLWidget>
//#include <QtOpenGL>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QPainter>
//#include <QFrame>

//#include "walrus_widget/glextensions.h"
#include "walrus_widget/mainview.h"
#include "walrus_widget/qnode.h"
#include "walrus_widget/overlay.h"
#include "walrus_widget/styles.h"


//TODO: Put widget attributes to static in description

int main(int argc, char **argv)
{

  /* Init QApp*/    
  QApplication app( argc, argv );
  app.setStyleSheet(Styles::style1);

  /* Init RosNode*/
  qnode::QNode* qnode = new qnode::QNode(argc,argv,false);
  qnode->init(getenv("ROS_MASTER_URI"),getenv("ROS_HOSTNAME"));

  /*Main Widget*/
  QWidget* widget = new QWidget();
  widget->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);

//  MapViz* scene3d_ = new MapViz(0,qnode);

//  QImage* test_image = new QImage("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/mire800.jpg");

  Overlay* gui = new Overlay(widget,qnode);
  gui->resize(1920,1080);
  gui->move(0,0);

  widget->show();

  // // view.setScene(&scene);

  return app.exec();
  delete widget;


}
