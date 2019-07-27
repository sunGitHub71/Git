#include "playview.h"
#include "resource_tr.h"
#include "videoname.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>

PlayView::PlayView(QWidget *parent) 
	: QWidget(parent)
{
	setMouseTracking(true);
	LayoutItem *item = NULL;
	for (int i = 0;i < MAX_NUM;++i)
	{
		item = new LayoutItem(this);
		item->index = i;
		item->m_videoWidget->index = i;
	
		item->setHidden(true);

		item->m_mainInterface->setHidden(true);

		connect(item,SIGNAL(newNodeDroped(LayoutItem *)),this,SLOT(onItemNewNodeDroped(LayoutItem *)));
		connect(item,SIGNAL(curList(QStringList )),this,SIGNAL(curOpenFileList(QStringList )));
		connect(item,SIGNAL(toolBarStatus(VideoWidget *,QPoint )),this,SLOT(posy(VideoWidget *,QPoint )));
		connect(item,SIGNAL(captureCompleted()),this,SIGNAL(captureOver()));
		connect(item,SIGNAL(overplay(LayoutItem *)),this,SIGNAL(overPlay(LayoutItem *)));
		connect(item,SIGNAL(startPlayItem(LayoutItem *)),this,SLOT(playThen(LayoutItem *)));
		connect(item,SIGNAL(endPlayItem(LayoutItem *)),this,SLOT(stopThen(LayoutItem *)));
		_item[i] = item;
	}
	
	this->setFocusPolicy(Qt::NoFocus);
	_maxItem = NULL;
	_currentItem = NULL;
	_numToShow = 0;
	Hwnd = NULL;
	firHwnd = NULL;
	videoCurTime = 0;
	videoTotalTime = 0;
	_curSpeed = 0;
	_isPlaying = false;
	_digitalStatus = false;
	m_isSoundOpen = false;
	m_isStopCapture = false;
	m_isAnyVideoPlay = false; 
}

