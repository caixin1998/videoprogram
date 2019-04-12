#ifndef MINORSCREEN_H
#define MINORSCREEN_H

#include <QMainWindow>
#include "showimage.h"
#include"videosurface.h"

namespace Ui {
class minorscreen;
}

class minorscreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit minorscreen(VideoSurface *videoSurface,QWidget *parent = nullptr);
    ~minorscreen();

private:
    Ui::minorscreen *ui;
    showImage * mplaywindow;
};

#endif // MINORSCREEN_H
