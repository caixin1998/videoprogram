#include "camerathread.h"


CameraThread::CameraThread(QObject *parent) : QObject(parent)
{
    isStop = false;
    camera =new QCamera();
    cameraSurface =new VideoSurface;
	camera->setViewfinder(cameraSurface);

}

void CameraThread:: start()
{
   
    camera->start();

}
