#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QWidget>
#include <Windows.h>
#include <QTimer>
#include <QLabel>
#include "videowidget.h"
#include "mainlayout.h"

#define BORDER_WIDTH 1

class PlayListModel;

class LayoutItem : public QWidget{
	Q_OBJECT

public:
	LayoutItem(QWidget *parent = NULL);
	~LayoutItem();

protected:
	virtual void paintEvent(QPaintEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

public:
	bool isChecked(){return _bClicked;};
	void setClicked(bool bClicked);
	void setName(QString name);
	bool curItemPlay(QString fileName,WId hWnd);
	void curItemStop();
	void curItemStepOne();
	void curItemSnapShot(QString capturePath);
	void curItemPlaySound();
	void setCurItemSound();
	void setDigitalZoom(bool isDigltalZoom);
	static void getListPic(QString fileName,QString picName);
	long getCurItemTotalTime();
	long getVideoCurPlayTime();
	void setCurItemSpeed(long Speed);
	void curItemContinousCapture(int sec,int num,QString path,bool isStopCapture);
	void setCurPlayTime(long curTime);
	void drawBorder();
	QColor borderColor();
	QString getCurVideoName(QString filePath);
	QString getCurVideoPath();
	void updateMainLabel(){m_mainInterface->initMainLayoutUi();};
	void curItemCloseSound();

	void setDisplayRect(const QRect & rect);
	void setDisplayRect(double zoomTimes,const QPoint& centerPt);
	void updateDisplayRect();

	QString getName(){return m_videoName;};

public:
	int index;					//����
	long m_curSpeed;			//��ǰ�ٶ�
	bool m_isPlay;				//��ǰ�Ƿ񲥷�
	bool m_isPause;				//��ǰ�Ƿ���ͣ
	bool m_digitalStatus;		//��ǰ�Ƿ�����
	QString m_fileName;			//��ǰ���ŵ��ļ���
	bool m_isStop;				//��ǰ�Ƿ�ֹͣ
	bool m_isOpenSound;			//�Ƿ񲥷�����
	VideoWidget *m_videoWidget;
	MainLayout *m_mainInterface;

private:
	bool _bClicked;
	QColor _selectColor;
	QColor _unSelectColor;
	HANDLE m_localPlayHandle;
	QTimer *timer;
	int m_picNum;
	int m_curPicNum;
	QTimer * _playTimer;
	QTimer *_refreshTimer;
	QTimer *_showInfoTimer;
	long m_totalTime;
	long m_curPlayTime;
	QString capPath;
	bool m_isChecked;
	QString m_curVideoPath;
	int m_infoShowTime;
	bool m_isShowInfo; 
	
	double _zoomTimes;
	double _xRatio;
	double _yRatio;
	QRect _playRect;

	long m_curTime;
	QString m_videoName;
private slots:
	void startCapture();
	void onPlayTimerTimerout();
	void curItemrefresh();
	void startDigitalZoom();
	void hideInfo();

signals:
	void newNodeDroped(LayoutItem *theItem);
	void curList(QStringList curOpenList);
	void toolBarStatus(VideoWidget *item,QPoint pos);
	void captureCompleted();
	void overplay(LayoutItem *curItem);
	void startPlayItem(LayoutItem *item);
	void endPlayItem(LayoutItem *thisItem);
};
#endif