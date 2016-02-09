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


#include "../include/walrus_widget/mapviz.h"


// BEGIN_TUTORIAL
// Constructor for MyViz.  This does most of the work of the class.
MapViz::MapViz( QWidget* parent )
  : QWidget( parent )
{

  // Construct and lay out render panel.
  render_panel_ = new rviz::RenderPanel();
  QVBoxLayout* main_layout = new QVBoxLayout;
  //main_layout->addLayout( controls_layout );
  main_layout->addWidget( render_panel_ );
  setLayout( main_layout );


  manager_ = new rviz::VisualizationManager( render_panel_ );
  render_panel_->initialize( manager_->getSceneManager(), manager_ );
  manager_->initialize();
  manager_->startUpdate();

  // Create a Grid display.
  grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
  //TODO: make walrus_model class
  model_ = manager_->createDisplay( "rviz/RobotModel", "robot_model", true );

  map_ = new rtabmap_ros::MapGraphDisplay();
  manager_->addDisplay(map_,true);
  ROS_ASSERT( model_ != NULL );
  // Configure the GridDisplay the way we like it.
  grid_->subProp( "Line Style" )->setValue( "Billboards" );
  grid_->subProp( "Color" )->setValue( Qt::yellow );
  grid_->subProp( "Frame")->setValue("walrus/odom");

  model_->subProp( "Tf Prefix")->setValue("walrus/");


  // Initialize the slider values.
  //thickness_slider->setValue( 25 );
 // cell_size_slider->setValue( 10 );
}

// Destructor.
MapViz::~MapViz()
{
  delete manager_;
}

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
