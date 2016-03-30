#ifndef STYLES_H
#define STYLES_H

#include <QString>
#include <QFont>

namespace Styles {

static const QString primary_color = QString("rgba(75, 75, 75, 50%)");
static const QString secondary_color = QString("rgba(40, 40, 40, 50%)");
static const QString text_select_bkg_color =  QString("rgba(20, 20, 20, 100%)");
static const QString text_select_color =  QString("rgba(230, 230, 230, 75%)");
static const QString transparent =  QString("rgba(0, 0, 0, 0%)");
static const QString battery_green = QString("rgba(5, 225, 5, 100%)");




static const QString style1 = "QLineEdit { background-color: " + Styles::secondary_color +
        "; selection-background-color: " + Styles::text_select_bkg_color +
        "; selection-color: " + Styles::text_select_color +
        "; border: 0 px" + "} \n" +

        "QTextEdit { background-color: " + Styles::primary_color + "} \n" +

        "QProgressBar { background-color: " + Styles::transparent +
        "; border-radius: " + "6px" +
        "; text-align: " + "center" + "} \n" +

        "QProgressBar::chunk { background-color: " + Styles::battery_green + //chunk value change for value below 20%
        "; border-radius: " + "6px" +
        "} \n" +

        "QLCDNumber { background-color: " + Styles::transparent +
        "; border: " + "0px" +
        "; color: " +  Styles::primary_color + "} \n" +

        "QScrollBar { background-color: " + Styles::secondary_color + "} \n";

}

namespace Fonts {

//inline QFont digi(float size = 10){
//    return QFont("DS-Digital",size, QFont::Bold);
//}
static const QFont digi12b = QFont("DS-Digital",12, QFont::Bold);
static const QFont digi10 = QFont("DS-Digital",10);


static const QFont moon10 = QFont("moonhouse",10);


}





#endif // STYLES_H
