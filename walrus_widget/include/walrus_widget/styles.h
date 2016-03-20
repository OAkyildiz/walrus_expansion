#ifndef STYLES_H
#define STYLES_H

#include <QString>
namespace Styles {

    QString primary_color = QString("rgba(75, 75, 75, 50%)");
    QString secondary_color = QString("rgba(40, 40, 40, 50%)");
    QString text_select_bkg_color =  QString("rgba(20, 20, 20, 100%)");
    QString text_select_color =  QString("rgba(230, 230, 230, 75%)");
    QString transparent =  QString("rgba(0, 0, 0, 0%)");
    QString battery_green = QString("rgba(5, 225, 5, 100%)");


    QString style1 = "QLineEdit { background-color: " + Styles::secondary_color +
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

            "QScrollBar { background-color: " + Styles::secondary_color + "} \n";
}





#endif // STYLES_H
