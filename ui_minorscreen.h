/********************************************************************************
** Form generated from reading UI file 'minorscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINORSCREEN_H
#define UI_MINORSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_minorscreen
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *minorscreen)
    {
        if (minorscreen->objectName().isEmpty())
            minorscreen->setObjectName(QString::fromUtf8("minorscreen"));
        minorscreen->resize(800, 600);
        centralwidget = new QWidget(minorscreen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(210, 190, 120, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        minorscreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(minorscreen);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        minorscreen->setMenuBar(menubar);
        statusbar = new QStatusBar(minorscreen);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        minorscreen->setStatusBar(statusbar);

        retranslateUi(minorscreen);

        QMetaObject::connectSlotsByName(minorscreen);
    } // setupUi

    void retranslateUi(QMainWindow *minorscreen)
    {
        minorscreen->setWindowTitle(QApplication::translate("minorscreen", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class minorscreen: public Ui_minorscreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINORSCREEN_H
