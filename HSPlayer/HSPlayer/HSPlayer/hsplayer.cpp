#include "hsplayer.h"
#include "LogUtility.h"
#include "titlebar.h"
#include "resource_tr.h"
#include "basicSetItem.h"
#include "customizemsgbox.h"
#include <QUrl>
#include <QDebug>
#include <QApplication>
#include <QDateTime>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>

CAPTURE_SET_ITEM globalCaptureSetItem;
BASIC_SET_ITEM globalBasicSetItem;
HOTKEY_SET_ITEM globalHotkeySetItem;

HSPlayer::HSPlayer(QWidget *parent)
	: QWidget(parent)
	,m_titleBarColor(QColor(45,45,45))
	,m_index(0)
	,m_isFullScreen(false)
	,curIndex(-1)
	,playSpeed(0)
	,m_isChinese(true)
	,translator(NULL)
	,m_curWndIndex(-1)
	,m_isFastBtnChange(false)
	,m_isSlowBtnChange(false)
	,m_isDigitalZoom(false)
	,m_isSaveFileList(true)
	,m_curLanguage("")
	,m_setPageIndex(0)
	,m_isCurOpenSound(false)
	,m_isToolBarHide(true)
	,m_isStopCapture(false)
	,m_playmode(SINGLE)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);
	setWindowIcon(QIcon(getPath() + APP_ICO));
	pTitleBar = new TitleBar(this);
	installEventFilter(pTitleBar);

	setMinimumSize(920,646);
	setAcceptDrops(true);

	QPalette pal(palette());
	pal.setColor(QPalette::Background,m_titleBarColor);
	setAutoFillBackground(true);
	setPalette(pal);

	playlist = new PlayList;
	pTitleBar->setPlayList(playlist);
	videoName = new VideoName;
	playCtrl = new PlayCtrl;
	translator = new QTranslator;

	m_mainLayout = new QStackedWidget;
	m_mainLayout->setFocusPolicy(Qt::NoFocus);
	m_mainLayout->setObjectName("MainLayout");
	m_mainLayout->setStyleSheet("#MainLayout{background-color:#000000;}");

	m_rightWidget = new QWidget;
	
	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(videoName);
	vl->addWidget(m_mainLayout);
	vl->addWidget(playCtrl);
	m_rightWidget->setLayout(vl);

	m_stretchWnd = new StretchWnd;
	QVBoxLayout *vl2 = new QVBoxLayout;
	vl2->setContentsMargins(0,0,0,0);
	vl2->setSpacing(0);
	vl2->addWidget(m_rightWidget);
	vl2->addWidget(m_stretchWnd);

	QString path = getPath() + CONFIG_INI;
	QString versionName = playlist->readName(path);
	playView = new PlayView(versionName);
	m_fullWidget = new VideoName(playView);
	m_fullWidget->setGeometry(0,0,0,0);
	m_fullWidget->m_fullScreenBtn->setShortcut(QString("Esc"));
	m_fullPlayCtrl = new PlayCtrl(playView);
	m_fullPlayCtrl->setGeometry(0,0,0,0);
	playView->setfullVideoName(m_fullWidget);
	_animation = new QPropertyAnimation(m_fullPlayCtrl, "geometry",playView);
	_animationVideoName = new QPropertyAnimation(m_fullWidget,"geometry",playView);
	_group = new QParallelAnimationGroup(this);
	
	playCtrl->setPlayView(playView);
	m_fullPlayCtrl->setPlayView(playView);
	m_fullPlayCtrl->setPlayList(playlist);
	playCtrl->setPlayList(playlist);
	playView->setCurVideoName(videoName);
	m_mainLayout->addWidget(playView);

	initMainLayout();

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,0,0,0);
	hl->setSpacing(0);
	hl->addWidget(playlist);
	hl->addLayout(vl2);

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setSpacing(0);
	vl1->setContentsMargins(0,0,0,0);
	vl1->addWidget(pTitleBar);
	vl1->addLayout(hl);
	setLayout(vl1);

	iniRead();
	iniLanguage();
	basicSetInit();
	iniVersion();
	m_playItem = NULL;
	m_hWnd = NULL;
	m_curVideoIndex = -1;

	connect(playCtrl,SIGNAL(startPlay()),this,SLOT(playControl()));
	connect(m_fullPlayCtrl,SIGNAL(startPlay()),this,SLOT(playControl()));
	connect(playCtrl, SIGNAL(checkVideoSignal()), this, SLOT(videoCheckCtr()));
	connect(playCtrl,SIGNAL(soundCtrl(bool )),this,SLOT(muteCtrl(bool )));
	connect(m_fullPlayCtrl,SIGNAL(soundCtrl(bool )),this,SLOT(muteCtrl(bool )));
	connect(playCtrl->m_windowDivision,SIGNAL(clicked()),this,SLOT(popup()));
	connect(m_fullPlayCtrl->m_windowDivision,SIGNAL(clicked()),this,SLOT(popup()));
	connect(playCtrl,SIGNAL(stopPlay()),this,SLOT(stop()));
	connect(m_fullPlayCtrl,SIGNAL(stopPlay()),this,SLOT(stop()));
	connect(videoName->m_captureBtn,SIGNAL(clicked()),this,SLOT(snapShot()));
	connect(m_fullWidget->m_captureBtn,SIGNAL(clicked()),this,SLOT(snapShot()));
	connect(videoName,SIGNAL(fullScreen()),this,SLOT(fullScreen()));
	connect(m_fullWidget,SIGNAL(fullScreen()),this,SLOT(fullScreen()));
	connect(videoName->m_digitalZoomBtn,SIGNAL(clicked()),this,SLOT(DigitalZoom()));
	connect(m_fullWidget->m_digitalZoomBtn,SIGNAL(clicked()),this,SLOT(DigitalZoom()));
	connect(playCtrl,SIGNAL(frameForward()),this,SLOT(stepByOne()));
	connect(m_fullPlayCtrl,SIGNAL(frameForward()),this,SLOT(stepByOne()));
	connect(playCtrl,SIGNAL(fastForward()),this,SLOT(setFastSpeed()));
	connect(m_fullPlayCtrl,SIGNAL(fastForward()),this,SLOT(setFastSpeed()));
	connect(playCtrl,SIGNAL(slowForward()),this,SLOT(setSlowSpeed()));
	connect(m_fullPlayCtrl,SIGNAL(slowForward()),this,SLOT(setSlowSpeed()));
	connect(videoName,SIGNAL(continousCapture(bool )),this,SLOT(continousCapture(bool )));
	connect(m_fullWidget,SIGNAL(continousCapture(bool )),this,SLOT(continousCapture(bool )));
	connect(pTitleBar->m_settings,SIGNAL(triggered()),this,SLOT(basicSet()));
	connect(playlist,SIGNAL(deleteCurOver()),this,SLOT(stopCurPlay()));
	connect(playlist,SIGNAL(deleteAllOver()),this,SLOT(stopAllPlay()));
	connect(playlist,SIGNAL(rightPlay()),this,SLOT(rightBtn()));
	connect(playlist,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClickedAutoPlay(const QModelIndex &)));
	connect(playView,SIGNAL(curOpenFileList(QStringList )),this,SLOT(openFile(QStringList)));
	connect(playView,SIGNAL(toolBarY(int )),this,SLOT(fullScreenCtrl(int )));
	connect(playView,SIGNAL(ctrlBtnEnabled(bool )),this,SLOT(setCtrlBtnEnabled(bool )));
	connect(playView,SIGNAL(captureOver()),this,SLOT(captureOverNext()));
	connect(playView,SIGNAL(isAnyVideoPlay(bool )),this,SLOT(setStickOnTop(bool )));
	connect(this,SIGNAL(stickChange(bool )),this,SLOT(setStickOnTop(bool )));
	connect(playlist,SIGNAL(singlePlay()),this,SLOT(singleMode()));
	connect(playlist,SIGNAL(orderPlay()),this,SLOT(orderMode()));
	connect(playlist,SIGNAL(repeatOnePlay()),this,SLOT(repeatOneMode()));
	connect(playlist,SIGNAL(repeatAllPlay()),this,SLOT(repeatAllMode()));
	connect(this,SIGNAL(playMode(int )),this,SLOT(setCurPlayMode(int )));
	connect(playView,SIGNAL(overPlay(LayoutItem *)),this,SLOT(changePlayMode(LayoutItem *)));
	connect(pTitleBar,SIGNAL(UrlPath(QString )),this,SLOT(test(QString )));
	connect(playView,SIGNAL(urlPlaySuccess(QString )),this,SLOT(urlVideoPic(QString )));
	connect(playView,SIGNAL(videoPlayTimeOut()),this,SLOT(onVideoPlayTimeOut()));
	connect(pTitleBar,SIGNAL(curlanCode(QString ,int )),this,SLOT(curSelectedLan(QString ,int )));
	
}
HSPlayer::~HSPlayer()
{

}

