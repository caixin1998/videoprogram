/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "videoplayer.h"
#include"showimage.h"
#include"videosurface.h"
#include <QtWidgets>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <qdebug.h>
#include<iostream>
#include "mainwindow.h"
extern MainWindow *w;
using namespace  std;
QString buffer ="D:/chrome_download/";
VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
{
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    playwindow = new showImage(this);
    videoSurface = new VideoSurface;
    medialist=new QMediaPlaylist;
    medialist->addMedia(QMediaContent(QUrl(buffer+"SampleVideo.mp4")));
    medialist->addMedia(QMediaContent(QUrl(buffer+"SampleVideo2.mp4")));
    medialist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    m_mediaPlayer->setPlaylist(medialist);
    QAbstractButton *addButton = new QPushButton(tr("Add.."));
    QAbstractButton *OpenButton = new QPushButton(tr("Open"));
    QAbstractButton *ReturnButton = new QPushButton(tr("return"));
    playlist = new QComboBox(this);
    playlist->addItem(QString::fromUtf8("playlist"));
    playlist->addItem(QString::fromUtf8("simplevideo"));
    playlist->addItem(QString::fromUtf8("simplevideo2"));
    connect(addButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);
    connect(OpenButton, &QAbstractButton::clicked, this, &VideoPlayer::playfile);
    connect(ReturnButton, &QAbstractButton::clicked,this, &VideoPlayer::returnmain);
    m_playButton = new QPushButton;
    //m_playButton->setEnabled(false);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

    m_positionSlider = new customSlider(this);
    m_positionSlider->setOrientation(Qt::Horizontal);
    m_positionSlider->setRange(0, 0);

    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
            this, &VideoPlayer::setPosition);
    connect(m_positionSlider,&customSlider::costomSliderClicked ,this,&VideoPlayer::slider_progress_clicked);
    m_errorLabel = new QLabel;
    m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(addButton);
    controlLayout->addWidget(playlist);
    controlLayout->addWidget(OpenButton);
    controlLayout->addWidget(ReturnButton);

    QBoxLayout *clayout = new QHBoxLayout;
    clayout->addWidget(m_playButton);
    clayout->addWidget(m_positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(playwindow);
    layout->addLayout(clayout);
    layout->addLayout(controlLayout);
    layout->addWidget(m_errorLabel);

    setLayout(layout);

    m_mediaPlayer->setVideoOutput(videoSurface);

    connect(videoSurface,SIGNAL(showImage(QImage)),playwindow,SLOT(onShowImage(QImage)));
    connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
            this, &VideoPlayer::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
    connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &VideoPlayer::handleError);

   if(desktop->screenCount()>1)
   {
        m=new minorscreen(videoSurface);
        m->setGeometry(desktop->screenGeometry(1));

   }
}

VideoPlayer::~VideoPlayer()
{
      //delete medialist;
      //delete playwindow;
      //delete videoSurface;
    //if(m!=nullptr)
    //    delete m;
}

void VideoPlayer::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Movie"));
    QStringList supportedMimeTypes = m_mediaPlayer->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty())
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
    {
        setUrl(fileDialog.selectedUrls().constFirst());
    }
}

void VideoPlayer::setUrl(const QUrl &url)
{
    m_errorLabel->setText(QString());
    QString *s= new QString(url.isLocalFile() ? url.toLocalFile() : QString());
    setWindowFilePath(*s);
    playlist->addItem(getfile(s));
    medialist->addMedia(url);
}

void VideoPlayer::play()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
}

void VideoPlayer::slider_progress_clicked()
{
    m_mediaPlayer->setPosition(m_positionSlider->value());
}
void VideoPlayer::handleError()
{
    m_playButton->setEnabled(false);
    const QString errorString = m_mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(m_mediaPlayer->error()));
    else
        message += errorString;
    m_errorLabel->setText(message);
}
QString VideoPlayer::getfile(QString* s)
{

     return s->section(QRegExp("[./]"), -2, -2).trimmed() ;
}
void VideoPlayer::playfile()
{
    int index=playlist->currentIndex();
    medialist->setCurrentIndex(index-1);
    m_mediaPlayer->play();
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}
void VideoPlayer::returnmain()
{
    w->show();
    this->hide();
    m->hide();
    m_mediaPlayer->pause();
}
