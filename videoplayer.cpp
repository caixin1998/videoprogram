

#include "videoplayer.h"
#include"showimage.h"
#include"videosurface.h"
#include <QtWidgets>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <qdebug.h>
#include<iostream>
#include "mainwindow.h"


string  childid = "default";
string  videoname = "Samplevideo";
extern MainWindow *w;
using namespace  std;
QString buffer ="./";
VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
{
    text = new QLineEdit(this);
	QString init = "眼睛位置(0,0,0)     视点位置(0,0)    瞳孔大小 0";
    text->setText(init);
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    playwindow = new showImage(this);
    videoSurface = new VideoSurface;
	
    medialist=new QMediaPlaylist;
    medialist->addMedia(QMediaContent(QUrl(buffer+"SampleVideo.mp4")));
    //medialist->addMedia(QMediaContent(QUrl(buffer+"SampleVideo2.mp4")));
    //medialist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    medialist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    m_mediaPlayer->setPlaylist(medialist);
	
    QAbstractButton *addButton = new QPushButton(tr("Add.."));
    QAbstractButton *OpenButton = new QPushButton(tr("Open"));
    QAbstractButton *ReturnButton = new QPushButton(tr("return"));
    QAbstractButton *inputButton = new QPushButton(tr("child id"));
                saveButton        = new QPushButton(tr("save"));      
    playlist = new QComboBox(this);
    playlist->addItem(QString::fromUtf8("playlist"));
    playlist->addItem(QString::fromUtf8("samplevideo"));
    //playlist->addItem(QString::fromUtf8("samplevideo2"));
    connect(addButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);
    connect(OpenButton, &QAbstractButton::clicked, this, &VideoPlayer::playfile);
    connect(ReturnButton, &QAbstractButton::clicked,this, &VideoPlayer::returnmain);
    connect(inputButton, &QAbstractButton::clicked,this, &VideoPlayer::inputdialog);
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
    controlLayout->addWidget(inputButton);
    controlLayout->addWidget(addButton);
    controlLayout->addWidget(playlist);
    controlLayout->addWidget(OpenButton);
    controlLayout->addWidget(ReturnButton);
     controlLayout->addWidget(saveButton);

    QBoxLayout *clayout = new QHBoxLayout;
    clayout->addWidget(m_playButton);
    clayout->addWidget(m_positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
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

    string dirname= ".\\output\\"+childid+"\\"+videoname+"\\"; 
    string command = "mkdir -p " + dirname;
    system(command.c_str());
   
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
	if (s != NULL)
		return s->section(QRegExp("[./]"), -2, -2).trimmed();
	else
		return NULL;
}
void VideoPlayer::playfile()
{
	
    int index=playlist->currentIndex();
	if (index>0)
		medialist->setCurrentIndex(index-1);
	else 
		medialist->setCurrentIndex(0);
    videoname = playlist->currentText().toStdString();
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

void VideoPlayer::inputdialog()
{
    dia =new QInputDialog(this);
    dia->setWindowTitle("child ID");
    dia->setLabelText("Please input child ID:");
    dia->setInputMode(QInputDialog::TextInput);
    if(dia->exec() == QInputDialog::Accepted)
    {
        childid = dia->textValue().toStdString();
        string dirname= ".\\output\\"+childid+"\\"+videoname+"\\"; 
        string command = "mkdir -p " + dirname;
        system(command.c_str());
    }
}

void VideoPlayer::receiveMeaage(QString msg)
{
    text->setText(msg);
}
/*
void VideoPlayer::record_duration()
{
    record->duration = m_mediaPlayer->duration;
}*/