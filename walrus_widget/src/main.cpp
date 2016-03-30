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
#include <QSizePolicy>
#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QPainter>
//#include <QFrame>

#include "walrus_widget/glextensions.h"
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

//  CameraDisplay* cam = new CameraDisplay(widget);
//  cam->resize(800,600);
//  QObject::connect(qnode,SIGNAL(Update_Image( QImage*)),cam,SLOT(updateImage( QImage*)));
 //    QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

//  MapViz* scene3d_ = new MapViz(0,qnode);


//  QImage* test_image = new QImage("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/mire800.jpg");



//  QLabel*  background = new QLabel(widget);
//  background->setPixmap(test_image);
//  background->move(200,200);
  Overlay* gui = new Overlay(widget,qnode);
  gui->resize(1920,1080);
  gui->move(0,0);
//  QGraphicsScene scene;

//  QGraphicsProxyWidget *proxy = scene.addWidget(gui);
//  //scene.addWidget(gui);

//  QGraphicsView view(&scene,widget);
//  view.setStyleSheet("background: transparent");


//  view.show();

//  gui->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);
//  gui->setAutoFillBackground(false);
//  QPixmap pixmap = gui->grab();
//  gui->setMask(pixmap.createHeuristicMask());

//  widget->show();
//  gui->show();

  //gui->setWindowFlags (Qt::FramelessWindowHint);

//  QVBoxLayout* main_layout = new QVBoxLayout;
//  main_layout->setSpacing(0);
//  main_layout->addWidget( scene3d_ );
//  widget->setLayout( main_layout );

  //widget->makeOverlayCurrent();
//  Overlay* indicators_=new Overlay(widget);


//  widget->update();
//  scene3d_->update();

//  //graphey->setStyleSheet("background: transparent; border: none");
//  //widget->makeCurrent(scene3d_);,

  widget->show();

  // // view.setScene(&scene);

  return app.exec();

}
