#ifndef HSPLAYER_H
#define HSPLAYER_H

#include <QtGui/QWidget>
#include "ui_hsplayer.h"
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QTranslator>
#include <titlebar.h>
#include "playlist.h"
#include "videoname.h"
#include "playctrl.h"
#include "popup.h"
#include "playview.h"
#include "basicsetbox.h"
#include "stretchwnd.h"
#include "CheckVideoWidget.h"

enum PlayMode {
	SINGLE = 0,
	ORDER,
	REPEATONE,
	REPEATALL
};

class HSPlayer : public QWidget
{
	Q_OBJECT

public:
	HSPlayer(QWidget *parent = 0);
	~HSPlayer();

private:
	Ui::HSPlayerClass ui;

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	void closeEvent(QCloseEvent *event);
public:
	void mainLayoutChange();
	void initMainLayout();
	void iniWrite(bool isIniWrite);
	void iniRead();
	void updateUi();
	void getPlayVideoPic(QString fileFullPath,QString picPath);
	void basicSetInit();
	void iniVersion();
	bool curWndIndexChange(int curIndex);

	void startPlay(QString fileName);
	void iniLanguage();
	void fastFrame(bool isWndChange);
	void slowFrame(bool isWndChange);
	void setAutoHide(bool bHide);

	void muteBtnStatusWhenFullscreen(bool isOpenSound,PlayCtrl *ctrlWidget);
	void continousCaptureBtnStatus(bool isStopCapture,VideoName *videoWidget);
	void setNeverOrAlwaysOnTop();
	void initVideo();
	void restoreFromFullScreen();

private slots:
	void playControl();
	void videoCheckCtr();
	void muteCtrl(bool isOpenSound);
	void popup();
	void getCurrentIndex();
	void openFile(QStringList theList);
	void stop();
	void snapShot();
	void fullScreen();
	void stepByOne();
	void setFastSpeed();
	void setSlowSpeed();
	void rightBtn();
	void continousCapture(bool isContinousCapture);
	void basicSet();
	void doubleClickedAutoPlay(const QModelIndex &);
	void DigitalZoom();
	void stopCurPlay();
	void stopAllPlay();
	void fullScreenCtrl(int pos);
	void setCtrlBtnEnabled(bool isCtrlBtnEnabled);
	void captureOverNext();
	void setStickOnTop(bool isAnyVideoPlay);
	void singleMode();
	void orderMode();
	void repeatOneMode();
	void repeatAllMode();
	void setCurPlayMode(int videoIndex);
	void changePlayMode(LayoutItem *theItem);
	void test(QString path);
	void urlVideoPic(QString fileName);
	void onVideoPlayTimeOut();
	void curSelectedLan(QString lanCode,int index);
signals:
	void stickChange(bool isChange);
	void playMode(int index);
private:
	//CheckVideoWidget *checkWidget;
	QStackedWidget *m_mainLayout;
	PopupWindow *popupWindow;
	BasicSetBox *basicSetBox;
	QPushButton *m_openFile;
	QWidget *m_rightWidget;
	QColor m_titleBarColor;
	QLabel *m_mainLabel;
	QWidget *m_center;

	VideoName *videoName;
	TitleBar *m_titleBar;
	TitleBar *pTitleBar;
	PlayView *playView;
	PlayList *playlist;
	PlayCtrl *playCtrl;

	QStringList openFileList;
	bool m_isFullScreen;
	bool m_isMainLayout;
	long playSpeed;
	int curIndex;
	int m_index;

	QPushButton *m_languageChange;
	QStringList lastSeaResult;
	QStringList searchResult;
	QString m_CaptureMode;
	int m_captuteInterval;
	QString m_capturePath;
	QString m_picFormat;
	int m_picMaxNums;

	QTranslator *translator;
	QStringList drapList;
	bool m_isChinese;
	QTimer *_timer;

	bool m_isStickOnTopWhenPlay;
	bool m_isLocateByTimestamp;
	bool m_isAlwaysStickOnTop;
	bool m_isNeverStickOnTop;
	bool m_isLocateByFrame;
	bool m_isKeywordChange;
	bool m_isFastBtnChange;
	bool m_isSlowBtnChange;
	bool m_isSaveFileList;
	bool m_isDigitalZoom;
	int m_curWndIndex;

	StretchWnd *m_stretchWnd;
	bool m_isCurOpenSound;
	QString m_curLanguage;
	int m_setPageIndex;

	VideoName *m_fullWidget;
	PlayCtrl *m_fullPlayCtrl;

	QPropertyAnimation *_animationVideoName;
	QParallelAnimationGroup *_group;
	QPropertyAnimation *_animation;
	bool m_isToolBarHide;
	bool m_isStopCapture;

	QStringList m_allFileList;
	PlayMode m_playmode;
	LayoutItem *m_playItem;
	QString m_videoName;
	HWND m_hWnd;
	int m_curVideoIndex;
};

#endif // HSPLAYER_H
