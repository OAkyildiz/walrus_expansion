#include "../include/walrus_widget/mainview.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>


MainView::MainView(QWidget *parent) :
    QMainWindow(parent)
{
    scene3d_ = new MapViz();
    //indicators_=new Overlay();

//    indicators_->setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout* main_layout = new QVBoxLayout;
    setCentralWidget( scene3d_);
//    main_layout->addWidget( scene3d_ );
//    setLayout( main_layout );
}

MainView::~MainView() {}

void MainView::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}
