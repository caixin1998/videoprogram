#include "camerascreen.h"
#include <QGridLayout>
#include <QtWidgets/QDesktopWidget>
extern QDesktopWidget *desktop;
CameraScreen::CameraScreen(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    mcamerawindow1 = new showImage(this);
    const QRect availableGeometry = desktop->availableGeometry(this);
    mcamerawindow1->resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
    QGridLayout * layout = new QGridLayout;
    layout->addWidget(mcamerawindow1,0,0);
    setLayout(layout);
}

CameraScreen::~CameraScreen()
{   
}


