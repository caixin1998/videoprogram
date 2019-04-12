#include "showimage.h"



showImage::showImage(QWidget *parent):QWidget(parent)
{
    showi=new QImage;
    showi->load("D:/Users/caixin/Documents/videoplayer/cover.png");

}
showImage::~showImage(){
    delete showi;
}

void showImage::paintEvent(QPaintEvent *e)
{
    static QPainter p(this);
	if (showi == NULL) return;
    iw = showi->width();
    ih = showi->height();
    rw = this->width();
    rh = this->height();
    int w=0,h=0;
	if (iw <=0|| ih <=0 || rw<=0 || rh <=0) return;
    if(iw<=rw && ih<=rh)
    {
        if(iw*rh==rw*ih)
        {
            w=iw;
            h=ih;
        }
        else if(iw*rh>rw*ih)
        {
            w=rw;
            h=rw*ih/iw;
        }
        else
        {
            w=rh *iw/ih;
            h=rh;
        }

    }
    else{
        if(iw*rh==rw*ih)
        {
            w=rw;
            h=rh;
        }

        else if(iw*rh>rw*ih)
        {
            w=rw;
            h=rw*ih/iw;
        }
        else
        {
            w=rh *iw/ih;
            h=rh;
        }
    }
    QRect Temp(0,0,w,h);

    p.begin(this);
    p.drawImage(Temp,*showi);
    p.end();
}

void showImage::loadimage(QImage* image)
{
    if(showi==NULL){
        qDebug()<<"error2!";
        return;
    }
    showi=image;
}

void showImage::onShowImage(QImage image)
{

    this->loadimage(&image);
    this->repaint();
    this->show();

}
