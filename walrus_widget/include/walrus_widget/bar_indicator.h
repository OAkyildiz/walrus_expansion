#ifndef BAR_INDICATOR_H
#define BAR_INDICATOR_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QProgressBar>
#include <QString>

class BarIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit BarIndicator(QWidget *parent = 0, QString icon_path = QString(), Qt::Orientation orientation = Qt::Horizontal);
    virtual ~BarIndicator() {delete level_; delete label_; delete nobar_;}

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

Q_SIGNALS:

public Q_SLOTS:
    void valueUpdated(double value);

protected:
    QLabel* label_; //icon holder
    QProgressBar* level_;
    QPixmap* icon_;
    QLabel* nobar_;

    Qt::Orientation _orientation;


    virtual void repaintEvent(QPaintEvent *event) = 0;
    void resizeEvent(QResizeEvent *event);

};

#endif // BAR_INDICATOR_H
