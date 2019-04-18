#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<fstream>
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
    CameraThread *worker1;
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();
    void camera_return_main();
    void on_pushButton_clicked();
    void recordcamera(QMediaPlayer::State);
    void do_record();
    void save_video();

private:
    Ui::MainWindow *ui;
    void startcamera();
    ofstream outfile;
};

#endif // MAINWINDOW_H
