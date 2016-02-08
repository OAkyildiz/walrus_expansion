#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QWidget>
#include "../include/walrus_widget/mapviz.h"
#include "../include/walrus_widget/overlay.h"
class MainView : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    void showNoMasterMessage();
Q_SIGNALS:

public Q_SLOTS:

private:
    MapViz* scene3d_;
    Overlay* indicators_;

};

#endif // MAINVIEW_H


