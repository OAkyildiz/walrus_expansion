#ifndef INDICATORSPANEL_H
#define INDICATORSPANEL_H

#include <tr1/unordered_map>

#include <QFrame>
#include <QBoxLayout>

#include "indicator.h"
typedef std::tr1::unordered_map<std::string , Indicator*> indicators_dict;

class IndicatorsPanel : public QFrame
{
    Q_OBJECT

public:
    explicit IndicatorsPanel(QWidget* parent = 0,  QBoxLayout::Direction dir = QBoxLayout::LeftToRight);
    virtual ~IndicatorsPanel(){}
    void addIndicator(Indicator* indic);
    void addIndicator(std::string name, QString image);

public Q_SLOTS : //protected
    // signal might be connected to indicators individually or it could be change(name,value)

protected:
   indicators_dict indicators_dict_;
   void resizeEvent(QResizeEvent *event);

private:
   QBoxLayout* indicators_layout_;

   std::vector<std::string> indicators_keys_ ;

};
#endif // INDICATORSPANEL_H
