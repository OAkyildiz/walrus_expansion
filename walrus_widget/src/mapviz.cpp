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


#include <QVBoxLayout>
#include <QSizePolicy>

#include "../include/walrus_widget/mapviz.h"

#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include "rviz/yaml_config_reader.h"
#include "rviz/config.h"

//#include "../include/rtabmap_ros/rviz/MapCloudDisplay.h"


// BEGIN_TUTORIAL
// Constructor for MyViz.  This does most of the work of the class.
MapViz::MapViz( QWidget* parent, qnode::QNode* qnode )
  : QWidget( parent )
{

  setQNode(qnode);

  setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
  // Construct and lay out render panel.
  render_panel_ = new rviz::RenderPanel();
  QVBoxLayout* main_layout = new QVBoxLayout;
  //main_layout->addLayout( controls_layout );
  main_layout->addWidget( render_panel_ );
  setLayout( main_layout );



//  rviz::Config* aconfig = new rviz::Config();
//  config_reader_->readFile(*aconfig,"remote_mapping.rviz");

//  config_ = aconfig;
//  manager_->load(*config_);

  manager_ = new rviz::VisualizationManager( render_panel_ );
  render_panel_->initialize( manager_->getSceneManager(), manager_ );
  manager_->initialize();
  manager_->startUpdate();

  // Create a Grid display.   //TODO: make walrus_model class

  grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
  model_ = manager_->createDisplay( "rviz/RobotModel", "robot_model", true );

  cloud_= manager_->createDisplay("rviz/PointCloud2", "voxel_cloud", true);
  //map_ = new rtabmap_ros::MapCloudDisplay();
  //manager_->addDisplay(map_,true);
  manager_->setFixedFrame("walrus/base_footprint");
  
  grid_->setFixedFrame("walrus/base_footprint");

  ROS_ASSERT( model_ != NULL );
  
  // Configure the GridDisplay the way we like it.
  grid_->subProp( "Line Style" )->setValue( "Billboards" );
  grid_->subProp( "Color" )->setValue( QColor(Qt::yellow) );

  cloud_->subProp( "Topic" )->setValue("/voxel_cloud");
  cloud_->subProp( "Queue Size" )->setValue("10");
  cloud_->subProp( "Size (m)" )->setValue("0.01");

  //map_->subProp( "Topic" )->setValue("/rtabmap/mapData");
  //map_->subProp( "Queue Size" )->setValue("10");

  manager_->startUpdate();


  // Initialize the slider values.
  //thickness_slider->setValue( 25 );
 // cell_size_slider->setValue( 10 );
}
MapViz::~MapViz()
{
  delete manager_;
}
//MapViz::MapViz( QWidget* parent = 0, qnode::QNode* qnode ) :
//    MapViz::MapViz( parent )
//{
//   setQNode(qnode);
//}
qnode::QNode *MapViz::qnode() const
{
    return qnode_;
}

void MapViz::setQNode(qnode::QNode *qnode)
{
    qnode_ = qnode;
}
rviz::VisualizationManager *MapViz::manager() const
{
    return manager_;
}

void MapViz::setManager(rviz::VisualizationManager *manager)
{
    manager_ = manager;
}
rviz::RenderPanel *MapViz::render_panel() const
{
    return render_panel_;
}

void MapViz::setRender_panel(rviz::RenderPanel *render_panel)
{
    render_panel_ = render_panel;
}
rviz::Display *MapViz::grid() const
{
    return grid_;
}

void MapViz::setGrid(rviz::Display *grid)
{
    grid_ = grid;
}
rviz::Display *MapViz::model() const
{
    return model_;
}

void MapViz::setModel(rviz::Display *model)
{
    model_ = model;
}
//rtabmap_ros::MapCloudDisplay *MapViz::map() const
//{
//    return map_;
//}

//void MapViz::setMap(rtabmap_ros::MapCloudDisplay *map)
//{
//    map_ = map;
//}









// This function is a Qt slot connected to a QSlider's valueChanged()
// signal.  It sets the line thickness of the grid by changing the
// grid's "Line Width" property.
//void MyViz::setThickness( int thickness_percent )
//{
//  if( grid_ != NULL )
//  {
//    grid_->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
//  }
//}

//// This function is a Qt slot connected to a QSlider's valueChanged()
//// signal.  It sets the cell size of the grid by changing the grid's
//// "Cell Size" Property.
//void MyViz::setCellSize( int cell_size_percent )
//{
//  if( grid_ != NULL )
//  {
//    grid_->subProp( "Cell Size" )->setValue( cell_size_percent / 10.0f );
//  }
//}
