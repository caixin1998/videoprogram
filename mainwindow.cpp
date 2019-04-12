#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new VideoPlayer;
    const QRect availableGeometry = desktop->availableGeometry(player);
    player->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    camera =new cameraplayer;
    camera->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    startcamera();
}

MainWindow::~MainWindow()
{
    delete ui;
    camerathread.quit();
    camerathread.wait();
}

void MainWindow::on_pushButton_4_clicked()
{


    player->show();
    player->m->showFullScreen();
    this->hide();
}

void MainWindow::startcamera()
{
    worker=new CameraThread;
    worker->moveToThread(&camerathread);
    connect(&camerathread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker->cameraSurface,SIGNAL(showImage(QImage)),camera->mplaywindow,SLOT(onShowImage(QImage)));
    connect(&camerathread,&QThread::started, worker, &CameraThread:: start);
    //worker->camera->setViewfinder(camera->viewfinder);
    camerathread.start();

}

void MainWindow::on_pushButton_clicked()
{

    camera->show();
    this->hide();
}
