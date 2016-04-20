#ifndef BASE_INDICATOR_H
#define BASE_INDICATOR_H

#include <string>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include "walrus_widget/styles.h"


class BaseIndicator : public QWidget
{
    Q_OBJECT

public:
    static const int ERROR_VALUE = -1;
    BaseIndicator(QWidget *parent =0, QString name = "", QString icon_path = Indicators::Placeholder);
    virtual ~BaseIndicator() {delete icon_; delete label_; delete nobar_;}
    int addImage(QString resource);


    QString name() const;

    int value() const;
    void setValue(int value);

    QPixmap *icon() const;
    void setIcon(QPixmap *icon);

protected Q_SLOTS:

public Q_SLOTS:
    void valueUpdated(int value);
    virtual bool update(int value) {setValue(value);}


protected:

    const QString name_;

    QLabel* label_; // icon holder
    QPixmap* icon_;

    QLabel* nobar_; // diagonal red bar
    QPixmap* nobar_icon_;

    int _value;

    void resizeEvent(QResizeEvent *event);

};

#endif // BASE_INDICATOR_H
