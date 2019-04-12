#include "cameraplayer.h"
#include <QLayout>
#include "mainwindow.h"
extern MainWindow *w;
extern VideoSurface *cameraSurface;
cameraplayer::cameraplayer(QWidget *parent): QWidget(parent)
{

    viewfinder=new QCameraViewfinder(this);
    mplaywindow = new rshowImage(this);
    returnbutton = new QPushButton(tr("return"));
    beginbutton = new QPushButton(tr("begin"));
    QBoxLayout *layout = new QVBoxLayout;
    QBoxLayout *clayout = new QHBoxLayout;
    layout->addWidget(viewfinder);
    clayout->addWidget(beginbutton);
    clayout->addWidget(returnbutton);
    layout->addLayout(clayout);
    setLayout(layout);
    connect(returnbutton, &QAbstractButton::clicked,this, &cameraplayer::returnmain);
	//connect(cameraSurface, SIGNAL(showImage(QImage)), mplaywindow, SLOT(onShowImage(QImage)));

}

void cameraplayer::returnmain()
{
    //disconnect(cameraSurface,SIGNAL(showImage(QImage)),mplaywindow,SLOT(onShowImage(QImage)));
    this->hide();
    w->show();
}
