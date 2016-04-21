#include "walrus_widget/warning.h"

#include <QGraphicsOpacityEffect>
#include <QEasingCurve>

Warning::Warning(QString name, QString icon_path):
    BaseIndicator(name,icon_path)

{

    setFader();

}


bool Warning::update(int value)
{
    setValue(value);
    if (value == 1)
        fader_->start();

    else if (value == 0)
        fader_->stop();


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
    label_->resize(size());
    *icon_ = icon_->scaled(size(), Qt::KeepAspectRatio);
    label_->setPixmap(*icon_);

    nobar_->resize(size());
    nobar_->setPixmap(nobar_->pixmap()->scaled(size(),Qt::KeepAspectRatio));
}
