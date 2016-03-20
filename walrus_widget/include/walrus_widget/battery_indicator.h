#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H

#include <QtWidgets>
#include <QResizeEvent>
#include <QPaintEvent>

class BatteryIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryIndicator(QWidget *parent = 0);
    virtual  ~BatteryIndicator();
Q_SIGNALS:

public Q_SLOTS:

protected:
    QLabel* icon_;
    QProgressBar* level_;
    QPixmap* battery_icon_;

    void repaintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


};

#endif // BATTERYINDICATOR_H
