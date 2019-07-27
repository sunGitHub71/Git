#include "playctrl.h"
#include "resource_tr.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QFileDialog>
#include <QStyleOption>
#include <QPainter>
#include <QSlider>
#include <QTimer>
#include <QDebug>
#include <QStyle>
#include "playview.h"
#include "playlist.h"

PlayCtrl::PlayCtrl(QWidget *parent)
	:QWidget(parent)
	,m_isPressed(false)
	,m_isHidePlayList(true)
	,m_isOpenSound(false)
{	
	setFixedHeight(100);
	setMouseTracking(true);
	setObjectName("PlayCtrl");
	setStyleSheet("#PlayCtrl{background-color:#262626;border-right:1px solid #000000;}");

	m_silderWidget = new QWidget;
	m_silder = new QSlider(Qt::Horizontal);
	m_silder->setObjectName("Slider");

	m_totalTimeLabel = new QLabel(tr("00:00:00"));
	m_totalTimeLabel->setAlignment(Qt::AlignCenter);
	m_totalTimeLabel->setObjectName("TotalTime");
	
	m_currentTimeLabel = new QLabel(tr("00:00:00"));
	m_currentTimeLabel->setAlignment(Qt::AlignCenter);
	m_currentTimeLabel->setObjectName("CurrentTime");

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(10,0,10,0);
	hl->setSpacing(5);
	hl->addWidget(m_currentTimeLabel);
	hl->addWidget(m_silder);
	hl->addWidget(m_totalTimeLabel);
	m_silderWidget->setLayout(hl);
	
	m_leftWidget = new QWidget;
	m_leftWidget->setFixedWidth(200);
	m_hidePlayList = new QPushButton;
	m_hidePlayList->setFocusPolicy(Qt::NoFocus);
	m_hidePlayList->setObjectName("HidePlayList");
	m_hidePlayList->setStyleSheet("#HidePlayList{background-image:url(" + getPath() + BTN_HIDELIST_NOR + ")} #HidePlayList:hover{background-image:url(" + getPath() + BTN_HIDELIST_PRESS + ")}");

	m_openFileDir = new QPushButton;
	m_openFileDir->setFocusPolicy(Qt::NoFocus);
	m_openFileDir->setObjectName("OpenFileDir");
	m_openFileDir->setStyleSheet("#OpenFileDir{background-image:url(" + getPath() + BTN_OPEN_NOR + ")} #OpenFileDir:hover {background-image:url(" + getPath() + BTN_OPEN_PRESS + ")}");

	m_checkVideo = new QPushButton;
	m_checkVideo->setFocusPolicy(Qt::NoFocus);
	m_checkVideo->setObjectName("CheckVideo");
	m_checkVideo->setStyleSheet("#CheckVideo{background-image:url(" + getPath() + BTN_CHECK_NOR + ")} #CheckVideo:hover {background-image:url(" + getPath() + BTN_CHECK_PRESS + ")}");

	QHBoxLayout *hl1 = new QHBoxLayout;
	hl1->setContentsMargins(10,0,0,0);
	hl1->setSpacing(10);
	hl1->addWidget(m_hidePlayList);
	hl1->addWidget(m_openFileDir);
	hl1->addWidget(m_checkVideo);
	hl1->addStretch();
	m_leftWidget->setLayout(hl1);

	m_CenterWidget = new QWidget;
	m_stopPlay = new QPushButton;
	m_stopPlay->setFocusPolicy(Qt::NoFocus);
	m_stopPlay->setObjectName("StopPlay");
	m_stopPlay->setEnabled(false);
	m_stopPlay->setStyleSheet("#StopPlay::disabled {background-image:url(" + getPath() + BTN_PAUSE_DIS + ")}");

	m_slowForward = new QPushButton;
	m_slowForward->setFocusPolicy(Qt::NoFocus);
	m_slowForward->setObjectName("SlowForward");
	m_slowForward->setShortcut(QString("Ctrl+Left"));
	m_slowForward->setEnabled(false);
	m_slowForward->setStyleSheet("#SlowForward::disabled{background-image:url(" + getPath() + BTN_SLOW_DIS + ")}");

	m_play = new QPushButton;
	m_play->setFocusPolicy(Qt::NoFocus);
	m_play->setObjectName("Play");
	m_play->setFocus();
	m_play->setStyleSheet("#Play{background-image:url(" + getPath() + BTN_PLAY_NOR + ")} #Play:hover {background-image:url(" + getPath() + BTN_PLAY_PRESS + ")}");

	m_fastForward = new QPushButton;
	m_fastForward->setFocusPolicy(Qt::NoFocus);
	m_fastForward->setObjectName("FastForward");
	m_fastForward->setEnabled(false);
	m_fastForward->setStyleSheet("#FastForward::disabled{background-image:url(" + getPath() + BTN_FAST_DIS + ")}");
	
	m_frameForward = new QPushButton;
	m_frameForward->setFocusPolicy(Qt::NoFocus);
	m_frameForward->setObjectName("FrameForward");
	m_frameForward->setEnabled(false);
	m_frameForward->setStyleSheet("#FrameForward::disabled{background-image:url(" + getPath() + BTN_NEXTFRAME_DIS + ")}");

	QHBoxLayout *hl2 = new QHBoxLayout;
	hl2->setContentsMargins(0,0,0,0);
	hl2->setSpacing(20);
	hl2->addStretch();
	hl2->addWidget(m_stopPlay);
	hl2->addWidget(m_slowForward);
	hl2->addWidget(m_play);
	hl2->addWidget(m_fastForward);
	hl2->addWidget(m_frameForward);
	hl2->addStretch();
	m_CenterWidget->setLayout(hl2);

	m_rightWidget = new QWidget;
	m_rightWidget->setFixedWidth(100);

	m_mute = new QPushButton;
	m_mute->setFocusPolicy(Qt::NoFocus);
	m_mute->setObjectName("Mute");
	m_mute->setStyleSheet("#Mute{background-image:url(" + getPath() + BTN_MUTE_NOR + ")} #Mute:hover {background-image:url(" + getPath() + BTN_MUTE_PRESS + ")}");

	m_closeAudio = new QPushButton;
	m_closeAudio->setObjectName("CloseAudio");
	m_closeAudio->setStyleSheet("#CloseAudio{background-image:url(" + getPath() + BTN_MUTE_NOR + ")} #CloseAudio:hover {background-image:url(" + getPath() + BTN_MUTE_PRESS + ")}");
	m_closeAudio->hide();

	m_windowDivision = new QPushButton;
	m_windowDivision->setFocusPolicy(Qt::NoFocus);
	m_windowDivision->setObjectName("WindowDivision");
	m_windowDivision->setStyleSheet("#WindowDivision{background-image:url(" + getPath() + BTN_VIEW_NOR + ")} #WindowDivision:hover {background-image:url(" + getPath() + BTN_VIEW_PRESS + ")}");

	QHBoxLayout *hl3 = new QHBoxLayout;
	hl3->setContentsMargins(0,0,10,0);
	hl3->setSpacing(10);
	hl3->addWidget(m_mute);
	hl3->addWidget(m_closeAudio);
	hl3->addWidget(m_windowDivision);
	m_rightWidget->setLayout(hl3);

	QHBoxLayout *hl4 = new QHBoxLayout;
	hl4->setContentsMargins(0,0,0,10);
	hl4->setSpacing(0);
	hl4->addWidget(m_leftWidget);
	hl4->addWidget(m_CenterWidget);
	hl4->addWidget(m_rightWidget);
	
	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_silderWidget);
	vl->addLayout(hl4);
	setLayout(vl);

	initPlayCtrlUi();

	m_silder->installEventFilter(this);

	_timer = new QTimer(this);
	connect(_timer,SIGNAL(timeout()),this,SLOT(onTimerTimeout()));
	_timer->start(100);
	
	connect(m_hidePlayList,SIGNAL(clicked()),this,SLOT(hideOrShowPlayList()));
	connect(m_mute,SIGNAL(clicked()),this,SLOT(openOrCloseSound()));
	connect(m_openFileDir,SIGNAL(clicked()),this,SLOT(openDir()));
	connect(m_checkVideo, SIGNAL(clicked()), this, SIGNAL(checkVideoSignal()));
	connect(m_play,SIGNAL(clicked()),this,SIGNAL(startPlay()));
	connect(m_stopPlay,SIGNAL(clicked()),this,SIGNAL(stopPlay()));
	connect(m_slowForward,SIGNAL(clicked()),this,SIGNAL(slowForward()));
	connect(m_fastForward,SIGNAL(clicked()),this,SIGNAL(fastForward()));
	connect(m_frameForward,SIGNAL(clicked()),this,SIGNAL(frameForward()));
}
PlayCtrl::~PlayCtrl()
{
	
}
void PlayCtrl::paintEvent(QPaintEvent *event){
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}
void PlayCtrl::keyPressEvent(QKeyEvent *event){
	if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_D))
	{
		openDir();
	}else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
	{
		emit stopPlay();
	}
	else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_L))
	{
		emit slowForward();
	}else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_R))
	{
		emit fastForward();
	}else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F))
	{
		emit frameForward();
	}else if (event->key() == Qt::Key_Space)
	{
		emit startPlay();
	}
}
void PlayCtrl::initPlayCtrlUi()
{
	m_hidePlayList->setToolTip(tr("Hide PlayList"));
	m_openFileDir->setToolTip(tr("Open File folder"));
	m_stopPlay->setToolTip(tr("Stop Play"));
	m_slowForward->setToolTip(tr("Slow Forward"));
	m_play->setToolTip(tr("Play"));

	m_fastForward->setToolTip(tr("Fast Forward"));
	m_frameForward->setToolTip(tr("Frame Forward"));
	m_mute->setToolTip(tr("Mute"));
	m_windowDivision->setToolTip(tr("Window Division"));
}
void PlayCtrl::hideOrShowPlayList()
{
	if (m_isHidePlayList)
	{
		m_hidePlayList->setStyleSheet("#HidePlayList{background-image:url(" + getPath() + BTN_APPEARLIST_NOR + ")} #HidePlayList:hover {background-image:url(" + getPath() + BTN_APPEARLIST_PRESS + ")}");
		_playlist->hide();
		m_isHidePlayList = false;
		_playView->curPlaySoundItem();
	}else {
		m_hidePlayList->setStyleSheet("#HidePlayList{background-image:url(" + getPath() + BTN_HIDELIST_NOR + ")} #HidePlayList:hover {background-image:url(" + getPath() + BTN_HIDELIST_PRESS + ")}");
		_playlist->show();
		m_isHidePlayList = true;
	}
}
void PlayCtrl::openOrCloseSound()
{
	muteStatusCtrl();
	emit soundCtrl(m_isOpenSound);
}
void PlayCtrl::muteStatusCtrl(){
	if (m_isOpenSound)
	{
		m_mute->setStyleSheet("#Mute{background-image:url(" + getPath() + BTN_MUTE_NOR + ")} #Mute:hover {background-image:url(" + getPath() + BTN_MUTE_PRESS + ")}");
		m_isOpenSound = false;
	}else {
		m_mute->setStyleSheet("#Mute{background-image:url(" + getPath() + BTN_VOLUME_NOR + ")} #Mute:hover {background-image:url(" + getPath() + BTN_VOLUME_PRESS + ")}");
		m_isOpenSound = true;
	}
}
void PlayCtrl::openDir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"./");
	QStringList traverseFileList = _playlist->traverseDir(dir);
	_playlist->createFileNode(traverseFileList);
	traverseFileList.clear();
}
void PlayCtrl::onTimerTimeout()
{
	LayoutItem * curItem = _playView->getCurClickedWnd();
	if (curItem)
	{
		ctrlCurPlayItem(curItem);
	}else {
		curItem = _playView->getFirItem();
		ctrlCurPlayItem(curItem);
	}
}
void PlayCtrl::ctrlCurPlayItem(LayoutItem *curPlayItem)
{
	if(curPlayItem)
	{
		if(curPlayItem->m_isPlay)
		{
			long totalTime = curPlayItem->getCurItemTotalTime();
			long curTime = curPlayItem->getVideoCurPlayTime();

			m_silder->setRange(0,totalTime);
			m_silder->setValue(curTime);

			QString strCurTime = showSliderTime(curTime);
			m_currentTimeLabel->setText(strCurTime);

			QString strTotalTime = showSliderTime(totalTime);
			m_totalTimeLabel->setText(strTotalTime);

			if(curPlayItem->m_isPause)
			{
				m_play->setStyleSheet("#Play{background-image:url(" + getPath() + BTN_PLAY_NOR + ")} #Play:hover {background-image:url(" + getPath() + BTN_PLAY_PRESS + ")}");
			}else{
				m_play->setStyleSheet("#Play{background-image:url(" + getPath() + BTN_STOP_NOR + ")} #Play:hover {background-image:url(" + getPath() + BTN_STOP_PRESS + ")}");
			}
		}else{
			m_silder->setRange(0,0);
			m_silder->setValue(0);

			m_currentTimeLabel->setText(tr("00:00:00"));
			m_totalTimeLabel->setText(tr("00:00:00"));
			m_play->setStyleSheet("#Play{background-image:url(" + getPath() + BTN_PLAY_NOR + ")} #Play:hover {background-image:url(" + getPath() + BTN_PLAY_PRESS + ")}");
		}
	}
}
QString PlayCtrl::showSliderTime(long curTime)
{
		long hour = curTime/3600;
		long minutes = (curTime - hour*3600)/60;
		long second = curTime - hour*3600 - minutes*60;

		QString strHour = hour > 9 ? QString::number(hour) : "0" + QString::number(hour);
		QString strMinutes = minutes > 9 ? QString::number(minutes) : "0" + QString::number(minutes);
		QString strSecond = second > 9 ? QString::number(second) : "0" + QString::number(second);

		QString str = strHour + ":" + strMinutes + ":" + strSecond;

		return str;
}
bool PlayCtrl::eventFilter(QObject *obj, QEvent *event)
{
	if (m_silder == obj)
	{
		QMouseEvent *ev = static_cast<QMouseEvent*>(event);
		int maxVaule = m_silder->maximum();
		int w = m_silder->width();

		if (event->type() == QEvent::MouseButtonPress)
		{
			int pos = (ev->pos().x())*maxVaule/w;
			_playView->setVideoCurPlayTime(pos);
			m_isPressed = true;
		}else if (event->type() == QEvent::MouseButtonRelease)
		{
			m_isPressed = false;
		}else if (event->type() == QEvent::MouseMove)
		{
			if (m_isPressed)
			{
				int pos = (ev->pos().x())*maxVaule/w;
				_playView->setVideoCurPlayTime(pos);
			}
		}
	}
	return QWidget::eventFilter(obj,event);
}
