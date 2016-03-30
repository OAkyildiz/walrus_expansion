//#include <QVBoxLayout>


#include "walrus_widget/radar.h"



Radar::Radar(QWidget *parent, qnode::QNode* qnode)
    : QFrame( parent )
 {
//TODO: Camera , constant top! rviz::FixedOrientationOrthoViewController and manager

    qnode_ = qnode;

    //setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    // Construct and lay out render panel.

    bound_ = new QLabel(this);
    bound_->setPixmap(QPixmap("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/circle_bound.png"));
    bound_->move(0,0);

    render_panel_ = new rviz::RenderPanel(bound_);
    render_panel_->move(0,0);

    //QVBoxLayout* main_layout = new QVBoxLayout;
    //main_layout->addLayout( controls_layout );
    //main_layout->addWidget( render_panel_ );
    //main_layout->setSpacing(0);
    //setLayout( main_layout );


  //  rviz::Config* aconfig = new rviz::Config();
  //  config_reader_->readFile(*aconfig,"remote_mapping.rviz");

  //  config_ = aconfig;
  //  manager_->load(*config_);

    manager_ = new rviz::VisualizationManager( render_panel_ );
    render_panel_->initialize( manager_->getSceneManager(), manager_ );
    manager_->initialize();
    manager_->unlockRender();
    manager_->startUpdate();

    manager_->setFixedFrame("walrus/base_footprint");


    grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
    grid_->subProp( "Line Style" )->setValue( "Billboards" );
    grid_->subProp( "Color" )->setValue( QColor(Qt::white) );

    obstacles_ = manager_->createDisplay( "rviz/GridCells", "obstacles", true );

    obstacles_->subProp( "Topic" )->setValue("/obstacles");
    //obstacles_->subProp( "Queue Size" )->setValue("10");


    robot_marker_ = manager_->createDisplay( "rviz/Marker", "robot_marker", true );
    robot_marker_->setFixedFrame("walrus/base_footprint");

    robot_marker_->subProp( "Marker Topic" )->setValue("/robot_marker");
    //robot_marker_->subProp( "Queue Size" )->setValue("10");

}

Radar::~Radar(){
    delete manager_;
}

void Radar::resizeEvent(QResizeEvent * event)
{
    int side = qMin(width(), height());
    QRegion maskedRegion(width() / 2 - side*0.95 / 2, height() / 2 - side*0.95 / 2, side*0.95,
                         side*0.95, QRegion::Ellipse);

    render_panel_->setMask(maskedRegion);
    render_panel_->resize(size());

    QRegion bound_maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
                         side, QRegion::Ellipse);

    bound_->resize(size());
    bound_->setPixmap(bound_->pixmap()->scaled(size()));
}
