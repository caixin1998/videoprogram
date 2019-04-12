#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QThread>
#include "videoplayer.h"
#include "cameraplayer.h"
#include "camerathread.h"
extern QDesktopWidget *desktop;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread camerathread;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    VideoPlayer *player;
    cameraplayer *camera;
    CameraThread *worker;
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void startcamera();
};

#endif // MAINWINDOW_H
