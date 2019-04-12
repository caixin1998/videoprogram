#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H
#include <QSlider>
#include <QMouseEvent>
#include <QCoreApplication>


class customSlider : public QSlider
{
    Q_OBJECT
public:
    customSlider(QWidget *parent = 0) : QSlider(parent)
    {
    }
protected:
    void mousePressEvent(QMouseEvent *ev);//重写QSlider的mousePressEvent事件
signals:
    void costomSliderClicked();//自定义的鼠标单击信号，用于捕获并处理

};

#endif // CUSTOMSLIDER_H
