/*
 *
 *
 *
 * /
#include <ros/ros.h>
#include <stdlib.h>     /* getenv */

#include <QtWidgets>
#include <QOpenGLWidget>
//#include <QtOpenGL>
#include <QVBoxLayout>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QPainter>
//#include <QFrame>

#include "../include/walrus_widget/glextensions.h"
#include "../include/walrus_widget/mainview.h"
#include "../include/walrus_widget/qnode.hpp"
#include "../include/walrus_widget/mapviz.h"



int main(int argc, char **argv)
{

  /* Init QApp*/    
  QApplication app( argc, argv );
  /* Init RosNode*/
  qnode::QNode* qnode = new qnode::QNode(argc,argv);
  qnode->init(getenv("ROS_MASTER_URI"),getenv("ROS_HOSTNAME"));
  /*Main Widget*/
  QOpenGLWidget* widget = new QOpenGLWidget();
  widget->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);

  //widget->makeCurrent();
  MapViz* scene3d_ = new MapViz(widget,qnode);

  QVBoxLayout* main_layout = new QVBoxLayout;
  main_layout->setSpacing(0);
  main_layout->addWidget( scene3d_ );
  widget->setLayout( main_layout );

  //widget->makeOverlayCurrent();
 // Overlay* indicators_=new Overlay();

//  indicators_->raise();
//  QPalette p = indicators_->palette();
//  p.setBrush(QPalette::Window, Qt::transparent);
//  indicators_->setPalette(p);
//  widget->makeCurrent();
//  QVBoxLayout* over_layout = new QVBoxLayout;
//  over_layout->setSpacing(0);
//  over_layout->addWidget( indicators_ );
//  //indicators_->setLayout( over_layout );
//  indicators_->setAttribute(Qt::WA_NoSystemBackground);

//  QWidget* widjey = new QWidget(widget);

//  widjey->raise();
//  widjey->resize(400,400);
//  //widjey->setWindowOpacity(0.25);
//  widjey->setAttribute(Qt::WA_NoSystemBackground);
//  widjey->setAttribute(Qt::WA_TranslucentBackground);

//  QFrame* framey = new QFrame();
//  QPalette p = framey->palette();

//  framey->setPalette( p );
//  framey->update();
  widget->update();

  //graphey->setStyleSheet("background: transparent; border: none");
  //widget->makeCurrent(scene3d_);,

  widget->show();

  // // view.setScene(&scene);

  return app.exec();

}
