#include "walrus_widget/warning.h"

#include <QGraphicsOpacityEffect>
#include <QEasingCurve>

Warning::Warning(QWidget* parent = 0, QString name = QString(), QString image = QString()):
    QLabel(parent),
    name_(name),
    icon_(new QPixmap(image))
{
    //scaled(size())
   // setPixmap(*icon_);
    setFader();

}


void Warning::startFade()
{
    fader_->start();
    switch_ = true;

}

void Warning::stopFade()
{
    fader_->stop();
    switch_ = false;
}

void Warning::setFader()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);


    fader_ = new QPropertyAnimation(eff,"opacity");
    //Animation Cycle
    fader_->setDuration(4000);
    fader_->setStartValue(0.8);
    fader_->setKeyValueAt(0.5, 0);
    fader_->setEndValue(0.8);
    fader_->setEasingCurve(QEasingCurve::InOutCubic);
    fader_->setLoopCount(-1);
    //a->start(QPropertyAnimation::DeleteWhenStopped);
    //connect(a,SIGNAL(finished()),this,SLOT(hideThisWidget()));
}


void Warning::resizeEvent(QResizeEvent * event){
    *icon_=icon_->scaledToHeight(height());
    setPixmap(*icon_);

}
