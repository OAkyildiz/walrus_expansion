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
#ifndef MAPVIZ_H
#define MAPVIZ_H

#include <QFrame>
#include <QWidget>
#include "qnode.h"


namespace rviz
{
class Display;
class RenderPanel;
class VisualizationManager;
class Config;
class YamlConfigReader;

}
namespace rtabmap_ros
{
class MapCloudDisplay;
}

class MapViz: public QWidget
{
  Q_OBJECT
public:
//  Mapviz( QWidget* parent = 0);
  MapViz(QWidget* parent = 0, qnode::QNode* qnode = 0 );


  //move to Q_Q_SLOTS?
  virtual ~MapViz();

  qnode::QNode *qnode() const;
  void setQNode(qnode::QNode *qnode);

  rviz::VisualizationManager *manager() const;
  void setManager(rviz::VisualizationManager *manager);

  rviz::RenderPanel *render_panel() const;
  void setRender_panel(rviz::RenderPanel *render_panel);

  rviz::Display *grid() const;
  void setGrid(rviz::Display *grid);

  rviz::Display *model() const;
  void setModel(rviz::Display *model);

  rtabmap_ros::MapCloudDisplay *map() const;
  void setMap(rtabmap_ros::MapCloudDisplay *map);

private Q_SLOTS:
  //void setThickness( int thickness_percent );
  //void setCellSize( int cell_size_percent );

private:
  qnode::QNode* qnode_;
  rviz::VisualizationManager* manager_;
  rviz::RenderPanel* render_panel_;

  rviz::Config* config_;
  rviz::YamlConfigReader* config_reader_;

  rviz::Display* grid_;
  rviz::Display* model_;

  rviz::Display* cloud_;
  rtabmap_ros::MapCloudDisplay* map_;

  //TO DO:: Encapsulate render panel elements rviz::RenderPanel*<-fancyname
};

#endif // MAPVIZ_H
