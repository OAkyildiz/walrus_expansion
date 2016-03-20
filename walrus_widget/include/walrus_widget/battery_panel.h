#ifndef BATTERYPANEL_H
#define BATTERYPANEL_H



#include <QFrame>
#include <QHBoxLayout>

#include "battery_indicator.h"

class BatteryPanel : public QFrame
{
    Q_OBJECT

public:
    explicit BatteryPanel(QWidget* parent = 0);
    virtual ~BatteryPanel();

Q_SIGNALS:
   //void batteryLow(){}

public Q_SLOTS: //protected
    // signal might be connected to indicators individually or it could be change(name,value)
   //void updateVaule();

protected:
   BatteryIndicator* battery1_;
   BatteryIndicator* battery2_;
   BatteryIndicator* battery3_;
   BatteryIndicator* battery4_;

   void resizeEvent(QResizeEvent *event);
private:
   QHBoxLayout* layout_;

};

#endif // BATTERYPANEL_H
