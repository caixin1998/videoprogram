#include "cameraplayer.h"
#include <QLayout>
#include "mainwindow.h"
extern MainWindow *w;
extern VideoSurface *cameraSurface;
cameraplayer::cameraplayer(QWidget *parent): QWidget(parent)
{

   // viewfinder=new QCameraViewfinder(this);
    mplaywindow = new showImage(this);
    returnbutton = new QPushButton(tr("return"));
    beginbutton = new QPushButton(tr("begin"));
    QBoxLayout *layout = new QVBoxLayout;
    QBoxLayout *clayout = new QHBoxLayout;
    layout->addWidget(mplaywindow);
    clayout->addWidget(beginbutton);
    clayout->addWidget(returnbutton);
    layout->addLayout(clayout);
    setLayout(layout);
	//connect(cameraSurface, SIGNAL(showImage(QImage)), mplaywindow, SLOT(onShowImage(QImage)));
    if(desktop->screenCount()>1)
   {
        camerascreen=new CameraScreen();
        camerascreen->setGeometry(desktop->screenGeometry(1));

   }
}


