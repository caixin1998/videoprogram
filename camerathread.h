#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>
#include<QCamera>
#include<QCameraViewfinder>
#include "videosurface.h"


class CameraThread : public QObject
{
    Q_OBJECT
public:
    CameraThread(QObject* parent = nullptr);
    VideoSurface *cameraSurface;
    QCamera *camera;
   // ~CameraThread();
signals:

public slots:
    void start();

private:

    volatile bool isStop;

};

#endif // CAMERATHREAD_H
