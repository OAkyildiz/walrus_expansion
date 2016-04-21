#ifndef INDICATORS_PANEL_H
#define INDICATORS_PANEL_H

/*Panel of Indicators, the commented out filds arefor hte version
where there is K-V pair of strings and indicators, and a vector of names.
*/


#include <tr1/unordered_map>

#include <QFrame>
#include <QBoxLayout>

#include "base_indicator.h"
//typedef std::tr1::unordered_map<std::string , BaseIndicator*> indicators_dict;

class IndicatorsPanel : public QFrame
{
    Q_OBJECT

public:
    explicit IndicatorsPanel(QWidget* parent = 0, QString name = "",
                             QBoxLayout::Direction dir = QBoxLayout::LeftToRight);
    virtual ~IndicatorsPanel(){}
    void addIndicator(BaseIndicator* indic);
    //void addIndicator(std::string name, QString image);

public Q_SLOTS : //protected
    // signal might be connected to indicators individually or it could be change(name,value)

protected:
   //std::vector<BaseIndicator*> indicators_;
   // void resizeEvent(QResizeEvent *event);
   std::vector<QString> names_ ;


private:

   QBoxLayout* indicators_layout_;
   Qt::Alignment _alignment;

   void SetLayoutAlignment();

};
#endif // INDICATORS_PANEL_H
