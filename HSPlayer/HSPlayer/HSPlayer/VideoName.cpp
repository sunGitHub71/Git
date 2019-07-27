#include "videoname.h"
#include "resource_tr.h"
#include <QKeyEvent>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

VideoName::VideoName(QWidget *parent)
	:QWidget(parent)
	,m_isStyleChange(false)
	,m_isContinousCapture(false)
{
	m_videoName = new QWidget;
	m_videoName->setObjectName("VideoName");
	m_videoName->setFixedHeight(33);
	m_videoName->setStyleSheet("#VideoName{background-color:#262626;border-top:1px solid #000000;border-left:1px solid #000000;border-right:1px solid #000000;}");

	m_videoNameLabel = new QLabel;
	m_videoNameLabel->setObjectName("VideoNameLabel");

	m_digitalZoomBtn = new QPushButton;
	m_digitalZoomBtn->setFocusPolicy(Qt::NoFocus);
	m_digitalZoomBtn->setObjectName("DigitalZoom");
	m_digitalZoomBtn->setStyleSheet("#DigitalZoom::disabled {background-image:url(" + getPath() + BTN_EXPAND_DIS + ")}");
	m_digitalZoomBtn->setEnabled(false);

	m_captureBtn = new QPushButton;
	m_captureBtn->setFocusPolicy(Qt::NoFocus);
	m_captureBtn->setShortcut(QString("F11"));
	m_captureBtn->setObjectName("Capture");
	m_captureBtn->setStyleSheet("#Capture::disabled {background-image:url(" + getPath() + BTN_SNAP_DIS + ")}");
	m_captureBtn->setEnabled(false);

	m_continuousCaptureBtn = new QPushButton;
	m_continuousCaptureBtn->setFocusPolicy(Qt::NoFocus);
	m_continuousCaptureBtn->setObjectName("ContinuousCapture");
	m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture::disabled {background-image:url(" + getPath() + BTN_SHOOT_DIS + ")}");
	m_continuousCaptureBtn->setEnabled(false);

	m_fullScreenBtn = new QPushButton;
	m_fullScreenBtn->setFocusPolicy(Qt::NoFocus);
	m_fullScreenBtn->setShortcut(QString("ctrl+Alt+F"));
	m_fullScreenBtn->setObjectName("FullScreen");
	m_fullScreenBtn->setStyleSheet("#FullScreen::disabled {background-image:url(" + getPath() + BTN_FULLSCREEN_DIS + ")}");
	m_fullScreenBtn->setEnabled(false);

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(10,0,14,0);
	hl->setSpacing(0);
	hl->addWidget(m_videoNameLabel);
	hl->addStretch();
	hl->addWidget(m_digitalZoomBtn);
	hl->addWidget(m_captureBtn);
	hl->addWidget(m_continuousCaptureBtn);
	hl->addWidget(m_fullScreenBtn);
	m_videoName->setLayout(hl);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_videoName);
	setLayout(vl);

	initVideoNameUi();

	connect(m_continuousCaptureBtn,SIGNAL(clicked()),this,SLOT(getIscontinuousCapture()));
	connect(m_fullScreenBtn,SIGNAL(clicked()),this,SIGNAL(fullScreen()));
}
VideoName::~VideoName()
{

}
void VideoName::initVideoNameUi()
{
	videoNameInit();
	m_digitalZoomBtn->setToolTip(tr("DigtitalZoom"));
	m_captureBtn->setToolTip(tr("Capture"));
	m_continuousCaptureBtn->setToolTip(tr("ContinuousCapture"));
	m_fullScreenBtn->setToolTip(tr("Full Screen"));
}
void VideoName::keyPressEvent(QKeyEvent *event){
	if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Alt))
	{
		if (event->key() == Qt::Key_F)
		{
			emit fullScreen();
		}
	}
}
void VideoName::showVideoStatus(QString fileName)
{
	if (fileName.isEmpty())
	{
		videoNameInit();
	}else {
		QFileInfo *info = new QFileInfo(fileName);
		if (!info->exists())
		{
			m_videoNameLabel->setText(fileName);
		}else {
			QString videoName = info->fileName();
			m_videoNameLabel->setText(videoName);
		}
	}
}
void VideoName::videoNameInit()
{
	m_videoNameLabel->setText(tr("Video Name"));
}
void VideoName::setDigitalBtn(bool isStyleChange)
{
	m_isStyleChange = isStyleChange;
	
	if (m_digitalZoomBtn->isEnabled())
	{
		if (m_isStyleChange)
		{
			m_digitalZoomBtn->setStyleSheet("#DigitalZoom{background-image:url(" + getPath() + BTN_EXPAND_PRESS + ")}");
		}else {
			m_digitalZoomBtn->setStyleSheet("#DigitalZoom{background-image:url(" + getPath() + BTN_EXPAND_NOR + ")} #DigitalZoom:hover{background-image:url(" + getPath() + BTN_EXPAND_PRESS + ")}");
		}
	}
}
void VideoName::getIscontinuousCapture(){
	if(m_continuousCaptureBtn->isEnabled()){
		if(m_isContinousCapture){
			m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_NOR + ")} #DigitalZoom:hover{background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
			m_isContinousCapture = false;
		}else {
			m_continuousCaptureBtn->setStyleSheet("#ContinuousCapture {background-image:url(" + getPath() + BTN_SHOOT_PRESS + ")}");
			m_isContinousCapture = true;
		}
	}
	emit continousCapture(m_isContinousCapture);
}
