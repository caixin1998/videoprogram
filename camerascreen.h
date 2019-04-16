#ifndef CAMERASCREEN_H
#define CAMERASCREEN_H

#include <QMainWindow>
#include "showimage.h"



class CameraScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraScreen(QWidget *parent = nullptr);
    ~CameraScreen();
    showImage * mcamerawindow1;
};
#endif