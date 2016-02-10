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

#include "../include/walrus_widget/glextensions.h"
#include "../include/walrus_widget/mainview.h"
#include "../include/walrus_widget/qnode.hpp"

/* GraphicsView checks


class GraphicsView : public QGraphicsView
{
public:
    GraphicsView()
    {
        setWindowTitle(tr("Walrus DriveStation 0.0.5"));
        setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        //setRenderHints(QPainter::SmoothPixmapTransform);
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

inline bool matchString(const char *extensionString, const char *subString)
{
    int subStringLength = strlen(subString);
    return (strncmp(extensionString, subString, subStringLength) == 0)
        && ((extensionString[subStringLength] == ' ') || (extensionString[subStringLength] == '\0'));
}

bool necessaryExtensionsSupported()
{
    const char *extensionString = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
    const char *p = extensionString;

    const int GL_EXT_FBO = 1;
    const int GL_ARB_VS = 2;
    const int GL_ARB_FS = 4;
    const int GL_ARB_SO = 8;
    int extensions = 0;

    while (*p) {
        if (matchString(p, "GL_EXT_framebuffer_object"))
            extensions |= GL_EXT_FBO;
        else if (matchString(p, "GL_ARB_vertex_shader"))
            extensions |= GL_ARB_VS;
        else if (matchString(p, "GL_ARB_fragment_shader"))
            extensions |= GL_ARB_FS;
        else if (matchString(p, "GL_ARB_shader_objects"))
            extensions |= GL_ARB_SO;
        while ((*p != ' ') && (*p != '\0'))
            ++p;
        if (*p == ' ')
            ++p;
    }
    return (extensions == 15);
}

*/


int main(int argc, char **argv)
{
//  if( !ros::isInitialized() )
//  {
//    ros::init( argc, argv, "myviz", ros::init_options::AnonymousName );
//  }

  /* Init QApp*/    
  QApplication app( argc, argv );

  /*
  if ((QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_5) == 0) {
      QMessageBox::critical(0, "OpenGL features missing",
          "OpenGL version 1.5 or higher is required to run this demo.\n"
          "The program will now exit.");
      return -1;
  }

  int maxTextureSize = 1024;
  QGLWidget *widget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
  widget->makeCurrent();

  if (!necessaryExtensionsSupported()) {
      QMessageBox::critical(0, "OpenGL features missing",
          "The OpenGL extensions required to run this demo are missing.\n"
          "The program will now exit.");
      delete widget;
      return -2;
  }
  */

  // Check if all the necessary functions are resolved.

  /*
   * if (!getGLExtensionFunctions().resolve(widget->context())) {
      QMessageBox::critical(0, "OpenGL features missing",
          "Failed to resolve OpenGL functions required to run this demo.\n"
          "The program will now exit.");
      delete widget;
      return -3;
    }
   */

 /* welcome-warning dialog message(optional)
    // TODO: Make conditional for final release
  QMessageBox::information(0, "For your information",
      "This demo can be GPU and CPU intensive and may\n"
      "work poorly or not at all on your system.");
 */

 //GraphicsView view;

  // The current context must be set before calling Scene's constructor
  //void Qwidget:raise();

  /* Init RosNode*/
  qnode::QNode* qnode = new qnode::QNode(argc,argv);
  qnode->init(getenv("ROS_MASTER_URI"),getenv("ROS_HOSTNAME"));


  QWidget* widget = new QWidget();
  widget->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);

  MapViz* scene3d_ = new MapViz(0,qnode);

  QVBoxLayout* main_layout = new QVBoxLayout;
  main_layout->addWidget( scene3d_ );
  widget->setLayout( main_layout );
  Overlay* indicators_=new Overlay();
  //indicators_->setAttribute(Qt::WA_TranslucentBackground);
  //scene3d_->grid_;
  //widget->makeCurrent(scene3d_);
  widget->show();


  // // view.setScene(&scene);

  app.exec();

  delete widget;
}
