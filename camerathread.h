#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>

#include <opencv2/opencv.hpp>
#include <QTimer>
#include<string>
#include<QImage>
#include <iostream>

using namespace std;
using namespace cv;
extern QTimer * timer ;
class CameraThread : public QObject
{
    Q_OBJECT
public:
    CameraThread(QObject* parent = nullptr);
    
    VideoCapture  capture;
    
    std::string outDir;
    int rate;
    int mark;
    Mat frame;
    Mat vframe[10000];
    QImage image;
    int index;

    void start_record();
    void stop_record();
    void start_play();
    void stop_play();

   // ~CameraThread();


public slots:
    void start();
    void record_camera();
    void nextFrame();
    void play_video();
signals:
    void showImage(QImage img);

private:
    
    volatile bool isStop;
    QImage  Mat2QImage(Mat);

};

#endif // CAMERATHREAD_H
