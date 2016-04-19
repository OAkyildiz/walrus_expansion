#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H

#include "bar_indicator.h"


class BatteryIndicator : public BarIndicator
{
    Q_OBJECT
public:
    explicit BatteryIndicator(QWidget *parent = 0);
    virtual  ~BatteryIndicator() { delete level_; delete label_; delete nobar_;}

Q_SIGNALS:

public Q_SLOTS:
    void batteryUpdated(double charge = 0) { BarIndicator::valueUpdated(charge); }

protected:


    void repaintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


};

#endif // BATTERYINDICATOR_H
