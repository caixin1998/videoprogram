

#include "videoplayer.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include "minorscreen.h"
#include "mainwindow.h"

#include <iostream>     // std::cout
#include <cstdlib>    
#include <new>          
QDesktopWidget *desktop;
MainWindow * w;
QTimer * timer;
typedef struct videorecord
{
    float eye_x;
    float eye_y;
    float eye_z;
    float gaze_x;
    float gaze_y;
    qint64 duration;
} videorecord_t;

videorecord_t record;

void init_record(videorecord_t record)
{
    record.eye_x = 0.0;
    record.eye_y = 0.0;
    record.eye_z = 0.0;
    record.gaze_x = 0.0;
    record.gaze_y = 0.0;
    record.duration = 0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    init_record(record);
	timer = new QTimer();
    timer->setInterval(40);
    QCoreApplication::setApplicationName("Video Widget Example");
    QCoreApplication::setOrganizationName("QtProject");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    desktop = QApplication::desktop();
    w = new MainWindow;
    const QRect availableGeometry = desktop->availableGeometry(w);
    w->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    w->show();
  
    return app.exec();
}
