#ifndef WIDGET_H
#define WIDGET_H


#include <QtWidgets>
#include <QFrame>
#include <QLCDNumber>

#include "indicatorspanel.h"
#include "console.h"
#include "warningspanel.h"
#include "battery_panel.h"
#include "radar.h"
#include "qnode.h"
#include "camera_display.h"

class Overlay : public QFrame
{
    Q_OBJECT

public:
    Overlay(QWidget *parent = 0,  qnode::QNode* qnode = 0 );
    ~Overlay(){}

private:
    void loadWidgets(qnode::QNode* qnode);


protected:

    QLCDNumber* speedometer_;

    Radar* radar_;
    CameraDisplay* cameras_;

    BatteryPanel* batteries_;
    Console* console_;
    WarningsPanel* warnings_panel_;

    IndicatorsPanel* comms_;

    void resizeEvent(QResizeEvent *event);

};




#endif // WIDGET_H
