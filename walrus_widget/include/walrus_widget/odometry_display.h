#ifndef ODOMETRYDISPLAY_H
#define ODOMETRYDISPLAY_H



#include "styles.h"

#include <QFrame>
#include <QLCDNumber>
#include <QLabel>

class OdometryDisplay : public QFrame
{
    Q_OBJECT

public:
    OdometryDisplay(QWidget* parent);
    virtual ~OdometryDisplay(){}

public Q_SLOTS:
    void SpeedUpdated(double x, double y, double z);
    void PoseUpdated(double x, double y, double z, double qx, double qy, double qz, double qw);

protected:
    QLCDNumber* speed_;
    QLabel* unit_;

    QLabel* poseX_;
    QLabel* poseY_;
    QLabel* poseZ_;

    QLabel* poseR_;
    QLabel* poseP_;
    QLabel* poseW_;





private:
    void resizeEvent(QResizeEvent * event);


};

#endif // ODOMETRYDISPLAY_H
