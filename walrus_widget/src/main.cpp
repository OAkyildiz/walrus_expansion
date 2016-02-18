/*
 *
 *
 *
 * /
#include <ros/ros.h>
#include <stdlib.h>     /* getenv */

#include <QApplication>
#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QPainter>
//#include <QFrame>

#include "../include/walrus_widget/glextensions.h"
#include "../include/walrus_widget/mainview.h"
#include "../include/walrus_widget/qnode.hpp"



int main(int argc, char **argv)
{
//  if( !ros::isInitialized() )
//  {
//    ros::init( argc, argv, "myviz", ros::init_options::AnonymousName );
//  }

  /* Init QApp*/    
  QApplication app( argc, argv );




  /* Init RosNode*/
  qnode::QNode* qnode = new qnode::QNode(argc,argv);
  qnode->init(getenv("ROS_MASTER_URI"),getenv("ROS_HOSTNAME"));


  QWidget* widget = new QWidget();
  widget->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);


  //widget->makeCurrent();
  MapViz* scene3d_ = new MapViz(widget,qnode);

  QVBoxLayout* main_layout = new QVBoxLayout;
  main_layout->setSpacing(0);
  main_layout->addWidget( scene3d_ );
  widget->setLayout( main_layout );

  //widget->makeOverlayCurrent();
  Overlay* indicators_=new Overlay();

  //widget->makeCurrent();

//  indicators_->raise();
//  QPalette p = indicators_->palette();
//  p.setBrush(QPalette::Window, Qt::transparent);
//  indicators_->setPalette(p);
//  widget->makeCurrent();
  ////  p.fillRect(rect(), QColor(80, 80, 255, 128));
//  QVBoxLayout* over_layout = new QVBoxLayout;
//  over_layout->setSpacing(0);
//  over_layout->addWidget( indicators_ );
//  indicators_->setLayout( over_layout );
//    indicators_->setAttribute(Qt::WA_NoSystemBackground);

//  main_layout->setMargin(0);
//  main_layout->setContentsMargins(  0,0,0,0);

//  widget->setLayout( main_layout );



//  QWidget* widjey = new QWidget(widget);

//  widjey->raise();
//  widjey->resize(400,400);
//  //widjey->setWindowOpacity(0.25);
//  widjey->setAttribute(Qt::WA_NoSystemBackground);
//  widjey->setAttribute(Qt::WA_TranslucentBackground);


//  QFrame* framey = new QFrame();

//  framey->raise();
//  framey->resize(200,400);
//  framey->setWindowOpacity(0.25);
//  //framey->setAttribute(Qt::WA_NoSystemBackground);
//  //framey->setAttribute(Qt::WA_TranslucentBackground);

//  QPalette p = framey->palette();
////  p.fillRect(rect(), QColor(80, 80, 255, 128));

//  framey->setPalette( p );
//  framey->update();
  widget->update();

  //graphey->setStyleSheet("background: transparent; border: none");
  //indicators_->setAttribute(Qt::WA_TranslucentBackground);

  //scene3d_->grid_;
  //widget->makeCurrent(scene3d_);,
  //widjey->makeCurrent(); // The current context must be set before calling Scene's constructor
//  QGraphicsScene* scene= new QGraphicsScene();
//  QGraphicsView* view;
//  view-> setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//  view->setViewport(widjey);
//  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//  view->setScene(scene);
//  view->showFullScreen();
 widget->show();

  // // view.setScene(&scene);

  app.exec();

  delete widget;
}
