//
#include <QGridLayout>

#include "walrus_widget/overlay.h"
#include "walrus_widget/mapviz.h"

#include "math.h"
#include <string>


Overlay::Overlay(QWidget *parent, qnode::QNode* qnode)
    :QFrame(parent)
    //:MapViz(parent,qnode)

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

    qnode_->cameraTopicChanged(4);

}


void Overlay::initWidgets(){


    /* Radar */
    radar_ = new Radar(this, qnode_);

    /* Cameras */
    cameras_= new CameraDisplay(this);
    //cameras_->updateImage(new QImage(gray));

    /* Console */
    console_ = new Console(this,qnode_);

    /* Batteries */
    batteries_= new IndicatorsPanel( this,"batteries",QBoxLayout::LeftToRight);

    BatteryIndicator* battery1 = new BatteryIndicator("battery1");
    BatteryIndicator* battery2 = new BatteryIndicator("battery2");
    BatteryIndicator* battery3 = new BatteryIndicator("battery3");
    BatteryIndicator* battery4 = new BatteryIndicator("battery4");

    batteries_->addIndicator( battery1 );
    batteries_->addIndicator( battery2 );
    batteries_->addIndicator( battery3 );
    batteries_->addIndicator( battery4 );

    /* Warnings */
    warnings_panel_ = new WarningsPanel(this);
    //warnings_panel_->addWarning("first",wat);
    //warnings_panel_->showWarning("first");


    //warnings_panel_->addWarning("second",heat);
    //warnings_panel_->showWarning("second");

//    warnings_panel_->hideWarning("first");
//    warnings_panel_->showWarning("first");

//    warnings_panel_->hideWarning("second");
//    warnings_panel_->showWarning("second");
    /* Indicators */

    IterIndicator* wifi = new IterIndicator("wifi",Indicators::Wifi::Poor);
    wifi->addImage(Indicators::Wifi::Weak);
    wifi->addImage(Indicators::Wifi::Fair);
    wifi->addImage(Indicators::Wifi::Strong);
    wifi->setErrorIndex(3);

    BaseIndicator* ctrl = new BaseIndicator("ctrl",Indicators::Controller);

    comms_= new IndicatorsPanel(this,"some",QBoxLayout::TopToBottom);
    comms_->addIndicator(wifi);
    comms_->addIndicator(ctrl);

    /* Odometry*/
    tachometer_ = new OdometryDisplay(this);


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
