/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// BEGIN_TUTORIAL

// The main() for this "myviz" example is very simple, it just
// initializes ROS, creates a QApplication, creates the top-level
// widget (of type "MyViz"), shows it, and runs the Qt event loop.

#include <stdlib.h>     /* getenv */
#include <QApplication>
#include <ros/ros.h>
#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
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

  MainView* widget = new MainView();
//  widget->setWindowState(widget->windowState() ^ Qt::WindowFullScreen);
  widget->show();

  // // view.setScene(&scene);

  app.exec();

  delete widget;
}
