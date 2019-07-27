#include "openurl.h"
#include "resource_tr.h"
#include <Windows.h>
#include "AVPlayerDef.h"
#include "HSAVPlayer.h"
#include "customizemsgbox.h"
#include "playlist.h"
#include <QListView>
#include <QPainter>
#include <QDebug>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

extern QString urlPath;

openUrl::openUrl(QWidget *parent)
	:BaseWindow(parent)
{
	setFixedSize(530,255);
	m_url = new QLabel(tr("URL:"));
	m_url->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	//m_urlInput 设置model  使下拉列表带记录功能
	m_urlInput = new QComboBox;
	m_urlInput->addItem("");
	//m_model = new QStringListModel(this);
	//m_model->setStringList(urlItem);
	m_listItem = new QListView;
	//m_listItem->setModel(m_model);
	m_urlInput->setView(m_listItem);
	m_urlInput->setObjectName("UrlInput");
	m_urlInput->setEditable(true);
	m_urlInput->setFixedSize(380,25);

	m_connectionMode = new QLabel(tr("Connection Mode:"));
	m_connectionMode->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_connectionModeSel = new QComboBox;
	m_connectionModeSel->setView(new QListView());
	m_connectionModeSel->setObjectName("ConnectionMode");
	m_connectionModeSel->setFixedSize(380,25);
	m_connectionModeSel->addItem("TCP");
	m_connectionModeSel->addItem("UDP");
	m_connectionModeSel->addItem("HTTP");

	m_okBtn = new QPushButton(tr("Yes"));
	m_okBtn->setObjectName("OpenUrlOk");
	m_okBtn->setFixedSize(70,25);
	m_okBtn->setStyleSheet("#OpenUrlOk{background-image:url(" + getPath() + BTN_COMFIRM_NOR + ");} #OpenUrlOk:hover {background-image:url(" + getPath() + BTN_COMFIRM_PRESS + ")}");

	m_cancelBtn = new QPushButton(tr("No"));
	m_cancelBtn->setObjectName("OpenUrlCancel");
	m_cancelBtn->setFixedSize(70,25);
	m_cancelBtn->setStyleSheet("#OpenUrlCancel{background-image:url(" + getPath() + BTN_CANCEL_NOR + ");} #OpenUrlCancel:hover {background-image:url(" + getPath() + BTN_CANCEL_PRESS + ")}");

	m_example = new QLabel(tr("Example:rtsp://admin:12345@172.6.10.11:554/Stream/Channels/101 \n\n      rtsp://UserName:PassWord@Ip Address/Stream/Channels/101"));
	m_example->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_example->setWordWrap(true);
	m_example->setFixedWidth(500);

	QGridLayout *gl = new QGridLayout;
	gl->setContentsMargins(0,40,15,0);
	gl->setSpacing(10);
	gl->addWidget(m_url,0,0,1,1);
	gl->addWidget(m_urlInput,0,1,1,1);
	gl->addWidget(m_connectionMode,1,0,1,1);
	gl->addWidget(m_connectionModeSel,1,1,1,1);
	//gl->addWidget(m_example,3,1,2,1);

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,0,0,0);
	hl->setSpacing(10);
	hl->addStretch();
	hl->addWidget(m_okBtn);
	hl->addWidget(m_cancelBtn);
	
	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,10,10);
	vl->setSpacing(20);
	//vl->addStretch();
	vl->addLayout(gl);
	vl->addWidget(m_example);
	vl->addLayout(hl);
	setLayout(vl);

	initWindow();

	HS_Initial();
	HS_Free();
}

openUrl::~openUrl()
{

}
void openUrl::initWindow()
{
	initTitleBar();
	Qt::WindowFlags flags = this->windowFlags();
	this->setWindowFlags(flags | Qt::Window);

	connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkClicked()));
	connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

void openUrl::initTitleBar()
{
	m_titleBar->move(0, 0);
	m_titleBar->setWindowBorderWidth(0);
	m_titleBar->setBackgroundColor(45,45,45);
	m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	m_titleBar->setTitleContent(tr("About"));
}

void openUrl::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()) , 3 , 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(QColor("#262626")));
	return QWidget::paintEvent(event);
}

void openUrl::setWindowTitle(QString title, int titleFontSize)
{
	m_titleBar->setTitleContent(title, titleFontSize);
}

void openUrl::setComboboxItem(){
	QString path = getPath() + URL_INI;
	QString item = m_playlist->readUrlIni(path);
	m_urlInput->addItem(item);
}

int openUrl::showMyMessageBox(QWidget* parent,PlayList * thePlaylist ,const QString &title,bool isModelWindow)
{
	openUrl * myMessageBox = new openUrl(parent);
	myMessageBox->setWindowTitle(title);
	myMessageBox->setPlaylist(thePlaylist);
	myMessageBox->setComboboxItem();
	if (isModelWindow)
	{
		return myMessageBox->exec();
	}
	else
	{
		myMessageBox->show();
	}
	return 0;
}

int openUrl::exec()
{
	this->setWindowModality(Qt::WindowModal); 
	show();

	m_eventLoop = new QEventLoop(this);
	m_eventLoop->exec();

	return m_chooseResult;
}

void openUrl::onOkClicked()
{
	m_chooseResult = OK;
	HANDLE m_localPlayHandle = NULL;
	if (m_localPlayHandle == NULL)
	{
		if (!m_urlInput->currentText().isEmpty())
		{
			QByteArray ba = m_urlInput->currentText().toLocal8Bit();
			char *msg = ba.data();
			int openRet = HS_OpenRecFile(msg,&m_localPlayHandle);
			if (openRet != -1)
			{
				urlPath = m_urlInput->currentText();
				QString iniPath = getPath() + URL_INI;
				m_playlist->getUrl(urlPath);
				m_playlist->writeIni(iniPath);
				close();
			}else {
				urlPath = "";
				//弹出提示框 提示超时
				CustomizeMsgBox::showMyMessageBox(this,tr("Hint"),tr("connection failed"),BUTTON_OK_AND_CANCEL,true);
			}
		}else {
			//URL地址为空
			CustomizeMsgBox::showMyMessageBox(this,tr("Hint"),tr("The url is empty"),BUTTON_OK_AND_CANCEL,true);
		}
	}
	HS_CloseRecFile(m_localPlayHandle);
	m_localPlayHandle = NULL;
}

void openUrl::onCancelClicked()
{
	m_chooseResult = CANCEL;
	close();
}

void openUrl::closeEvent(QCloseEvent *event)
{
	if (m_eventLoop != NULL)
	{
		m_eventLoop->exit();
	}
		event->accept();
}