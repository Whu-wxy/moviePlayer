#include "mymovie.h"

#include <QFileDialog>
#include <QFile>
#include <QGridLayout>
#include <QMessageBox>
#include <QSpacerItem>
#include <QDebug>
#include <QTime>
#include <QMediaMetaData>
MyMovie::MyMovie(QWidget *parent)
    : QMainWindow(parent)
{
        setWindowTitle("小鸟播放器   1.0.5.171119_Beta");
        setMinimumSize(300,200);
        num=0;


        gifLabel=new QLabel;
        gif=new QMovie("D:/QtWork/Movie/gifsucai.gif");
        gifLabel->setMovie(gif);
        gif->start();
        setCentralWidget(gifLabel);

        playerArea=new QVideoWidget;
        playerArea->setAspectRatioMode(Qt::KeepAspectRatio);//视频等比例缩放
        player = new QMediaPlayer;
        player->setVideoOutput(playerArea);
        connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(slot_durationChanged(qint64)));
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(changeSlider(qint64)));
         connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatus()));

        timeLabel=new QLabel("00:00:00/00:00:00");

        mainControl();
        createActions();
        createMenus();
}

MyMovie::~MyMovie()
{

}

void MyMovie::mainControl()
{

    QWidget *widget = new QWidget();
    QGridLayout *mainlayout=new QGridLayout(widget);


    /////进度条
    playSlider=new QSlider(Qt::Horizontal);
    playSlider->setValue(0);
    connect(playSlider,SIGNAL(valueChanged(int)),this,SLOT(setplay(int)));




    /////控制按钮
    startBtn=new QPushButton;
    startBtn->setFocus(Qt::ActiveWindowFocusReason);
    startBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Play.ico"));
    stopBtn=new QPushButton;
    stopBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Stop.ico"));
    PreBtn=new QPushButton;
    PreBtn->setIcon(QIcon("D:/QtWork/Movie/mm-First.ico"));
    NextBtn=new QPushButton;
    NextBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Last.ico"));

    //音量调节
    voice=new QSlider(Qt::Horizontal);
    voice->setMinimum(0);
    voice->setMaximum(100);
    voice->setValue(50);
    player->setVolume(50);
    voice->setStatusTip("音量");
    connect(voice,SIGNAL(valueChanged(int)),this,SLOT(setVoice()));

    ////静音按钮
    voiceBtn=new QPushButton;
    voiceBtn->setIcon(QIcon("D:/QtWork/Movie/Musical Note.ico"));
    connect(voiceBtn,SIGNAL(clicked(bool)),this,SLOT(clearVoice()));

    startBtn->setMinimumWidth(50);
    stopBtn->setMinimumWidth(50);
    PreBtn->setMinimumWidth(50);
    NextBtn->setMinimumWidth(50);
    connect(NextBtn,SIGNAL(clicked(bool)),this,SLOT(setNext()));
    connect(PreBtn,SIGNAL(clicked(bool)),this,SLOT(setBack()));
    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(playing()));
    connect(stopBtn,SIGNAL(clicked(bool)),this,SLOT(stopplay()));

/////总体布局
    mainlayout->addWidget(playSlider,0,0,0,9);
    mainlayout->addWidget(timeLabel,1,6);
    mainlayout->addWidget(PreBtn,1,1);
    mainlayout->addWidget(startBtn,1,2);
    mainlayout->addWidget(stopBtn,1,3);
    mainlayout->addWidget(NextBtn,1,4);
    mainlayout->addWidget(voiceBtn,1,7,Qt::AlignRight);
    mainlayout->addWidget(voice,1,8,Qt::AlignRight);
    mainlayout->setColumnStretch(0,1);
    mainlayout->setColumnStretch(5,1);
    widget->setMinimumHeight(85);
////dock布局下方按钮
    dock=new QDockWidget(this);
    QWidget *qw=new QWidget;///去掉标题
    dock->setTitleBarWidget(qw);
    dock->setWidget(widget);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
}

