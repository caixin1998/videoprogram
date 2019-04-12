#ifndef CAMERAPLAYER_H
#define CAMERAPLAYER_H

#include <QWidget>
#include "rotateimage.h"
#include<QAbstractButton>
#include<QPushButton>
#include "videosurface.h"
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
    rshowImage * mplaywindow;
    QCameraViewfinder *viewfinder;
private:
    QAbstractButton *returnbutton;

private slots:
    void returnmain();
};

#endif // CAMERAPLAYER_H
