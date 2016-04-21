#ifndef ITER_INDICATOR_H
#define ITER_INDICATOR_H

#include "base_indicator.h"

class  IterIndicator: public BaseIndicator
{
    Q_OBJECT

public:
    IterIndicator(QString name = "", QString icon_path = Indicators::Placeholder);
    virtual ~IterIndicator() {delete &images_;}

    void addImage(QString resource);
    void addImage(QPixmap* pixmap);

    void setErrorIndex(int err);

public Q_SLOTS:
    bool update(int value);


protected:
    int _size;
    int _error_index;
    std::vector<QPixmap*> images_;
    void resizeEvent(QResizeEvent * event);

};

#endif // ITER_INDICATOR_H
