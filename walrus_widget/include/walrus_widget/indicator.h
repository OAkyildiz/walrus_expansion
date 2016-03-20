#ifndef INDIC_H
#define INDIC_H

#include <string>
#include <QLabel>
#include <QPixmap>

class Indicator : public QLabel
{
    Q_OBJECT

public:
    Indicator(QWidget *parent, QString name, QString def_image_path);
    virtual ~Indicator() {}
    int addImage(QString resource);


    QString name() const;
//protected Q_SLOTS:

public Q_SLOTS:
    void switchImage(int sel);


protected:
    QString name_;
    std::vector<QPixmap*> images_;
    int current_;
    void resizeEvent(QResizeEvent * event);

};

#endif // INDIC_H
