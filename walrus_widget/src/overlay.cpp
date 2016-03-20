//
#include <QGridLayout>

#include "walrus_widget/overlay.h"
#include "math.h"



Overlay::Overlay(QWidget *parent, qnode::QNode* qnode)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    loadWidgets(qnode);

    //setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::WindowStaysOnTopHint);
   // setAttribute(Qt::WA_PaintOnScreen);

    // Connect signals to slots
    QObject::connect(qnode,SIGNAL(Update_Image(QImage*)),cameras_,SLOT(updateImage(QImage*)));


}




void Overlay::loadWidgets(qnode::QNode *qnode){
    QString gray = QString("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/placeholder64.gif");
    QString icon = QString("/home/oakyildiz/mqp_2016_ws/src/walrus_xp/walrus_widget/resources/images/icon.png");



    /* Radar */
    radar_ = new Radar(this, qnode);

    /* Cameras */
    cameras_= new CameraDisplay(this);
    //cameras_->updateImage(qnode->PixmapModel());

    /* Console */
    console_ = new Console(this,qnode);

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
    speedometer_ = new QLCDNumber(this);
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
    gui_layout_->addWidget(warnings_panel_,grid_rows-1,3,1,3);
    gui_layout_->addWidget(comms_,grid_rows-1,grid_cols-2,2,1);
    gui_layout_->addWidget(speedometer_,grid_rows,grid_cols-1,1,2);


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
    radar_->resize(w_unit*3, h_unit*3);

    cameras_->resize(w_unit*4, h_unit*3);   // for 16:9 ratio
    cameras_->move(w-spacing-cameras_->width(), spacing); //top right corner

    batteries_->resize(w_unit*6, h_unit*1); //bottom left corner
    batteries_->move(spacing, h - batteries_->height()- spacing);

    console_->resize(w_unit*8, h_unit*4);   //left side, above batteries
    console_->move(spacing, batteries_-> y() - console_->height() - spacing);

    warnings_panel_->resize(w_unit*6, h_unit*1.5); //next to console, above batteries
    warnings_panel_->move(console_->x() + console_->width() + spacing, batteries_->y() -warnings_panel_->height() - spacing);

    speedometer_->resize(w_unit*4, h_unit*1); //bottom right corner
    speedometer_->move(w - spacing-speedometer_->width(), h - spacing -  speedometer_->height());

    comms_->resize(w_unit*1.5, h_unit*7); //bottom, next to speedometer
    comms_->move(speedometer_->x() - comms_->width() - spacing, h - comms_->height() - spacing);
}


