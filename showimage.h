#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H


#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include<qdebug.h>
class showImage:public QWidget
{
    Q_OBJECT
public:
    showImage(QWidget *parent = 0);
    ~showImage();
    QImage* showi;

    void paintEvent(QPaintEvent *e);
    void loadimage(QImage* image);
    int rw,rh,iw,ih;
private slots:
    void onShowImage(QImage image);
};
#endif // SHOWIMAGE_H
