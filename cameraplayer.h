#ifndef CAMERAPLAYER_H
#define CAMERAPLAYER_H

#include <QWidget>
#include "showimage.h"
#include<QAbstractButton>
#include<QPushButton>
#include "camerascreen.h"
#include "camerathread.h"

QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE

class cameraplayer:public QWidget
{
    Q_OBJECT
public:
    cameraplayer(QWidget *parent = nullptr);
    QAbstractButton *beginbutton;
    showImage * mplaywindow;
    QAbstractButton *returnbutton;
    CameraScreen * camerascreen;
   // QCameraViewfinder *viewfinder;
private:
    

private slots:
    
};

#endif // CAMERAPLAYER_H
