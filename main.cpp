

#include "videoplayer.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include "minorscreen.h"
#include "mainwindow.h"
QDesktopWidget *desktop;
MainWindow * w;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Video Widget Example");
    QCoreApplication::setOrganizationName("QtProject");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    desktop = QApplication::desktop();
    w = new MainWindow;
    const QRect availableGeometry = desktop->availableGeometry(w);
    w->resize(availableGeometry.width() / 2, availableGeometry.height() / 3*2);
    w->show();
    /*
    minorscreen m;
    m.setGeometry(desktop->screenGeometry(1));
    m.showFullScreen();
    */
    return app.exec();
}
