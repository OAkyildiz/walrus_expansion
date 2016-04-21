#ifndef BAR_INDICATOR_H
#define BAR_INDICATOR_H

#include <QPaintEvent>
#include <QProgressBar>

#include "base_indicator.h"
class BarIndicator : public BaseIndicator
{
    Q_OBJECT
public:
    explicit BarIndicator(QString name = "", QString icon_path = Indicators::Placeholder,
                          Qt::Orientation orientation = Qt::Horizontal);
    virtual ~BarIndicator() {delete level_;}

    Qt::Orientation orientation() const;

    int value() const;
    void setValue(int value);

Q_SIGNALS:

public Q_SLOTS:
    bool update(int value);
protected:
    QProgressBar* level_;
    Qt::Orientation _orientation;

    virtual void repaintEvent(QPaintEvent *event) = 0;
    void resizeEvent(QResizeEvent *event);

};

#endif // BAR_INDICATOR_H
