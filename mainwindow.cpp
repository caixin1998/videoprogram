#include "mainwindow.h"
#include "ui_mainwindow.h"

extern string childid;
extern string videoname;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new VideoPlayer;
    const QRect availableGeometry = desktop->availableGeometry(player);
    player->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    connect(player->saveButton, &QAbstractButton::clicked, this, &MainWindow::save_video);
    camera =new cameraplayer;
    camera->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    startcamera();
	connect(timer, SIGNAL(timeout()), this, SLOT(do_record()));
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

void MainWindow :: do_record()
{
    
    if(player->m_mediaPlayer->state()==QMediaPlayer::PlayingState)
    {
        string filename= ".\\output\\"+childid+"\\"+videoname+"\\record.txt";
        outfile.open(filename,ios::app);
        int a=player->m_mediaPlayer->position();
        outfile<<a<<endl;
        cout<<player->m_mediaPlayer->position();
        outfile.close();
    }   

}


void MainWindow::save_video()
{
    string outDir1 = ".\\output\\"+childid+"\\"+videoname+"\\camera1.avi";
    VideoWriter writer(outDir1, CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));  
    //writer << frame;
    for(int i=0;i<worker1->index;i++)
    {
        writer << worker1->vframe[i];
    }  
    worker1->index = 0 ;
    //cout<< outDir1<<endl;

}
