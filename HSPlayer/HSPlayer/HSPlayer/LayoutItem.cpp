#include "layoutitem.h"
#include "tchar.h"
#include <Windows.h>
#include "AVPlayerDef.h"
#include "HSAVPlayer.h"
#include "playlistmodel.h"
#include <QPainter>
#include <QDateTime>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QFileInfo>
#include <QVBoxLayout>

void __stdcall hsDrawCallback( HANDLE hHandle, HDC hDC, void *lpContext )
{
	if (!hDC || !lpContext){
		return;
	}

	VideoWidget *Wnd = (VideoWidget *)lpContext;
	HDC dc = (HDC)hDC;
	HPEN hPen,oldPen;
	
	QString captureInf = Wnd->getShowInfo();
	QByteArray ba = captureInf.toLocal8Bit();
	char *str = ba.data();

	bool isShow = Wnd->getIsShowInfo();
	if (isShow)
	{
		if (NULL != str)
		{
			RECT textRect;
			textRect.left = 10;
			textRect.top = 10;
			textRect.right = Wnd->width();
			textRect.bottom = 40;

			::SetTextColor(dc,RGB(213,205,0));
			::SetBkColor(dc,RGB(255,255,0));
			::SetBkMode(dc,TRANSPARENT);
			::DrawTextA(dc,_T(str),-1,&textRect,DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL);
		}
	}
	
	QRect *pRect = Wnd->selectedWndRect();
	bool _isDraw = Wnd->getDraw();
	int dir = Wnd->getDrawDir();

	if(_isDraw){
	if (pRect)
	{
		hPen = ::CreatePen(PS_SOLID,2,RGB(213,205,0));
		oldPen = (HPEN) ::SelectObject(dc,hPen);

		::MoveToEx(dc,pRect->left(),pRect->top(),NULL);
		if (dir == RIGHT_BOTTOM)
		{
			::LineTo(dc,pRect->right(),pRect->top());
			::LineTo(dc,pRect->right(),pRect->bottom());
			::LineTo(dc,pRect->left(),pRect->bottom());
		}else if (dir == RIGHT_TOP)
		{
			::LineTo(dc,pRect->right(),pRect->top());
			::LineTo(dc,pRect->right(),pRect->bottom() - pRect->height()*2);
			::LineTo(dc,pRect->left(),pRect->bottom() - pRect->height()*2);
		}else if (dir == LEFT_TOP)
		{
			::LineTo(dc,pRect->left(),pRect->bottom() - pRect->height()*2);
			::LineTo(dc,pRect->left()-pRect->width(),pRect->top() - pRect->height());
			::LineTo(dc,pRect->left() - pRect->width(),pRect->top());
		}else if (dir == LEFT_BOTTOM)
		{
			::LineTo(dc,pRect->left() - pRect->width(),pRect->top());
			::LineTo(dc,pRect->left() - pRect->width(),pRect->top() + pRect->height());
			::LineTo(dc,pRect->left(),pRect->top() + pRect->height());
		}
		::LineTo(dc,pRect->left(),pRect->top());

		::SelectObject(dc,oldPen);
		::DeleteObject(hPen);
		}
	}
}

LayoutItem::LayoutItem(QWidget *parent)
	:QWidget(parent)
	,_bClicked(false)
	,index(-1)
	,_selectColor(QColor(230,192,19))
	,_unSelectColor(QColor(0,25,30))
	,m_localPlayHandle(NULL)
	,m_isPlay(false)
	,m_isStop(true)
	,m_isPause(false)
	,m_fileName("")
	,m_digitalStatus(false)
	,m_picNum(0)
	,m_curPicNum(0)
	,m_curSpeed(0)
	,m_isOpenSound(false)
	,m_infoShowTime(0)
	,_zoomTimes(1.0)
{
	this->setObjectName("LayoutItem");
	m_videoWidget = new VideoWidget(this);

	m_mainInterface = new MainLayout;

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setContentsMargins(0,0,0,0);
	vl1->setSpacing(0);
	vl1->addWidget(m_mainInterface);
	m_videoWidget->setLayout(vl1);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(1,1,1,1);
	vl->setSpacing(0);
	vl->addWidget(m_videoWidget);
	setLayout(vl);

	m_totalTime = 0;

	_playTimer = new QTimer(this);
	connect(_playTimer,SIGNAL(timeout()),this,SLOT(onPlayTimerTimerout()));
	
	_refreshTimer = new QTimer(this);
	connect(_refreshTimer,SIGNAL(timeout()),this,SLOT(curItemrefresh()));
	_refreshTimer->start(50);

	_showInfoTimer = new QTimer(this);
	connect(_showInfoTimer,SIGNAL(timeout()),this,SLOT(hideInfo()));
	
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(startCapture()));

	setAcceptDrops(true);

	HS_Initial();
	HS_Free();

	connect(m_videoWidget,SIGNAL(drawEnd()),this,SLOT(startDigitalZoom()));
	connect(m_mainInterface,SIGNAL(curOpenList(QStringList )),this,SIGNAL(curList(QStringList )));
	connect(m_videoWidget,SIGNAL(toolBarShow(VideoWidget *,QPoint )),this,SIGNAL(toolBarStatus(VideoWidget *,QPoint )));
}