void HSPlayer::curSelectedLan(QString lanCode,int index){
	QString exePath = getPath() + "/translation/player/";  
	QString QmName;  
	QTranslator Translator; 

	QmName = "hsplayer_" + lanCode + ".qm";
	
	m_curLanguage = lanCode;

	if (translator->load(QmName,exePath)){
		qApp->installTranslator(translator);
	}
	playlist->getCurLanguage(lanCode);
	updateUi();
}
void HSPlayer::test(QString path){
	QStringList temp;
	temp.append(path);

	stop();
	bool ret = false;
	int nums = playView->getWndNums();
	if(nums == 1)
	{
		HWND firItemHwnd = playView->getFirHwnd();
		ret = playView->curPlayItem(path,firItemHwnd);
	}else {
		HWND curClickHwnd = playView->getClickedHwnd();
		if (curClickHwnd == NULL)
		{
			curClickHwnd = playView->getFirHwnd();
		}
		ret = playView->curPlayItem(path,curClickHwnd);
	}

	if (ret)
	{
		QStringList str1 = path.split("@");
		QStringList str2 = str1.at(1).split("/");
		QString strIp = str2.at(0);
		getPlayVideoPic(path.toUtf8().data(),getPath() + "/Skin/player/PlayListPic/" + strIp + ".jpg");
		videoName->showVideoStatus(path);
		playlist->createFileNode(temp);
	}
}
void HSPlayer::onVideoPlayTimeOut(){
	//5秒后没有播放 弹出提示会话失败
	CustomizeMsgBox::showMyMessageBox(this,tr("Hint"),tr("opening conversation failed."),BUTTON_OK_AND_CANCEL,true);
}
void HSPlayer::initMainLayout()
{
	playView->setLayoutType(HS_VIEW_LAYOUT1x1);
	m_mainLayout->setCurrentWidget(playView);
}
void HSPlayer::basicSet()
{
	BasicSetBox *setPage = new BasicSetBox(this,m_setPageIndex);
	int result = setPage->showMyMessageBox(this,tr("Setting"),BUTTON_OK_CANCEL,true);
	m_setPageIndex = setPage->getCurIndex();
	if (result == ID_OK_BTN)
	{
		m_captuteInterval = globalCaptureSetItem.interval;
		m_picMaxNums = globalCaptureSetItem.maxCaptureNum;
		m_capturePath = globalCaptureSetItem.savePath;
		m_picFormat = globalCaptureSetItem.format;
		m_CaptureMode = globalCaptureSetItem.Mode;

		m_isStickOnTopWhenPlay = globalBasicSetItem.isStickOnTopWhenPlay;
		m_isLocateByTimestamp = globalBasicSetItem.locateByTimestamp;
		m_isNeverStickOnTop = globalBasicSetItem.isNeverStickOnTop;
		m_isSaveFileList = globalBasicSetItem.saveListWhenLeave;
		m_isAlwaysStickOnTop = globalBasicSetItem.isAlwayOnTop;
		m_isLocateByFrame = globalBasicSetItem.locateByFrame;

		bool isHaveVideoPlay = playView->isVideoPlay(16);
		emit stickChange(isHaveVideoPlay);
		
		setNeverOrAlwaysOnTop();
	}
	QString path = getPath() + BASICSET_INI;
	BasicSetBox::WriteSetIni(path,&globalBasicSetItem,&globalCaptureSetItem,&globalHotkeySetItem);
}
void HSPlayer::basicSetInit()
{
	QString path = getPath() + BASICSET_INI;
	BasicSetBox::readSetIni(path);

	m_picFormat = globalCaptureSetItem.format;
	m_capturePath = globalCaptureSetItem.savePath;
	m_CaptureMode = globalCaptureSetItem.Mode;
	m_captuteInterval = globalCaptureSetItem.interval;
	m_picMaxNums = globalCaptureSetItem.maxCaptureNum;
	
	m_isStickOnTopWhenPlay = globalBasicSetItem.isStickOnTopWhenPlay;
	m_isLocateByTimestamp = globalBasicSetItem.locateByTimestamp;
	m_isNeverStickOnTop = globalBasicSetItem.isNeverStickOnTop;
	m_isSaveFileList = globalBasicSetItem.saveListWhenLeave;
	m_isAlwaysStickOnTop = globalBasicSetItem.isAlwayOnTop;
	m_isLocateByFrame = globalBasicSetItem.locateByFrame;
	m_isSaveFileList = globalBasicSetItem.saveListWhenLeave;

	setNeverOrAlwaysOnTop();
}

