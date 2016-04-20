#ifndef WARNING_H
#define WARNING_H

#include "base_indicator.h"
#include <QPropertyAnimation>

class Warning : public BaseIndicator
{
    Q_OBJECT

public:
    explicit Warning(QWidget *parent =0, QString name = "", QString icon_path = Indicators::Placeholder);
    virtual ~Warning() {delete fader_;}


public Q_SLOTS:
    bool update(int value);


protected:

    //bool _bar = True;
    QPropertyAnimation* fader_;

    void resizeEvent(QResizeEvent * event);

private:
    void setFader();


};

#endif // WARNING_H