LayoutItem::~LayoutItem(){

}
void LayoutItem::setClicked(bool bClicked)
{
	_bClicked = bClicked;

	int w = width();
	int h = height();

	update(0,0,BORDER_WIDTH,h);
	update(0,0,w,BORDER_WIDTH);
	update(w-BORDER_WIDTH,0,BORDER_WIDTH,h);
	update(0,h-BORDER_WIDTH,w,BORDER_WIDTH);
}

void LayoutItem::setName(QString name)
{
	m_mainInterface->setName(name);
}

void LayoutItem::drawBorder(){
	QPainter painter(this);

	QColor color = borderColor();

	int w = width();
	int h = height();

	painter.setPen(QPen(color,BORDER_WIDTH));
	QPainterPath path;
	path.moveTo(0,0);
	path.lineTo(w-BORDER_WIDTH,0);
	path.lineTo(w-BORDER_WIDTH,h-BORDER_WIDTH);
	path.lineTo(0,h-BORDER_WIDTH);
	path.lineTo(0,0);

	painter.drawPath(path);
	painter.restore();
}
QColor LayoutItem::borderColor()
{
	if (_bClicked)
	{
		return _selectColor;
	}else{
		return _unSelectColor;
	}
}
void LayoutItem::paintEvent(QPaintEvent *event)
{
		drawBorder();
}
void LayoutItem::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("pointer/MyModelItem"))
	{
		QByteArray data = event->mimeData()->data("pointer/MyModelItem");
		MyModelItem* dropNode = (MyModelItem*)data.toInt();

		if(dropNode)
		{
			event->acceptProposedAction();
		}
	}
	return QWidget::dragEnterEvent(event);
}
void LayoutItem::dropEvent(QDropEvent *event)
{
	const QMimeData *mimedata = event->mimeData();
	if(mimedata)
	{
		QByteArray data = mimedata->data("pointer/MyModelItem");
		MyModelItem* dropNode = (MyModelItem*)data.toInt();
		if (dropNode)
		{
			m_curVideoPath = dropNode->filePath;
		}
		emit newNodeDroped(this);
	}
	return QWidget::dropEvent(event);
}
QString LayoutItem::getCurVideoPath()
{
	return m_curVideoPath;
}
bool LayoutItem::curItemPlay(QString fileName,WId hWnd)
{
	if (m_isPlay) 
	{
		m_isPause = !m_isPause;
		HS_Pause(m_localPlayHandle,m_isPause);
	}else{
		if (m_localPlayHandle == NULL){
			QByteArray ba = fileName.toLocal8Bit();
			char *msg = ba.data();
			int openRet = HS_OpenRecFile(msg,&m_localPlayHandle);
			if (openRet != -1)
			{
				HS_SetDrawCallBack(m_localPlayHandle,hsDrawCallback,m_videoWidget);
			}
			int ret = HS_Play(m_localPlayHandle,hWnd);
			if(ret != -1){
				m_isPlay = true;
				m_isStop = false;
				m_fileName = fileName;
				m_videoName = fileName;
				emit startPlayItem(this);
			}else {
				return false;
			}
			_playTimer->start(1000);
		}
	}
	return true;
}
long LayoutItem::getCurItemTotalTime()
{
	long totalTime = -1;
	if (m_localPlayHandle != NULL)
	{
		HS_GetFileTotalTime(m_localPlayHandle,&totalTime);
	}
	m_totalTime = totalTime;
	return m_totalTime;
}
long LayoutItem::getVideoCurPlayTime()
{
	long curPlayTime = 0;
	if (m_localPlayHandle != NULL)
	{
		HS_GetPlayTime(m_localPlayHandle,&curPlayTime);
	}
	m_curPlayTime = curPlayTime;
	return m_curPlayTime;
}
void LayoutItem::curItemrefresh()
{
	if( m_localPlayHandle != NULL)
	{
		HS_Refresh(m_localPlayHandle);
	}
}
void LayoutItem::curItemStop()
{
	if (m_localPlayHandle != NULL)
	{
		HS_Stop(m_localPlayHandle);
		HS_CloseRecFile(m_localPlayHandle);
		m_localPlayHandle = NULL;
		m_isPlay = false;
		m_isPause = false;
		m_isStop = true;
		m_curSpeed = 0;
		m_digitalStatus = false;
		m_fileName = "";
		_playTimer->stop();
		emit endPlayItem(this);
	}
}
void LayoutItem::curItemStepOne()
{
	if (m_localPlayHandle != NULL)
	{
		HS_OneByOne(m_localPlayHandle);
		m_isPause = true;
	}
}
void LayoutItem::curItemSnapShot(QString capturePath)
{
	QDate cdate;
	cdate = QDate::currentDate();
	QString dateStr = cdate.toString(Qt::LocalDate);

	QTime ctime;
	ctime = QTime::currentTime();
	QString mescStr = ctime.toString("hh:mm:ss.zzz");

	QString fileName = dateStr + "_" +  mescStr;
	fileName.replace(":","");
	fileName.replace("/","");
	fileName.replace(".","");
	capturePath.replace('\\',"//");

	if (m_localPlayHandle != NULL)
	{
		QString temp = capturePath + "/" + fileName + ".jpg";
		QByteArray tempCapPath = temp.toLocal8Bit();
		char *finalCapPath = tempCapPath.data();
		HS_Snapshot(m_localPlayHandle,finalCapPath,0);
	}
	
	QString infoStr = tr("Capture Completed: ") + capturePath + "/" + fileName + ".jpg";
	m_videoWidget->setShowInfo(infoStr);

	if (m_infoShowTime > 0)
	{
		m_infoShowTime = 0;
	}else {
		_showInfoTimer->start(1000);
		m_videoWidget->setIsShowInfo(true);
	}
}
void LayoutItem::hideInfo()
{
	m_infoShowTime++;
	if (m_infoShowTime >= 3)
	{
		m_infoShowTime = 0;
		m_videoWidget->setIsShowInfo(false);
		_showInfoTimer->stop();
		emit captureCompleted();
	}
}
void LayoutItem::setCurItemSpeed(long Speed)
{
	if (m_localPlayHandle != NULL)
	{
		HS_SetSpeed(m_localPlayHandle,Speed);
		m_curSpeed = Speed;
		
		QString speedValue = "";
		switch(Speed){
		case 1:
			speedValue = "2";
			break;
		case 2:
			speedValue = "4";
			break;
		case 3:
			speedValue = "8";
			break;
		case 0:
			speedValue = "Play";
			break;
		case -1:
			speedValue = "1/2";
			break;
		case -2:
			speedValue = "1/4";
			break;
		case -3:
			speedValue = "1/8";
			break;
		default:
		break;
		}
		QString curSpeedInfo = "" ;
		if (Speed == 0)
		{
			curSpeedInfo = tr("Play");
		}else {
			curSpeedInfo = tr("speed * ") + speedValue;
		}
		m_videoWidget->setShowInfo(curSpeedInfo);

		if (m_infoShowTime > 0)
		{
			m_infoShowTime = 0;
		}else {
			_showInfoTimer->start(1000);
			m_videoWidget->setIsShowInfo(true);
		}
	}
}
void LayoutItem::curItemPlaySound()
{
	if (m_localPlayHandle != NULL)
	{
		int ret = HS_OpenSound(m_localPlayHandle);
		if(ret != -1)
		{
			m_isOpenSound = true;
		}
	}
}
void LayoutItem::curItemCloseSound()
{
	if (m_localPlayHandle != NULL)
	{
		if (m_isOpenSound)
		{
			int ret = HS_CloseSound(m_localPlayHandle);
			if (ret != -1)
			{
				m_isOpenSound = !m_isOpenSound;
			}
		}
	}
}
void LayoutItem::setCurItemSound()
{
	if (m_localPlayHandle != NULL)
	{
		HS_SetVolume(m_localPlayHandle,255);
	}
}
void LayoutItem::getListPic(QString fileName,QString picName)
{
	if (!fileName.isEmpty() && !picName.isEmpty())
	{
		HS_SnapshotFromFile(fileName.toUtf8().data(),picName.toUtf8().data(),0,0,40);
	}
}
void LayoutItem::curItemContinousCapture(int sec,int num,QString path,bool isStopCapture)
{
	capPath = path;
	m_picNum = num;

	if(sec < 1)	sec = 1;
	if(m_localPlayHandle != NULL)
	{
		if (isStopCapture)
		{
			timer->start(sec*1000);
		}else {
			timer->stop();
			m_curPicNum = 0;
			QString captureOver = tr("ContinousCapture Completed");
			m_videoWidget->setShowInfo(captureOver);
		}	
	}
}
void LayoutItem::startCapture()
{
	curItemSnapShot(capPath);
	m_curPicNum++;

	if (m_curPicNum == m_picNum)
	{
		timer->stop();
		m_curPicNum = 0;
		QString captureOver = tr("ContinousCapture Completed");
		m_videoWidget->setShowInfo(captureOver);
	}
}
void LayoutItem::onPlayTimerTimerout()
{
	long playTime = -1;
	long totalTime = 0;

	if (m_localPlayHandle != NULL)
	{
		HS_GetPlayTime(m_localPlayHandle,&playTime);
		HS_GetFileTotalTime(m_localPlayHandle,&totalTime);
	}

	if (totalTime != 0)
	{
		if(playTime == totalTime) 
		{
			curItemStop();
			emit overplay(this);
		}
	}
}
void LayoutItem::setCurPlayTime(long curTime)
{
	if (m_localPlayHandle != NULL)
	{
		HS_SetPlayTime(m_localPlayHandle,curTime);
	}
}
QString LayoutItem::getCurVideoName(QString filePath)
{
	QFileInfo *info = new QFileInfo(filePath);
	QString curVideoName = info->fileName();

	if (filePath == "")
	{
		return "Video Name";
	}
	return curVideoName;
}
void LayoutItem::setDigitalZoom(bool isDigltalZoom)
{
	m_videoWidget->setDraw(isDigltalZoom);
	if (!m_videoWidget->getDraw())
	{
		HS_ShowRect(m_localPlayHandle,0);
		m_digitalStatus = isDigltalZoom;
	}
}
void LayoutItem::startDigitalZoom()
{
	if (m_videoWidget->getDraw())
	{
		if (m_localPlayHandle != NULL)
		{
			QRect curRect = m_videoWidget->getCurSelectedRect();
			if (curRect.width() >= 5)
			{
				setDisplayRect(curRect);
			}
		}
	}
}
void LayoutItem::setDisplayRect(const QRect & rect){
	double zoomTimes;
	if (rect.width() >= rect.height())
	{
		zoomTimes = (double)m_videoWidget->width()/rect.width();
	}else
	{
		zoomTimes = (double)m_videoWidget->height()/rect.height();
	}

	if (zoomTimes >= 1)
	{
		if (zoomTimes >= 10)
		{
			zoomTimes = 10;
		}

		int cx = rect.center().x()/_zoomTimes;
		int cy = rect.center().y()/_zoomTimes;

		QPoint temp ;
		temp.setX(_playRect.x() + cx);
		temp.setY(_playRect.y() + cy);

		zoomTimes *= _zoomTimes;

		setDisplayRect(zoomTimes,temp);
	}
}
void LayoutItem::setDisplayRect(double zoomTimes,const QPoint& centerPt){
	if(zoomTimes < 1)
		zoomTimes = 1;
	else if(zoomTimes > 10)
		zoomTimes = 10;	

	if(_zoomTimes == 10 && zoomTimes == 10)
		return;

	_zoomTimes = zoomTimes;

	int w = m_videoWidget->width()/_zoomTimes;
	int h = m_videoWidget->height()/_zoomTimes;

	int x = centerPt.x() - w/2;
	int y = centerPt.y() - h/2;

	if(x < 0)
		x = 0;
	if(y < 0)
		y = 0;
	if(x + w > m_videoWidget->width())
	{
		x = m_videoWidget->width() - w;
	}
	if(y + h > m_videoWidget->height())
	{
		y = m_videoWidget->height() - h;
	}

	_playRect = QRect(x,y,w,h);
	updateDisplayRect();
}
void LayoutItem::updateDisplayRect(){
	_xRatio = (double)_playRect.x()/m_videoWidget->width();
	_yRatio = (double)_playRect.y()/m_videoWidget->height();

	if(m_localPlayHandle != NULL)
	{
		if(_zoomTimes == 1)
		{
			HS_ShowRect(m_localPlayHandle,0);
		}
		else
		{
			long videoWidth,videoHeight;
			HS_GetPictureSize(m_localPlayHandle,&videoWidth,&videoHeight);

			RECT hsr;
			hsr.left	= videoWidth * _xRatio;
			hsr.top		= videoHeight * _yRatio;
			hsr.right	= hsr.left + videoWidth/_zoomTimes;
			hsr.bottom	= hsr.top + videoHeight/_zoomTimes;

			HS_ShowRect(m_localPlayHandle,&hsr);
		}	
	}
}