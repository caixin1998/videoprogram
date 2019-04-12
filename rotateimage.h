#ifndef RSHOWIMAGE_H
#define RSHOWIMAGE_H


#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include<qdebug.h>
class rshowImage:public QWidget
{
    Q_OBJECT
public:
    rshowImage(QWidget *parent = 0);
    ~rshowImage();
    QImage* showi;

    void paintEvent(QPaintEvent *e);
    void loadimage(QImage* image);
    int rw,rh,iw,ih;
private slots:
    void onShowImage(QImage image);
};
#endif // RSHOWIMAGE_H