PlayView::PlayView(QString name, QWidget *parent) 
	: QWidget(parent)
{
	setMouseTracking(true);
	LayoutItem *item = NULL;
	for (int i = 0;i < MAX_NUM;++i)
	{
		item = new LayoutItem(this);
		item->setName(name);
		item->index = i;
		item->m_videoWidget->index = i;

		item->setHidden(true);

		item->m_mainInterface->setHidden(true);

		connect(item,SIGNAL(newNodeDroped(LayoutItem *)),this,SLOT(onItemNewNodeDroped(LayoutItem *)));
		connect(item,SIGNAL(curList(QStringList )),this,SIGNAL(curOpenFileList(QStringList )));
		connect(item,SIGNAL(toolBarStatus(VideoWidget *,QPoint )),this,SLOT(posy(VideoWidget *,QPoint )));
		connect(item,SIGNAL(captureCompleted()),this,SIGNAL(captureOver()));
		connect(item,SIGNAL(overplay(LayoutItem *)),this,SIGNAL(overPlay(LayoutItem *)));
		connect(item,SIGNAL(startPlayItem(LayoutItem *)),this,SLOT(playThen(LayoutItem *)));
		connect(item,SIGNAL(endPlayItem(LayoutItem *)),this,SLOT(stopThen(LayoutItem *)));
		_item[i] = item;
	}

	this->setFocusPolicy(Qt::NoFocus);
	_maxItem = NULL;
	_currentItem = NULL;
	_numToShow = 0;
	Hwnd = NULL;
	firHwnd = NULL;
	videoCurTime = 0;
	videoTotalTime = 0;
	_curSpeed = 0;
	_isPlaying = false;
	_digitalStatus = false;
	m_isSoundOpen = false;
	m_isStopCapture = false;
	m_isAnyVideoPlay = false; 
}
PlayView::~PlayView(){

}
void PlayView::onItemNewNodeDroped(LayoutItem * theItem)
{
	if (theItem->isChecked())
	{
		_currentItem = 0;
	}
	setCurrentClickItem(theItem);

	QString _fileName = theItem->getCurVideoPath();
	HWND _dropHwnd = theItem->m_videoWidget->winId();
	
	curStopItem();
	curPlayItem(_fileName,_dropHwnd);
}
void PlayView::posy(VideoWidget *item,QPoint posy){
	int index = item->index;
	int curRow = index/_row;

	int itemy  = posy.y() + curRow*(item->height());

	emit toolBarY(itemy);
}
QString PlayView::getCurVideoName()
{
	QString curFileName = "";
	if (_currentItem)
	{
		curFileName = _currentItem->m_fileName;
	}
	return curFileName;
}
void PlayView::resizeEvent(QResizeEvent *event)
{
	if (_maxItem != NULL)
	{
		_maxItem->setGeometry(0,0,width(),height());
	}else {
		setLayoutType(_layoutType);
	}
}
void PlayView::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		LayoutItem *current = NULL;
		for (int i = 0;i < _numToShow;++i)
		{
			if (_item[i]->geometry().contains(event->pos()))
			{
				current = _item[i];
				break;
			}
		}
		if (current)
		{
			showMaxItem(current);
		}
	}
}
void PlayView::showMaxItem(LayoutItem *item)
{
	if (_numToShow != 1)
	{
		if (item == _maxItem)
		{
			setLayoutType(_layoutType);
			_maxItem = NULL;
		}else {
			for (int i = 0;i < _numToShow;++i)
			{
				_item[i]->setGeometry(0,0,0,0);
			}
			item->show();
			item->setGeometry(0,0,width(),height());
			_maxItem = item;
		}
	}
}
void PlayView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		LayoutItem *current = NULL;
		for (int i = 0;i < _numToShow;++i)
		{
			if (_item[i]->geometry().contains(event->pos()))
			{
				current = _item[i];
				Hwnd = current->m_videoWidget->winId();
				_videoName->showVideoStatus(current->m_fileName);
				_fullViewName->showVideoStatus(current->m_fileName);
				_curSpeed = current->m_curSpeed;
				_digitalStatus = current->m_digitalStatus;
				_isPlaying = current->m_isPlay;
				setBtnEnabled(_isPlaying);
				_videoName->setDigitalBtn(_digitalStatus);
				_fullViewName->setDigitalBtn(_digitalStatus);
				emit ctrlBtnEnabled(_isPlaying);
				break;
			}
		}
		setCurrentClickItem(current);
		setCurSound(current);
	}
	QWidget::mousePressEvent(event);
}
void PlayView::setBtnEnabled(bool isPlay){
	_videoName->m_digitalZoomBtn->setEnabled(isPlay);
	_videoName->m_continuousCaptureBtn->setEnabled(isPlay);
	_videoName->m_captureBtn->setEnabled(isPlay);
	_fullViewName->m_captureBtn->setEnabled(isPlay);
	_fullViewName->m_continuousCaptureBtn->setEnabled(isPlay);
	_fullViewName->m_digitalZoomBtn->setEnabled(isPlay);
	
	if (isPlay)
	{
		_videoName->m_digitalZoomBtn->setStyleSheet("#DigitalZoom {background-image:url(" + getPath() + BTN_EXPAND_NOR + ")} #DigitalZoom:hover {background-image:url(" + getPath() + BTN_EXPAND_PRESS + ")}");
		_videoName->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #ContinuousCapture:hover {background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
		_videoName->m_captureBtn->setStyleSheet("#Capture {background-image:url(" + getPath() + BTN_SNAP_NOR + ")} #Capture:hover {background-image:url("+ getPath() + BTN_SNAP_PRESS + ")}");
		_fullViewName->m_captureBtn->setStyleSheet("#Capture {background-image:url(" + getPath() + BTN_SNAP_NOR + ")} #Capture:hover {background-image:url("+ getPath() + BTN_SNAP_PRESS + ")}");
		_fullViewName->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #ContinuousCapture:hover {background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
		_fullViewName->m_digitalZoomBtn->setStyleSheet("#DigitalZoom {background-image:url(" + getPath() + BTN_EXPAND_NOR + ")} #DigitalZoom:hover {background-image:url(" + getPath() + BTN_EXPAND_PRESS + ")}");
	}else {
		_videoName->m_digitalZoomBtn->setStyleSheet("#DigitalZoom::disabled {background-image:url(" + getPath() + BTN_EXPAND_DIS + ")}");
		_videoName->m_captureBtn->setStyleSheet("#Capture::disabled {background-image:url(" + getPath() + BTN_SNAP_DIS + ")}");
		_videoName->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture::disabled {background-image:url(" + getPath() + BTN_SHOOT_DIS + ")}");
		_fullViewName->m_captureBtn->setStyleSheet("#Capture::disabled {background-image:url(" + getPath() + BTN_SNAP_DIS + ")}");
		_fullViewName->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture::disabled {background-image:url(" + getPath() + BTN_SHOOT_DIS + ")}");
		_fullViewName->m_digitalZoomBtn->setStyleSheet("#DigitalZoom::disabled {background-image:url(" + getPath() + BTN_EXPAND_DIS + ")}");
	}
}
bool PlayView::isVideoPlay(int num){
	if (num > 0)
	{
		for (int i = 0;i < num;++i)
		{
			if (_item[i]->m_isPlay)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}
long PlayView::getCurSpeed()
{
	if (_numToShow == 1)
	{
		return _item[0]->m_curSpeed;
	}
	return _curSpeed;
}
void PlayView::setCurrentClickItem(LayoutItem *current)
{
	if (current)
	{
		if (current != _currentItem)
		{
			if (_currentItem)
			{
				_currentItem->setClicked(false);
			}
				_currentItem = current;
				_currentItem->setClicked(true);	
			}
		}
	}
void PlayView::resetVisible(int numToShow)
{
	_numToShow = numToShow;
	for (int i = 0;i < MAX_NUM;++i)
	{
		if (i < numToShow)
		{
			if (_item[i]->isHidden())
			{
				_item[i]->show();
			}
		}else {
			if (numToShow == 0 || _item[i]->isVisible())
			{
				_item[i]->hide();
			}
		}
	}
}
void PlayView::setNormalLayout(int rows,int cols)
{
	if (rows >= 1 && cols >= 1 && rows*cols <= MAX_NUM)
	{
		int numToShow = rows*cols;
		resetVisible(numToShow);

		_row = rows;
		_col = cols;

		double w = (double)width()/cols;
		double h = (double)height()/rows;

		for (int i = 0;i < numToShow;++i)
		{
			int r = i/cols;
			int c = i%cols;

			_item[i]->setGeometry(w*c,h*r,w,h);
		}
		firHwnd = _item[0]->m_videoWidget->winId();
	}
}
void PlayView::setLayoutType(HS_VIEW_LAYOUT_TYPE layoutType)
{
	_layoutType = layoutType;
	if (_layoutType == HS_VIEW_LAYOUT1x1)
	{
		setNormalLayout(1,1);
		bool isShowMainInterface = _item[0]->m_isPlay;
		_item[0]->m_mainInterface->setHidden(isShowMainInterface);
		setCurrentClickItem(_item[0]);
		_item[0]->setClicked(false);
	}else if(_layoutType == HS_VIEW_LAYOUT2x2){
		setNormalLayout(2,2);
		_item[0]->m_mainInterface->setHidden(true);
	}else if (_layoutType == HS_VIEW_LAYOUT3x3)
	{
		setNormalLayout(3,3);
		_item[0]->m_mainInterface->setHidden(true);
	}else if (_layoutType == HS_VIEW_LAYOUT4x4)
	{
		setNormalLayout(4,4);
		_item[0]->m_mainInterface->setHidden(true);
	}
	//主界面切换其他界面 默认选中第一个窗口
	if (_layoutType != HS_VIEW_LAYOUT1x1)
	{
		if (_currentItem == _item[0])
		{
			_item[0]->setClicked(true);
		}
	}else {
		if (!_item[0]->m_isPlay)
		{
			initStatus();
		}
	}
	//选中窗口索引大于要切换的界面的窗口数 默认选中第一个窗口
	int index = getSelectedWndIndex();
	if (index != -1)
	{
		if (index > _numToShow -1)
		{
			setCurrentClickItem(_item[0]);
		}
	}

	bool isAnyPlay = false;
	for (int i = 0;i < _numToShow;++i)
	{
		if (_item[i]->m_isPlay)
		{
			isAnyPlay = _item[i]->m_isPlay;
			break;
		}
	}

	_videoName->m_fullScreenBtn->setEnabled(isAnyPlay);

	if (isAnyPlay)
	{
		_videoName->m_fullScreenBtn->setStyleSheet("#FullScreen {background-image:url(" + getPath() + BTN_FULLSCREEN_NOR + ")} #FullScreen:hover {background-image:url(" + getPath() + BTN_FULLSCREEN_PRESS + ")}");
	}else {
		_videoName->m_fullScreenBtn->setStyleSheet("#FullScreen::disabled {background-image:url(" + getPath() + BTN_FULLSCREEN_DIS + ")}");
		initStatus();
	}

	setCurSound(_currentItem);
	Hwnd = _currentItem->m_videoWidget->winId();
}
int PlayView::getSelectedWndIndex()
{
	if(_currentItem){
		return _currentItem->index;
	}
	return -1;
}
void PlayView::updateMainItemLabel()
{
	if (_numToShow == 1)
	{
		_item[0]->updateMainLabel();
	}
}
bool PlayView::curPlayItem(QString fileName,WId hwnd)
{
	bool ret = false;
	if (_currentItem)
	{	
		 ret = 	_currentItem->curItemPlay(fileName,hwnd);
		 QFileInfo info(fileName);
		 if(!info.exists())
		 {
			if (ret){
					emit urlPlaySuccess(fileName);
			}else {
					emit videoPlayTimeOut();
				}
	     }
	}
	return ret;
}
void PlayView::playThen(LayoutItem *item)
{
	if (item == _currentItem)
	{
		_item[0]->m_mainInterface->setHidden(true); 

		_videoName->showVideoStatus(item->m_fileName);
		_fullViewName->showVideoStatus(item->m_fileName);

		setCurSound(item);

		setBtnEnabled(true);
		emit ctrlBtnEnabled(true);

		_videoName->m_fullScreenBtn->setEnabled(true);
		_videoName->m_fullScreenBtn->setStyleSheet("#FullScreen {background-image:url(" + getPath() + BTN_FULLSCREEN_NOR + ")} #FullScreen:hover {background-image:url(" + getPath() + BTN_FULLSCREEN_PRESS + ")}");

		emit isAnyVideoPlay(true);

		if (m_isSoundOpen)
		{
			curPlaySoundItem();
		}else {
			curCloseSoundItem();
		}
	}
}
void PlayView::curStopItem()
{
	if (_currentItem)
	{
		_currentItem->curItemStop();
	}
}
void PlayView::initStatus()
{
	_videoName->videoNameInit();
	_fullViewName->videoNameInit();
	_videoName->setDigitalBtn(false);
	_fullViewName->setDigitalBtn(false);
	emit ctrlBtnEnabled(false);
	m_isAnyVideoPlay = isVideoPlay(16);
	emit isAnyVideoPlay(m_isAnyVideoPlay);
	setBtnEnabled(false);
}
void PlayView::stopThen(LayoutItem *thisItem)
{
	if (thisItem == _currentItem)
	{
		thisItem->setDigitalZoom(false);
		initStatus();
	}
}
void PlayView::stopAllVideo()
{
	for (int i = 0;i < _numToShow;++i)
	{
		_item[i]->curItemStop();
	}
}
void PlayView::stopCurVideo(QString fileName)
{
	for (int i = 0;i < 16;++i)
	{
		if(_item[i]->m_fileName == fileName){
			_item[i]->curItemStop();
		}
	}

	m_isAnyVideoPlay = isVideoPlay(16);
	emit isAnyVideoPlay(m_isAnyVideoPlay);
}
void PlayView::curStepOneItem()
{
	if (_currentItem)
	{
		_currentItem->curItemStepOne();
	}
	return;
}
void PlayView::curSnapShotItem(QString SnapShotPath)
{
	if (_currentItem)
	{
		_currentItem->curItemSnapShot(SnapShotPath);
	}
	return;
}
void PlayView::setCurPlaySpeed(long Speed)
{
	if (_currentItem)
	{
		_currentItem->setCurItemSpeed(Speed);
	}
	return;
}
void PlayView::curPlaySoundItem()
{
	int index = 0;
	if (_numToShow == 1)
	{
		if (_item[0]->m_isPlay)
		{
			_item[0]->curItemPlaySound();
		}
	}else {
		index = getSelectedWndIndex();
		if (_item[index]->m_isPlay)
		{
			_item[index]->curItemPlaySound();
		}
	}
	return;
}
void PlayView::curCloseSoundItem()
{
	for (int i = 0;i < _numToShow;++i)
	{
		_item[i]->curItemCloseSound();
	}
	return;
}
void PlayView::setCurSound(LayoutItem *curSound)
{
	if (curSound)
	{
		for (int i = 0;i < 16;++i)
		{
			if (_item[i]->m_isPlay)
			{
				_item[i]->curItemCloseSound();
			}
		}

		if (m_isSoundOpen)
		{
			if (curSound->m_isPlay)
			{
				curSound->curItemPlaySound();
			}
		}
	}
}
void PlayView::getPlayListPic(QString fileName,QString picPath)
{
	LayoutItem::getListPic(fileName,picPath);
}
void PlayView::curContinousCaptrueItem(int sec,int picNum,QString path)
{
	if (_currentItem)
	{
		_currentItem->curItemContinousCapture(sec,picNum,path,m_isStopCapture);
	}
	return;
}
void PlayView::setVideoCurPlayTime(long playTime)
{
	if (_currentItem)
	{
		_currentItem->setCurPlayTime(playTime);
	}
}
long PlayView::getVideoCurTime()
{
	if (_currentItem)
	{
		videoCurTime = _currentItem->getVideoCurPlayTime();
		return videoCurTime;
	}
	return 0;
}
long PlayView::getVideoTotalTime()
{
	if (_currentItem)
	{
		videoTotalTime = _currentItem->getCurItemTotalTime();
		return videoTotalTime;
	}
	return -1;
}
QString PlayView::showCurVideoName(QString filePath)
{
	QString name = "";
	if (_currentItem)
	{
		name =  _currentItem->getCurVideoName(filePath);
	}
	return name;
}
void PlayView::setCurDigitalZoom(bool isDigitalZoom)
{
	if (_currentItem)
	{
		_currentItem->setDigitalZoom(isDigitalZoom);
		_currentItem->m_digitalStatus = isDigitalZoom;
	}
}
bool PlayView::getDigitalStatus()
{
	return _digitalStatus;
}
void PlayView::setCurRect()
{
	if (_currentItem)
	{
		_currentItem->setDisplayRect(1,QPoint(_currentItem->m_videoWidget->width()/2,_currentItem->m_videoWidget->height()/2));
	}
}