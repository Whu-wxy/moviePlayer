#ifndef MYMOVIE_H
#define MYMOVIE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QButtonGroup>
#include <QDockWidget>
#include <QSlider>
#include <QSplitter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMovie>
#include <QLabel>
class MyMovie : public QMainWindow
{
    Q_OBJECT

public:
    MyMovie(QWidget *parent = 0);
    ~MyMovie();

    void createMenus();
    void createActions();
    void mainControl();
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
QLabel *gifLabel;
QMovie *gif;

    int num;//记录播放暂停
     QString filename;
     QDockWidget *dock;
     QSplitter *split;
     QVideoWidget *playerArea;
     QMediaPlayer *player;
     QMovie *mv;
/////Menu
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *tryDlg;
///////fileMenu
    QAction *openFileAction;
    QAction *closeFile;
//////Buttons
    QSlider *voice;
    QPushButton *voiceBtn;
    QSlider *playSlider;
    QLabel *timeLabel;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *PreBtn;
    QPushButton *NextBtn;


public slots:
    void ShowOpenFile();
    void playing();
    void stopplay();
    void closing();
    void setVoice();
    void clearVoice();
    void setBack();
    void setNext();
    void setplay(int);//手动控制滑块
    void slot_durationChanged(qint64);///自动调整滑块范围
    void changeSlider(qint64);////滑块随视频动
    void mediaStatus();

};

#endif // MYMOVIE_H
