//
#include <QGridLayout>

#include "walrus_widget/overlay.h"
#include "walrus_widget/mapviz.h"

#include "math.h"
#include <string>


Overlay::Overlay(QWidget *parent, qnode::QNode* qnode)
    //:QFrame(parent)
    :MapViz(parent,qnode)

{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    qnode_= qnode;
    initWidgets();

    //setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::WindowStaysOnTopHint);
   // setAttribute(Qt::WA_PaintOnScreen);

    // Connect signals to slots
    connect(qnode_,SIGNAL(Update_Image(QImage*)),cameras_,SLOT(updateImage(QImage*)));
    connect(qnode_,SIGNAL(Update_Video_Title(QString*)),cameras_,SLOT(updateVideoTitle(QString*)));
    connect(qnode_,SIGNAL(Update_Speed(double, double, double)),tachometer_,SLOT(SpeedUpdated(double, double, double)));
    connect(qnode_,SIGNAL(Update_Pose(double, double, double, double, double, double, double)),tachometer_,SLOT(PoseUpdated(double, double, double, double, double, double, double)));

    qnode_->cameraTopicChanged(1);

}


void Overlay::initWidgets(){
    QString gray = QString("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/placeholder64.gif");
    QString icon = QString("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/icon.png");



    /* Radar */
    radar_ = new Radar(this, qnode_);

    /* Cameras */
    cameras_= new CameraDisplay(this);
    //cameras_->updateImage(new QImage(gray));

    /* Console */
    console_ = new Console(this,qnode_);

    /* Batteries */
    batteries_= new BatteryPanel(this);


    /* Warnings */
    warnings_panel_ = new WarningsPanel(this);
    warnings_panel_->addWarning("first",icon);
    warnings_panel_->showWarning("first");


    warnings_panel_->addWarning("second",gray);
    warnings_panel_->showWarning("second");

//    warnings_panel_->hideWarning("first");
//    warnings_panel_->showWarning("first");

//    warnings_panel_->hideWarning("second");
//    warnings_panel_->showWarning("second");
    /* Indicators */

    Indicator* wifi = new Indicator(0,"wifi",gray);

    comms_= new IndicatorsPanel(this,"V");
    comms_->addIndicator(wifi);
    comms_->addIndicator("controller", icon);

    /* Odometry*/
    tachometer_ = new OdometryDisplay(this);
/* With Layout:
    int grid_rows = 144;
    int grid_cols = floor(grid_rows*16/9);

    QGridLayout* gui_layout_ = new QGridLayout();

    gui_layout_->setSpacing(0);

    //change to normal placement
    gui_layout_->addWidget(radar_,0,0,3,3);
    gui_layout_->addWidget(cameras_,0,grid_cols-2,3,3);
    gui_layout_->addWidget(console_,grid_rows-2,0,2,3);
    gui_layout_->addWidget(batteries_,grid_rows,0,1,4);
    gui_layout_->addWidget(warnam
Ros shutdown, proceeding to close the gui.
ings_panel_,grid_rows-1,3,1,3);
    gui_layout_->addWidget(comms_,grid_rows-1,grid_cols-2,2,1);
    gui_layout_->addWidget(tachometer_,grid_rows,grid_cols-1,1,2);


    setLayout(gui_layout_);

*/

}

void Overlay::resizeEvent(QResizeEvent *event){
    int w = width();
    int h = height();
    int w_unit = w/32;
    int h_unit = h/18;
    int spacing = 10;

    radar_->move(spacing, spacing); //top left corner
    radar_->resize(w_unit*4, h_unit*4);

//    cameras_->setSize(QSize(w_unit*8, h_unit*4.5));
//    cameras_->setSize(QSize(w_unit*16, h_unit*9));
    cameras_->resize(w_unit*8, h_unit*6);   // for 4:3 ratio
    cameras_->move(w-spacing-cameras_->width(), spacing); //top right corner


    batteries_->resize(w_unit*6, h_unit*1); //bottom left corner
    batteries_->move(spacing, h - batteries_->height()- spacing);

    console_->resize(w_unit*8, h_unit*4);   //left side, above batteries
    console_->move(spacing, batteries_-> y() - console_->height() - spacing);

    warnings_panel_->resize(w_unit*6, h_unit*1.5); //next to console, above batteries
    warnings_panel_->move(console_->x() + console_->width() + spacing, batteries_->y() -warnings_panel_->height() - spacing);

    tachometer_->resize(w_unit*4, h_unit*2); //bottom right corner
    tachometer_->move(w - spacing-tachometer_->width(), h - spacing -  tachometer_->height());

    comms_->resize(w_unit*1.5, h_unit*7); //bottom, next to speedometer
    comms_->move(tachometer_->x() - comms_->width() - spacing, h - comms_->height() - spacing);
}


void Overlay::toggleVideoSize(){
   if (cameras_->large()){
       cameras_->resize(w_unit*8, h_unit*6);
       cameras_->move(w-spacing-cameras_->width(), spacing);
       cameras_->setLarge(false);
   }
   else{
       cameras_->setLarge(true);
       cameras_->resize(w_unit*16, h_unit*12);   // for 4:3 ratio
       cameras_->move(w-spacing-cameras_->width(), spacing);

   }
}
