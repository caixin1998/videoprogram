#include "minorscreen.h"
#include "ui_minorscreen.h"

minorscreen::minorscreen(VideoSurface *videoSurface,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::minorscreen)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    mplaywindow = new showImage(this);
    this->setCentralWidget(mplaywindow);
    connect(videoSurface,SIGNAL(showImage(QImage)),mplaywindow,SLOT(onShowImage(QImage)));
}

minorscreen::~minorscreen()
{
    delete ui;
    delete mplaywindow;
}