void HSPlayer::iniVersion()
{
	QString path = getPath() + CONFIG_INI;
	QString versionNum = playlist->readVersion(path);
	pTitleBar->setVersion(versionNum);
}

void HSPlayer::iniWrite(bool isIniWrite)
{
	QString path = getPath() + CONFIG_INI;
	HW_WRITE_LOG(log_info,"path: %s",path.toUtf8().data());
	playlist->writeIni(path,isIniWrite);
}
void HSPlayer::iniRead()
{
	QString path = getPath() + CONFIG_INI;       
	QStringList iniFileList = playlist->readIni(path);
	playlist->createFileNode(iniFileList);
}
void HSPlayer::iniLanguage()
{
	QString path = getPath() + CONFIG_INI;
	QString iLang = playlist->readCurLanguage(path);

	QString exePath = getPath() + "/translation/player/";
	QString QmName;  
	QTranslator Translator; 

	QString curUsedLan = pTitleBar->m_lang->codeToLan(iLang);
	int index = pTitleBar->list.indexOf(curUsedLan);
	if (index == -1)
	{
		index = 0;
	}

	QmName = "hsplayer_" + iLang + ".qm";
	pTitleBar->m_lanItem.at(index)->setChecked(true);
	
	if (translator->load(QmName,exePath)){
		qApp->installTranslator(translator);
	}
	playlist->getCurLanguage(iLang);
	updateUi();
}
void HSPlayer::setCtrlBtnEnabled(bool isCtrlBtnEnabled)
{    
	playCtrl->m_stopPlay->setEnabled(isCtrlBtnEnabled);
	playCtrl->m_slowForward->setEnabled(isCtrlBtnEnabled);
	playCtrl->m_fastForward->setEnabled(isCtrlBtnEnabled);
	playCtrl->m_frameForward->setEnabled(isCtrlBtnEnabled);
	m_fullPlayCtrl->m_stopPlay->setEnabled(isCtrlBtnEnabled);
	m_fullPlayCtrl->m_slowForward->setEnabled(isCtrlBtnEnabled);
	m_fullPlayCtrl->m_fastForward->setEnabled(isCtrlBtnEnabled);
	m_fullPlayCtrl->m_frameForward->setEnabled(isCtrlBtnEnabled);

	if (isCtrlBtnEnabled)
	{
		playCtrl->m_stopPlay->setStyleSheet("#StopPlay{background-image:url(" + getPath() + BTN_PAUSE_NOR + ")} #StopPlay:hover {background-image:url(" + getPath() + BTN_PAUSE_PRESS + ")}");
		playCtrl->m_slowForward->setStyleSheet("#SlowForward{background-image:url(" + getPath() + BTN_SLOW_NOR + ")} #SlowForward:hover {background-image:url(" + getPath() + BTN_SLOW_PRESS + ")}");
		playCtrl->m_fastForward->setStyleSheet("#FastForward{background-image:url(" + getPath() + BTN_FAST_NOR + ")} #FastForward:hover {background-image:url(" + getPath() + BTN_FAST_PRESS + ")}");
		playCtrl->m_frameForward->setStyleSheet("#FrameForward{background-image:url(" + getPath() + BTN_NEXTFRAME_NOR + ")} #FrameForward:hover {background-image:url(" + getPath() + BTN_NEXTFRAME_PRESS + ")}");
		m_fullPlayCtrl->m_stopPlay->setStyleSheet("#StopPlay{background-image:url(" + getPath() + BTN_PAUSE_NOR + ")} #StopPlay:hover {background-image:url(" + getPath() + BTN_PAUSE_PRESS + ")}");
		m_fullPlayCtrl->m_slowForward->setStyleSheet("#SlowForward{background-image:url(" + getPath() + BTN_SLOW_NOR + ")} #SlowForward:hover {background-image:url(" + getPath() + BTN_SLOW_PRESS + ")}");
		m_fullPlayCtrl->m_fastForward->setStyleSheet("#FastForward{background-image:url(" + getPath() + BTN_FAST_NOR + ")} #FastForward:hover {background-image:url(" + getPath() + BTN_FAST_PRESS + ")}");
		m_fullPlayCtrl->m_frameForward->setStyleSheet("#FrameForward{background-image:url(" + getPath() + BTN_NEXTFRAME_NOR + ")} #FrameForward:hover {background-image:url(" + getPath() + BTN_NEXTFRAME_PRESS + ")}");
	}else {
		playCtrl->m_stopPlay->setStyleSheet("#StopPlay::disabled {background-image:url(" + getPath() + BTN_PAUSE_DIS + ")}");
		playCtrl->m_slowForward->setStyleSheet("#SlowForward::disabled{background-image:url(" + getPath() + BTN_SLOW_DIS + ")}");
		playCtrl->m_fastForward->setStyleSheet("#FastForward::disabled{background-image:url(" + getPath() + BTN_FAST_DIS + ")}");
		playCtrl->m_frameForward->setStyleSheet("#FrameForward::disabled{background-image:url(" + getPath() + BTN_NEXTFRAME_DIS + ")}");
		m_fullPlayCtrl->m_stopPlay->setStyleSheet("#StopPlay::disabled {background-image:url(" + getPath() + BTN_PAUSE_DIS + ")}");
		m_fullPlayCtrl->m_slowForward->setStyleSheet("#SlowForward::disabled{background-image:url(" + getPath() + BTN_SLOW_DIS + ")}");
		m_fullPlayCtrl->m_fastForward->setStyleSheet("#FastForward::disabled{background-image:url(" + getPath() + BTN_FAST_DIS + ")}");
		m_fullPlayCtrl->m_frameForward->setStyleSheet("#FrameForward::disabled{background-image:url(" + getPath() + BTN_NEXTFRAME_DIS + ")}");
	}
}
void HSPlayer::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list")){
		event->acceptProposedAction();
	}
}
void HSPlayer::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if(!urls.isEmpty())
	{
		for (int i = 0;i < urls.size();++i)
		{
			QString file_name = urls.at(i).toLocalFile();
			drapList.append(file_name);
		}	
	}

	if (!drapList.isEmpty())
	{
		QStringList filterFiles = playlist->fileFilter(drapList);
		playlist->createFileNode(filterFiles);
	}
	drapList.clear();
}
void HSPlayer::closeEvent(QCloseEvent *event)
{
	if (!m_curLanguage.isEmpty()){
		playlist->getCurLanguage(m_curLanguage);
	}else {
		QString path = getPath() + CONFIG_INI;
		m_curLanguage = playlist->readCurLanguage(path);
		playlist->getCurLanguage(m_curLanguage);
	}

	iniWrite(m_isSaveFileList);	
	playlist->removeTempFile(getPath() + "/Skin/player/PlayListPic/");

	close();
	return QWidget::closeEvent(event);
}
void HSPlayer::updateUi()
{
	pTitleBar->initTitleUi();
	playlist->initPlayListUi();
	videoName->initVideoNameUi();
	BasicSetBox basicSetBox = new BasicSetBox;
	basicSetBox.initSetUi();
	playCtrl->initPlayCtrlUi();
	m_fullPlayCtrl->initPlayCtrlUi();
	m_fullWidget->initVideoNameUi();
	playView->updateMainItemLabel();
}
void HSPlayer::playControl()
{
	QString curVideoName = playView->getCurVideoName();
	if (curVideoName.isEmpty())
	{
		QString fileName = playlist->getCurFilePath();
		if (!fileName.isEmpty())
		{
			startPlay(fileName);
		}	
	}else {
		startPlay(curVideoName);
	}
}

