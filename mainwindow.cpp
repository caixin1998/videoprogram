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
    worker1=new CameraThread;
    worker1->moveToThread(&camerathread);
    connect(&camerathread, &QThread::finished, worker1, &QObject::deleteLater);
    connect(worker1,SIGNAL(showImage(QImage)),camera->mplaywindow,SLOT(onShowImage(QImage)));
    connect(worker1,SIGNAL(showImage(QImage)),camera->camerascreen->mcamerawindow1,SLOT(onShowImage(QImage)));
    connect(&camerathread,&QThread::started, worker1, &CameraThread:: start);
    //connect(ui->pushButton ,&QAbstractButton::clicked , worker1, &CameraThread::start_play);
  //  connect(camera->returnbutton ,&QAbstractButton::clicked , worker1, &CameraThread::stop_play);
    connect(camera->returnbutton ,&QAbstractButton::clicked , this, &MainWindow :: camera_return_main);
	//connect(player->m_mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State state)),this ,SLOT(recordcamera(QMediaPlayer::State state)));
    connect(player->m_mediaPlayer,&QMediaPlayer::stateChanged,this ,&MainWindow::recordcamera);
    camerathread.start();
    timer->start();
    worker1->start_play();
    
}

void MainWindow :: camera_return_main()
{
	camera->camerascreen->hide();
	camera -> hide();
    this -> show();
}

void MainWindow::on_pushButton_clicked()
{ 
   // camera->mplaywindow->showi.load("D:/Users/caixin/Documents/videoplayer/cover.png");
    camera->show();
    camera->camerascreen->showFullScreen();
    this->hide();
}

void MainWindow :: recordcamera (QMediaPlayer::State state)
{
    switch(state) {
        case QMediaPlayer::PlayingState:
            worker1->start_record();
            break;
        default:
            //timer->stop();
            worker1->stop_record();
            break;
    }
 
}