#include "walrus_widget/odometry_display.h"

#include <cmath>   


OdometryDisplay::OdometryDisplay(QWidget* parent) : QFrame(parent)
{


    speed_ = new QLCDNumber(this);
    speed_->setSmallDecimalPoint(true);
    speed_->setDigitCount(6);

    unit_= new QLabel("m/s",this);
    unit_->setFont(Fonts::digi12b);
    unit_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

    //Pose table

    poseX_= new QLabel("x:",this);
    poseX_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseX_->setFont(Fonts::digi10);

    poseY_= new QLabel("y:",this);
    poseY_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseY_->setFont(Fonts::digi10);

    poseZ_= new QLabel("z:",this);
    poseZ_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseZ_->setFont(Fonts::digi10);

    poseR_= new QLabel("roll:",this);
    poseR_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseR_->setFont(Fonts::digi10);

    poseP_= new QLabel("pitch:",this);
    poseP_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseP_->setFont(Fonts::digi10);

    poseW_= new QLabel("yaw:",this);
    poseW_->setAlignment(Qt::AlignBottom | Qt::AlignLeft);  poseW_->setFont(Fonts::digi10);



}

void OdometryDisplay::SpeedUpdated(double x, double y, double z)
{
    double speed = round(sqrt(x*x+y*y+z*z)*100)/100; //change this to string


    int i = speed;
    speed_->display(QString("%1").arg(i, 1, 10, QChar('0'))
                       + "."
                       + QString("%1").arg(qRound((speed - i) * 100), 2, 10, QChar('0')));

}

void OdometryDisplay::resizeEvent(QResizeEvent *event)
{
    int w_unit = width()/12;
    int h_unit = height()/8;

    speed_->move(0,h_unit);
    speed_->resize(w_unit*10.5,h_unit*5);

    unit_->move(speed_->width(),speed_->y());
    unit_->resize(w_unit*1.5,h_unit*4.4);

    QSize pose_size = QSize(3*w_unit, h_unit);

    poseX_->resize(pose_size); poseX_->move(w_unit,     speed_->y()+speed_->height());
    poseY_->resize(pose_size); poseY_->move(5*w_unit,   poseX_->y());
    poseZ_->resize(pose_size); poseZ_->move(9*w_unit,   poseX_->y());

    poseR_->resize(pose_size); poseR_->move(w_unit,     poseX_->y()+h_unit);
    poseP_->resize(pose_size); poseP_->move(5*w_unit,   poseR_->y());
    poseW_->resize(pose_size); poseW_->move(9*w_unit,   poseR_->y());

}

void OdometryDisplay::PoseUpdated(double x, double y, double z, double qx, double qy, double qz, double qw)
{
    double r = round(atan2(2*(qx*qy + qz*qw),1-2*( qy*qy + qz*qz))*100)/100;
    double p = round(asin(2*(qx*qz - qw*qy))*100)/100;
    double w = round(atan2(2*(qx*qw + qy*qz),1-2*(  qz*qz + qw*qw))*100)/100;

    poseX_->setText(QString("x: %1").arg(round(x*100)/100));
    poseY_->setText(QString("y: %1").arg(round(y*100)/100));
    poseZ_->setText(QString("z: %1").arg(round(z*100)/100));

    poseR_->setText(QString("roll: %1").arg(r));
    poseP_->setText(QString("pitch: %1").arg(p));
    poseW_->setText(QString("yaw: %1").arg(w));

}