void HSPlayer::videoCheckCtr()
{
	//打开校验界面，同时将文件列表传入
	QStringList  allFileList = playlist->getAllFilePath();
	CheckVideoWidget *checkWidget = new CheckVideoWidget(this);
	checkWidget->setFileList(allFileList);
	checkWidget->exec();
	

}

void HSPlayer::startPlay(QString fileName)
{
	QStringList allFileList = playlist->getAllFilePath();
	if (allFileList.indexOf(fileName) != -1)
	{
		videoName->showVideoStatus(fileName);
		int nums = playView->getWndNums();
		bool playRet = false;
		if(nums == 1)
		{
			HWND firItemHwnd = playView->getFirHwnd();
			playRet = playView->curPlayItem(fileName,firItemHwnd);
		}else {
			HWND curClickHwnd = playView->getClickedHwnd();
			if (curClickHwnd == NULL)
			{
				curClickHwnd = playView->getFirHwnd();
			}
			playRet = playView->curPlayItem(fileName,curClickHwnd);
		}
	}
}
void HSPlayer::urlVideoPic(QString fileName){
	QFileInfo videoInfo(fileName);
	QStringList tempList = playlist->getAllFilePath();
	if (tempList.indexOf(fileName) != -1)
	{
		if (!videoInfo.exists())
		{
			QStringList str1 = fileName.split("@");
			QStringList str2 = str1.at(1).split("/");
			QString strIp = str2.at(0);
			QString picturePath = getPath() + "/Skin/player/PlayListPic/" + strIp + ".jpg";
			QFileInfo picInfo(picturePath);
			if (!picInfo.exists())
			{
				getPlayVideoPic(fileName.toUtf8().data(),picturePath);
				int index = playlist->getCurSelectedIndex();
				playlist->deletePlayListItem();
				playlist->insertItem(index,fileName);
			}
		}
	}
}
void HSPlayer::doubleClickedAutoPlay(const QModelIndex &)
{
	stop();
	playControl();
}
void HSPlayer::stopCurPlay()
{
	QString fileName = playlist->getCurFilePath();
	playView->stopCurVideo(fileName);
	int wndNums = playView->getWndNums();
	if (wndNums == 1)
	{
		initVideo();
	}
}
void HSPlayer::stopAllPlay()
{
	playView->stopAllVideo();
	int wndNums = playView->getWndNums();
	if (wndNums == 1)
	{
		initVideo();
	}
}
void HSPlayer::muteCtrl(bool isOpenSound){
	m_isCurOpenSound = isOpenSound;
	if (isOpenSound)
	{
		playView->curPlaySoundItem();
	}else {
		playView->curCloseSoundItem();
	}
	playView->setSoundIsOpen(isOpenSound);
}
void HSPlayer::popup()
{
	popupWindow = new PopupWindow(m_index);
	if (m_mainLayout->isFullScreen())
	{
		QPoint fullMoveTo = m_fullPlayCtrl->m_windowDivision->mapToGlobal(QPoint(0,0));
		fullMoveTo += QPoint(-190,-50);
		popupWindow->move(fullMoveTo);
	}else {
		QPoint moveTo = playCtrl->m_windowDivision->mapToGlobal(QPoint(0,0));
		moveTo += QPoint(-190,-50);
		popupWindow->move(moveTo);
	}
	popupWindow->show();
	for (int i = 0;i < BTNNUM;++i)
	{
		connect(popupWindow->popupItem[i]->m_btn,SIGNAL(clicked()),this,SLOT(getCurrentIndex()));
	}
}
void HSPlayer::getCurrentIndex()
{
	QPushButton *Btn = (QPushButton *)QObject::sender();
	popupWindow->setCurrentItem(Btn);
	for (int i = 0;i < BTNNUM;++i)
	{
		if (Btn == popupWindow->popupItem[i]->m_btn)
		{
			m_index = popupWindow->popupItem[i]->index;
			break;
		} 
	}
	mainLayoutChange();
}
void HSPlayer::mainLayoutChange()
{
	if (m_index == 0)
	{
		initMainLayout();
	}else if (m_index == 1)
	{
		playView->setLayoutType(HS_VIEW_LAYOUT2x2);
		m_mainLayout->setCurrentWidget(playView);
	}else if (m_index == 2)
	{
		playView->setLayoutType(HS_VIEW_LAYOUT3x3);
		m_mainLayout->setCurrentWidget(playView);
	}else if (m_index == 3)
	{
		playView->setLayoutType(HS_VIEW_LAYOUT4x4);
		m_mainLayout->setCurrentWidget(playView);
	}
}
void HSPlayer::openFile(QStringList theList)
{
	if(!theList.isEmpty())
	{
		playlist->createFileNode(theList);
	}
}
void HSPlayer::stop()
{
	playView->curStopItem();
	initVideo();
	if (m_mainLayout->isFullScreen())
	{
		if (m_playmode == REPEATALL || m_playmode == REPEATONE)
		{
			restoreFromFullScreen();
		}
	}
}
void HSPlayer::initVideo(){
	playSpeed = 0;

	int wndNums = playView->getWndNums();
	if(wndNums == 1){
		initMainLayout();
		update();
	}

	if (m_mainLayout->isFullScreen())
	{
		if (m_playmode == SINGLE) //单视频播放
		{
			bool isHaveVideo = playView->isVideoPlay(wndNums);
			if (!isHaveVideo)
			{
				restoreFromFullScreen();
			}
		}else if (m_playmode == ORDER) //顺序播放
		{
			if (m_curVideoIndex == m_allFileList.size() - 1)
			{
				restoreFromFullScreen();
			}
		}
	}else {
		bool isHaveVideo = playView->isVideoPlay(wndNums);
		if (!isHaveVideo)
		{
			m_fullWidget->hide();
			videoName->m_fullScreenBtn->setEnabled(false);
			videoName->m_fullScreenBtn->setStyleSheet("#FullScreen::disabled {background-image:url(" + getPath() + BTN_FULLSCREEN_DIS + ")}");
		}
	}
}
void HSPlayer::restoreFromFullScreen(){
	m_mainLayout->setWindowFlags(Qt::SubWindow); 
	m_mainLayout->showNormal();
	m_isFullScreen = false;
	m_fullWidget->hide();
	videoName->m_fullScreenBtn->setEnabled(false);
	videoName->m_fullScreenBtn->setStyleSheet("#FullScreen::disabled {background-image:url(" + getPath() + BTN_FULLSCREEN_DIS + ")}");
}
void HSPlayer::snapShot()
{
	playView->curSnapShotItem(m_capturePath);
}
void HSPlayer::fullScreen()
{
	if (m_isFullScreen)
	{
		m_mainLayout->setWindowFlags(Qt::SubWindow); 
		m_mainLayout->showNormal();
		muteBtnStatusWhenFullscreen(m_isCurOpenSound,playCtrl);
		continousCaptureBtnStatus(m_isStopCapture,videoName);
		m_fullPlayCtrl->hide();
		m_fullWidget->hide();
		m_isFullScreen = false;
	}else{
		m_mainLayout->setWindowFlags(Qt::Dialog);
		m_mainLayout->showFullScreen();
		if (!m_fullWidget->isVisible())
		{
			m_fullWidget->show();
		}
		if (!m_fullPlayCtrl->isVisible())
		{
			m_fullPlayCtrl->show();
		}
		m_fullWidget->setStyleSheet("#FullScreen {background-image:url(" + getPath() + BTN_FULLSCREEN_NOR + ")} #FullScreen:hover {background-image:url(" + getPath() + BTN_FULLSCREEN_PRESS + ")}");
		muteBtnStatusWhenFullscreen(m_isCurOpenSound,m_fullPlayCtrl);
		continousCaptureBtnStatus(m_isStopCapture,m_fullWidget);
		m_isFullScreen = true;
		m_fullWidget->setGeometry(0,-33,m_mainLayout->width(),33);
		m_fullPlayCtrl->setGeometry(0,m_mainLayout->height(),m_mainLayout->width(),100);
	}
	m_isToolBarHide = true;
}
void HSPlayer::muteBtnStatusWhenFullscreen(bool isOpenSound,PlayCtrl *ctrlWidget){
	if (isOpenSound)
	{
		ctrlWidget->m_mute->setStyleSheet("#Mute{background-image:url(" + getPath() + BTN_VOLUME_NOR + ")} #Mute:hover {background-image:url(" + getPath() + BTN_VOLUME_PRESS + ")}");
		ctrlWidget->setIsOpenSound(true);
	}else {
		ctrlWidget->m_mute->setStyleSheet("#Mute{background-image:url(" + getPath() + BTN_MUTE_NOR + ")} #Mute:hover {background-image:url(" + getPath() + BTN_MUTE_PRESS + ")}");
		ctrlWidget->setIsOpenSound(false);
	}
}
void HSPlayer::continousCaptureBtnStatus(bool isStopCapture,VideoName *videoWidget){
	if (isStopCapture)
	{
		videoWidget->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
		videoWidget->setIsStopCapture(true);
	}else {
		videoWidget->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #DigitalZoom:hover{background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
		videoWidget->setIsStopCapture(false);
	}
}
void HSPlayer::fullScreenCtrl(int pos)
{
	if (m_isFullScreen)
	{
		videoName->m_fullScreenBtn->setEnabled(true);
		m_fullWidget->m_fullScreenBtn->setEnabled(true);
		int h = m_mainLayout->height();
		if (pos >= h - 120 || pos <= 36 )
		{
			if (m_isToolBarHide){
				setAutoHide(false);
			}
		}else{
			if(!m_isToolBarHide){
				setAutoHide(true);
			}
		}
	}
}
void HSPlayer::setAutoHide(bool bHide){
	QRect showRect(0,m_mainLayout->height()-100,m_mainLayout->width(),100);
	QRect hideRect(0,m_mainLayout->height(),m_mainLayout->width(),100);

	QRect showVideoNameRect(0,0,m_mainLayout->width(),33);
	QRect hideVideoNameRect(0,-33,m_mainLayout->width(),33);

	_animation->setDuration(300); 
	_animationVideoName->setDuration(300);

	if (bHide)
	{
		_animation->setStartValue(showRect);
		_animation->setEndValue(hideRect);
		_animationVideoName->setStartValue(showVideoNameRect);
		_animationVideoName->setEndValue(hideVideoNameRect);
	}else {
		_animation->setStartValue(hideRect);
		_animation->setEndValue(showRect);
		_animationVideoName->setStartValue(hideVideoNameRect);
		_animationVideoName->setEndValue(showVideoNameRect);
	}

	m_isToolBarHide = bHide;
	_group->addAnimation(_animation);
	_group->addAnimation(_animationVideoName);
	_group->start();
}
void HSPlayer::DigitalZoom()
{
	if (m_isDigitalZoom)
	{
		m_isDigitalZoom = false;
		playView->setCurDigitalZoom(m_isDigitalZoom);
	}else {
		m_isDigitalZoom = true;
		playView->setCurDigitalZoom(m_isDigitalZoom);
	}
	videoName->setDigitalBtn(m_isDigitalZoom);
	m_fullWidget->setDigitalBtn(m_isDigitalZoom);
	playView->setCurRect();
}
void HSPlayer::stepByOne()
{
	playView->curStepOneItem();
}
void HSPlayer::fastFrame(bool isWndChange){
	if (isWndChange)
	{
		playSpeed = playView->getCurSpeed();
	}
	if(playSpeed < 0){ 
		playSpeed = 0;
		m_isFastBtnChange = true;
		playView->setCurPlaySpeed(playSpeed);
	}
	if (!m_isFastBtnChange)
	{
		long curSpeed = playSpeed + 1;
		playSpeed = curSpeed;
		if (curSpeed <= 3)
		{
			playView->setCurPlaySpeed(curSpeed);
		}
	}
	m_isFastBtnChange = false;
}
void HSPlayer::slowFrame(bool isWndChange){
	if (isWndChange)
	{
		playSpeed = playView->getCurSpeed();
	}
	if(playSpeed > 0){ 
		playSpeed = 0;
		m_isSlowBtnChange = true;
		playView->setCurPlaySpeed(playSpeed);
	}
	if (!m_isSlowBtnChange)
	{
		long curSpeed = playSpeed - 1;
		playSpeed = curSpeed;

		if (curSpeed >= -3)
		{
			playView->setCurPlaySpeed(curSpeed);
		}
	}
	m_isSlowBtnChange = false;
}
void HSPlayer::setFastSpeed()
{
	int index = playView->getSelectedWndIndex();
	bool isWndChanged = curWndIndexChange(index);
	fastFrame(isWndChanged);
}
void HSPlayer::setSlowSpeed(){
	int index = playView->getSelectedWndIndex();
	bool isWndChanged = curWndIndexChange(index);
	slowFrame(isWndChanged);
}
void HSPlayer::rightBtn()
{
	playControl();
}
void HSPlayer::continousCapture(bool isContinousCapture)
{
	m_isStopCapture = isContinousCapture;
	playView->setIsStopCapture(isContinousCapture);
	playView->curContinousCaptrueItem(m_captuteInterval,m_picMaxNums,m_capturePath);
}
void HSPlayer::captureOverNext(){
	if(m_isStopCapture){
		m_isStopCapture = false;
		if (m_mainLayout->isFullScreen())
		{
			m_fullWidget->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #DigitalZoom:hover{background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
			m_fullWidget->setIsStopCapture(m_isStopCapture);
		}else {
			videoName->m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #DigitalZoom:hover{background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
			videoName->setIsStopCapture(m_isStopCapture);
		}
	}
}
void HSPlayer::getPlayVideoPic(QString fileFullPath,QString picPath)
{
	playView->getPlayListPic(fileFullPath,picPath);
}
bool HSPlayer::curWndIndexChange(int curIndex)
{
	if (m_curWndIndex != curIndex)
	{
		m_curWndIndex = curIndex;
		return true;
	}else {
		return false;
	}
}
void HSPlayer::setStickOnTop(bool isAnyVideoPlay){
	if (m_isStickOnTopWhenPlay)
	{
		if (isAnyVideoPlay)
		{
			SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
		}else {
			SetWindowPos((HWND)this->winId(),HWND_NOTOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
		}
	}
}
void HSPlayer::setNeverOrAlwaysOnTop(){
	if (m_isAlwaysStickOnTop)
	{
		SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
	}else if (m_isNeverStickOnTop)
	{
		SetWindowPos((HWND)this->winId(),HWND_NOTOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
	}
}
void HSPlayer::singleMode(){
	m_playmode = SINGLE;
}
void HSPlayer::orderMode(){
	m_playmode = ORDER;
}
void HSPlayer::repeatOneMode(){
	m_playmode = REPEATONE;
}
void HSPlayer::repeatAllMode(){
	m_playmode = REPEATALL;
}
void HSPlayer::changePlayMode(LayoutItem *theItem){
	m_playItem = new LayoutItem;
	//获取程序名，放在配置文件中方便定制
	QString path = getPath() + CONFIG_INI;
	QString Pname = playlist->readName(path);
	m_playItem->setName(Pname);
	m_playItem = theItem;

	m_videoName = m_playItem->getName();
	m_allFileList = playlist->getAllFilePath();
	m_curVideoIndex = m_allFileList.indexOf(m_videoName);
	m_hWnd = m_playItem->m_videoWidget->winId();

	initVideo();

	emit playMode(m_curVideoIndex);
}
void HSPlayer::setCurPlayMode(int videoIndex){
	switch(m_playmode){
	case SINGLE: //单个播放
		break;
	case ORDER:  //顺序播放
		{
			int index = videoIndex + 1;
			if (index < m_allFileList.size())
			{
				m_playItem->curItemPlay(m_allFileList.at(index),m_hWnd);
			}
		}
		break;
	case REPEATONE:	 //单个循环
		m_playItem->curItemPlay(m_allFileList.at(videoIndex),m_hWnd);
		break;
	case REPEATALL:  //列表循环
		{
			int index = videoIndex + 1;
			if (index <= m_allFileList.size())
			{
				if (index == m_allFileList.size())
				{
					index = 0;
				}
				m_playItem->curItemPlay(m_allFileList.at(index),m_hWnd);
			}
		}
		break;
	}
}