void MyMovie::ShowOpenFile()
{
  filename=QFileDialog::getOpenFileName(this, tr("打开视频或音频文件"), "F:/剧",tr("music(*.mp3);;movies (*.avi  *.mp4 *rmvb)"));
 if(!filename.isNull())
  {
      player->setMedia(QUrl::fromLocalFile(filename));
      player->setVideoOutput(playerArea);



          /////不能进行类型的判断，为什么？
//     if(player->audioRole()==QAudio::MusicRole)
// {
     playing();


//   }
//    else if(player->audioRole()==QAudio::VideoRole)
//   {
     gif->stop();
   // takeCentralWidget();
      setCentralWidget(playerArea);
//    }
  }
}

void MyMovie::createActions()
{
   openFileAction=new QAction(QIcon("open.png"),tr("打开"),this);
   openFileAction->setShortcut(tr("Ctrl+O"));
   openFileAction->setStatusTip(tr("打开一个文件"));
   connect(openFileAction,SIGNAL(triggered()),this,SLOT(ShowOpenFile()));

   closeFile=new QAction("关闭");
   connect(closeFile,SIGNAL(triggered(bool)),this,SLOT(closing()));
}

void MyMovie::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(closeFile);
}




void MyMovie::playing()
{
//    bool e=player->isVideoAvailable();
//    if(e==true)
//    {
    startBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Pause.ico"));
    if(num%2==0)
    {
    startBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Pause.ico"));
    player->play();
    num++;
    }
    else
    {
        startBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Play.ico"));
        player->pause();
        num++;
    }
 //   }
//    else
//        QMessageBox::warning(this,"警告","未打开音频或视频",QMessageBox::Ok);
}

void MyMovie::stopplay()
{
     startBtn->setIcon(QIcon("D:/QtWork/Movie/mm-Play.ico"));
     player->stop();
     num=0;
}

void MyMovie::closing()
{
//   int i=QMessageBox::warning(this,"正在关闭这个文件","是否关闭",
//                         QMessageBox::Ok|
//                         QMessageBox::Cancel);
   QMessageBox msgBox;
     msgBox.setText("是否关闭这个文件?");
     msgBox.setWindowTitle("正在关闭文件");
     msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     int ret = msgBox.exec();

     switch (ret)
     {
         case QMessageBox::Ok:
         player->stop();

      //   takeCentralWidget();
         filename.clear();
if(player->audioRole()==QAudio::MusicRole)
{
         gif->setFileName("D:/QtWork/Movie/gifsucai.gif");
        gifLabel->setMovie(gif);
         gif->start();
         setCentralWidget(gifLabel);
}
             break;

         case QMessageBox::Cancel:
             break;

       }

//    if(i==1)
//    {
//        player->stop();
//        filename.clear();
//        setCentralWidget(gifLabel);
//        gif->start();
//    }
//    else if(i==0)
//        return;

}

void MyMovie::setVoice()
{
      int volume=voice->value();
      player->setVolume(volume);

}

void MyMovie::setBack()
{


}
void MyMovie::setNext()
{


}

 void MyMovie::keyPressEvent(QKeyEvent *e)
 {
     if(e->key()==Qt::Key_Space)
         playing();
     else
         return;
 }

 void MyMovie::mousePressEvent(QMouseEvent *)
 {
     if(!filename.isNull()&&playerArea->underMouse())
         playing();
 }

  void MyMovie::clearVoice()
  {
      static bool ok=true;
      static int i;
      if(ok==true)
      {
      voiceBtn->setIcon(QIcon("D:/QtWork/Movie/Musical Note2.png"));
      i=player->volume();
      voice->setValue(0);
      player->setVolume(0);
      ok=false;
      }
      else
        {  voice->setValue(i);
          player->setVolume(i);
          ok=true;
          voiceBtn->setIcon(QIcon("D:/QtWork/Movie/Musical Note.ico"));
      }
  }

void MyMovie::mouseDoubleClickEvent(QMouseEvent *)
{
      if(filename.isNull()&&gifLabel->underMouse())
          ShowOpenFile();
}

void MyMovie::setplay(int position)
{
     player->setPosition(position);

}

void MyMovie::slot_durationChanged(qint64 duration)
{
      playSlider->setRange(0,duration);
}

void MyMovie::changeSlider(qint64 position)
{
    playSlider->setSliderPosition(position);
}

void MyMovie::mediaStatus()
{
    if(player->mediaStatus()==QMediaPlayer::LoadingMedia)
     timeLabel->setText(player->metaData("QMediaMetaData::Title").toString());

}
