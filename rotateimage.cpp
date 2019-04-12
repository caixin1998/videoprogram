#include "rotateimage.h"



rshowImage::rshowImage(QWidget *parent):QWidget(parent)
{
    showi=new QImage;
    showi->load("D:/videowidget/cover2.png");

}
rshowImage::~rshowImage(){
    delete showi;
}

void rshowImage::paintEvent(QPaintEvent *e)
{
    static QPainter p(this);
	if (showi == NULL) return;
    iw = showi->width();
    ih = showi->height();
    rw = this->width();
    rh = this->height();
    int w=0,h=0;
	if (iw <= 0 || ih <= 0 || rw <= 0 || rh <= 0) return;
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
    p.translate(w/2,h/2); //让图片的中心作为旋转的中心
    p.rotate(180); //顺时针旋转180度
    p.translate(-w/2,-h/2); //使原点复原
    p.drawImage(Temp,*showi);
    p.end();
}

void rshowImage::loadimage(QImage* image)
{
    if(showi==NULL){
        qDebug()<<"error2!";
        return;
    }
    showi=image;
}

void rshowImage::onShowImage(QImage image)
{

    this->loadimage(&image);
    this->repaint();
    this->show();

}
