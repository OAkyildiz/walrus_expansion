#ifndef STYLES_H
#define STYLES_H

#include <QString>
#include <QFont>
#include <ros/package.h>

static const QString widget_path = QString::fromStdString(ros::package::getPath("walrus_widget"));
static const QString img_path = widget_path + "/resources/images";

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


namespace Indicators {

 static const QString Placeholder = QString(img_path + "/placeholder64.gif");

 static const QString NoBar = QString(img_path + "/nobar.png");

 static const QString Battery1 = QString(img_path + "/battery/h-battery1.png");

 static const QString cotnroller = QString(img_path + "/indic/controller1.png");

 namespace PC{
    static const QString CPU = QString(img_path + "/pc/ram2.png");
    static const QString Memory = QString(img_path + "/pc/cpu-512.png");
    static const QString Temperature = QString(img_path + "/indic/therm_inside.png");
 }

 namespace Environment{
     static const QString CO = QString(img_path + "/enviro/CO_128.png");
     static const QString LPG = QString(img_path + "/enviro/lpg-128.png");
     static const QString H = QString(img_path + "/enviro/h2-512.png");
     static const QString CNG = QString(img_path + "/enviro/cng-512.png");
     static const QString Humidity = QString(img_path + "/enviro/humidity_512.png");
     static const QString Temperature = QString(img_path + "/indic/thermoC");

 }

 namespace Wifi{
    //static const QString None = QString(img_path + "/indic");
    static const QString Poor = QString(img_path + "/indic/wifi_0_512.png");
    static const QString Weak = QString(img_path + "/indic/wifi_1_512.png");
    static const QString Fair = QString(img_path + "/indic/wifi_2_512.png");
    static const QString Strong = QString(img_path + "/indic/wifi_full_512.png");
 }

}

namespace Warnings {

static const QString NoBar = QString(img_path + "/nobar.png");
static const QString Water1 = QString(img_path + "/warnings/water1.jpg");
static const QString Water2 = QString(img_path + "/warnings/water_icon.png");
static const QString Overheat = QString(img_path + "/warnings/overheat2-512.jpg");
static const QString LowBattery = QString(img_path + "/warnings/battery_gray.png");


}




#endif // STYLES_H
