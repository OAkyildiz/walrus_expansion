#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QFrame>
#include <QLCDNumber>

#include "indicatorspanel.h"
#include "console.h"
#include "warningspanel.h"
#include "battery_panel.h"
#include "radar.h"
#include "qnode.h"
#include "camera_display.h"
#include "mapviz.h"
#include "odometry_display.h"

class Overlay : public MapViz
{
    Q_OBJECT

public:
    Overlay(QWidget *parent = 0,  qnode::QNode* qnode = 0 );
    ~Overlay(){}

private:
    void initWidgets();
protected Q_SLOTS:
    void toggleVideoSize();

protected:
    qnode::QNode*  qnode_;

    OdometryDisplay* tachometer_;

    Radar* radar_;
    CameraDisplay* cameras_;

    BatteryPanel* batteries_;
    Console* console_;
    WarningsPanel* warnings_panel_;

    IndicatorsPanel* comms_;

    void resizeEvent(QResizeEvent *event);

    int w;
    int h;
    int w_unit;
    int h_unit;
    int spacing;
};




#endif // WIDGET_H
