

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include <QWidget>
#include "customslider.h"
#include "minorscreen.h"
#include <QInputDialog>
QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
class QComboBox;
class QTextEdit;
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setUrl(const QUrl &url);
    QMediaPlayer* m_mediaPlayer;
    QString getfile(QString*);
    QAbstractButton *saveButton;
    minorscreen *m;
public slots:
    void openFile();
    void play();
    void playfile();
    void returnmain();
    void inputdialog();
    void receiveMeaage(QString msg);

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void slider_progress_clicked();
    void handleError();
private:
    QLineEdit *text;
    QAbstractButton *m_playButton;

    customSlider *m_positionSlider;
    QLabel *m_errorLabel;
    QComboBox* playlist;
    QAbstractButton *inputButton;
    QInputDialog *dia;
    showImage* playwindow;
    QMediaPlaylist *medialist;
    VideoSurface *videoSurface;


};

#endif
