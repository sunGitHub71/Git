#pragma  once
#ifndef PLAYVIEW_H
#define PLAYVIEW_H

#include <QWidget>
#include <Windows.h>
#include "layoutitem.h"
class VideoName;
class MainLayout;

#define MAX_ROW 10
#define MAX_COLUMN 10
#define MAX_NUM MAX_ROW*MAX_COLUMN

typedef enum _enumHsLayoutType{
	HS_VIEW_LAYOUT1x1,
	HS_VIEW_LAYOUT2x2,
	HS_VIEW_LAYOUT3x3,
	HS_VIEW_LAYOUT4x4,
}HS_VIEW_LAYOUT_TYPE;


class PlayView : public QWidget{
	Q_OBJECT

public:
	PlayView(QWidget *parent = NULL);
	PlayView(QString name, QWidget *parent = NULL);
	~PlayView();
	void setCurVideoName(VideoName *videoName){_videoName = videoName;};
	void setfullVideoName(VideoName *fullViewName){_fullViewName = fullViewName;};

public:
	void setNormalLayout(int rows,int cols);
	void resetVisible(int numToShow);
	void showMaxItem(LayoutItem *item);
	void setCurrentClickItem(LayoutItem *item);
	void setLayoutType(HS_VIEW_LAYOUT_TYPE layoutType);
	int getSelectedWndIndex();
	void getFileName();
	bool curPlayItem(QString fileName,WId hwnd);
	void curStopItem();
	void curStepOneItem();
	void curSnapShotItem(QString SnapShotPath);
	void curPlaySoundItem();
	void curCloseSoundItem();
	void setCurSound(LayoutItem *curSound);
	void setCurPlaySpeed(long Speed);
	void getPlayListPic(QString fileName,QString picPath);
	long getVideoTotalTime();
	long getVideoCurTime();
	void curContinousCaptrueItem(int sec,int picNum,QString path);
	void setVideoCurPlayTime(long playTime);
	void setCurDigitalZoom(bool isDigitalZoom);
	QString showCurVideoName(QString filePath);
	long getCurSpeed();
	bool getDigitalStatus();
	void stopAllVideo();
	void stopCurVideo(QString fileName);
	QString getCurVideoName();
	int getWndNums(){return _numToShow;};
	HWND getFirHwnd(){return firHwnd;};
	HWND getClickedHwnd(){return Hwnd;};
	LayoutItem * getCurClickedWnd(){return _currentItem;};
	LayoutItem * getFirItem(){return _item[0];};
	void updateMainItemLabel();
	bool isVideoPlay(int num);
	void setBtnEnabled(bool isPlay);
	void setSoundIsOpen(bool isOpen){m_isSoundOpen = isOpen;};
	void setCurRect();
	void setIsStopCapture(bool isStopCapture){m_isStopCapture = isStopCapture;};
	bool getIsAnyVideoPlay(){return m_isAnyVideoPlay;};
	void initStatus();

private:
	LayoutItem *_item[MAX_NUM]; 
	LayoutItem *_currentItem; 
	LayoutItem *_maxItem;  
	int _numToShow;  
	int _row;
	int _col;
	HWND Hwnd;
	HWND firHwnd;
	HWND _dropHwnd;
	HS_VIEW_LAYOUT_TYPE _layoutType;
	long videoTotalTime;
	long videoCurTime;
	VideoName *_videoName;
	VideoName *_fullViewName;
	long _curSpeed;
	bool _digitalStatus;
	bool _isPlaying;
	bool m_isSoundOpen;
	bool m_isStopCapture;
	bool m_isAnyVideoPlay;
protected:
	void resizeEvent(QResizeEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

private slots:
	void onItemNewNodeDroped(LayoutItem * theItem);
	void posy(VideoWidget *item,QPoint posy);
	void playThen(LayoutItem *item);
	void stopThen(LayoutItem *thisItem);

signals:
	void dropItemPlay(QString *fileName);
	void curOverPlay();
	void curOpenFileList(QStringList curOpenList);
	void toolBarCurStatus(VideoWidget *item,QPoint pos);
	void toolBarY(int cury);
	void ctrlBtnEnabled(bool isEnabled);
	void captureOver();
	void isAnyVideoPlay(bool videoPlay);
	void overPlay(LayoutItem *curItem);
	void urlPlaySuccess(QString fileName);
	void videoPlayTimeOut();
};

#endif
