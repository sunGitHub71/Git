#pragma  once
#ifndef PLAYCTRL_H
#define PLAYCTRL_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include "basicSetItem.h"
#include <QPropertyAnimation>

class PlayView;
class LayoutItem;
class PlayList;

class PlayCtrl : public QWidget {
	Q_OBJECT

public:
	PlayCtrl(QWidget *parent = NULL);
	~PlayCtrl();
	void setPlayView(PlayView * playview){_playView = playview;}
	void setPlayList(PlayList *playlist){_playlist = playlist;}
	void paintEvent(QPaintEvent *event);
	void muteStatusCtrl();
	void setIsOpenSound(bool isOpenSound){m_isOpenSound = isOpenSound;};
	void keyPressEvent(QKeyEvent *event);
public:
	QWidget *m_playCtrl;
	QWidget *m_silderWidget;
	QSlider *m_silder;
	QLabel *m_currentTimeLabel;
	QLabel *m_totalTimeLabel;

	QWidget *m_leftWidget;
	QPushButton *m_hidePlayList;
	QPushButton *m_showPlayList;
	QPushButton *m_openFileDir;
	QPushButton *m_checkVideo;

	QWidget *m_CenterWidget;
	QPushButton *m_stopPlay;
	QPushButton *m_slowForward;
	QPushButton *m_play;
	QPushButton *m_fastForward;
	QPushButton *m_frameForward;

	QWidget *m_rightWidget;
	QPushButton *m_mute;
	QPushButton *m_closeAudio;
	QSlider *m_muteSlider;
	QPushButton *m_windowDivision;

	QTimer * _timer;
	PlayView * _playView;
	PlayList *_playlist;
	bool m_isPressed;

	bool m_isHidePlayList;
	bool m_isOpenSound;
public:
	QString showSliderTime(long curTime);
	void ctrlCurPlayItem(LayoutItem *curPlayItem);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	void initPlayCtrlUi();
protected slots:
	void onTimerTimeout();
	void hideOrShowPlayList();
	void openOrCloseSound();
	void openDir();
signals:
	void soundCtrl(bool isOpenSound);
	void startPlay();
	void checkVideoSignal();
	void stopPlay();
	void slowForward();
	void fastForward();
	void frameForward();
};
#endif