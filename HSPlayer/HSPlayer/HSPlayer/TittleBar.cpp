#include "titlebar.h"
#include "playlist.h"
#include "aboutmsgbox.h"
#include "openurl.h"
#include "resource_tr.h"
#include <QEvent>
#include <QDebug>
#include <QActionGroup>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QApplication>

#define TITLEBAR_HEIGHT 36
#define BUTTON_WIDTH 24
#define BUTTON_HEIGHT 24

QString urlPath;

TitleBar::TitleBar(QWidget *parent)
	:QWidget(parent)
	,m_isPressed(false)
	,m_isMaxmized(false)
{
	this->setFixedHeight(TITLEBAR_HEIGHT);

	m_ConnentLabel = new QPushButton(this);
	m_ConnentLabel->setFocusPolicy(Qt::NoFocus);
	m_MaximizeButton = new QPushButton(this);
	m_MaximizeButton->setFocusPolicy(Qt::NoFocus);
	m_MinimizeButton = new QPushButton(this);
	m_MinimizeButton->setFocusPolicy(Qt::NoFocus);
	m_CloseButton = new QPushButton(this);
	m_CloseButton->setShortcut(QString("Ctrl+W"));
	m_CloseButton->setFocusPolicy(Qt::NoFocus);
	m_setting = new QPushButton(this);
	m_setting->setFocusPolicy(Qt::NoFocus);
	m_setBtn = new QMenu(this);

	m_setting->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
	m_MinimizeButton->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
	m_MaximizeButton->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
	m_CloseButton->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);

	m_ConnentLabel->setObjectName("whiteLabel");
	m_setting->setObjectName("Setting");
	m_setting->setStyleSheet("#Setting{background-image:url(" + getPath() + BTN_SETUP_NOR + ")} #Setting:hover {background-image:url(" +  getPath() + BTN_SETUP_PRESS + ")}");
	
	m_MinimizeButton->setObjectName("minimizeButton");
	m_MinimizeButton->setStyleSheet("#minimizeButton{background-image:url(" + getPath() + BTN_MINIMIZE_NOR + ") }#minimizeButton:hover {background-image:url(" + getPath() + BTN_MINIMIZE_PRESS + ") }");
	m_MaximizeButton->setObjectName("maximizeButton");
	m_MaximizeButton->setStyleSheet("#maximizeButton{background-image:url(" + getPath() + BTN_MAXIMIZE_NOR + ") } #maximizeButton:hover {background-image:url(" + getPath() + BTN_MAXIMIZE_PRESS + ") }");
	m_CloseButton->setObjectName("closeButton");
	m_CloseButton->setStyleSheet("#closeButton{background-image:url(" + getPath() + BTN_CLOSE_NOR + ") } #closeButton:hover {background-image:url(" + getPath() + BTN_CLOSE_PRESS + ") }");

	m_open = new QMenu;
	m_setBtn->addMenu(m_open);
	m_openFile = new QAction(this);
	m_openDir = new QAction(this);
	m_openUrl = new QAction(this);
	m_open->addAction(m_openFile);
	m_open->addAction(m_openDir);
	//m_open->addAction(m_openUrl);

	m_lang = new Language();
	m_lang->init();
	//支持的语言类型
	list = m_lang->suportedLanguages();
	m_language = new QMenu;
	QActionGroup *actionGroup = new QActionGroup(this);

	for (int i = 0;i < list.size();++i)
	{
		m_lanItem.append(new lanItem(this));
		m_lanItem.at(i)->index = i;
		m_language->addAction(m_lanItem.at(i));
		m_lanItem.at(i)->setCheckable(true);
		actionGroup->addAction(m_lanItem.at(i));

		connect(m_lanItem.at(i),SIGNAL(triggered()),this,SLOT(onCurLan()));
	}

	m_setBtn->addMenu(m_language);

	m_settings = new QAction(this);
	m_setBtn->addAction(m_settings);

	//m_userManual = new QAction(this);
	//m_setBtn->addAction(m_userManual);

	m_about = new QAction(this);
	m_setBtn->addAction(m_about);

	m_setting->setMenu(m_setBtn);

	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->addSpacing(5);
	pLayout->addStretch();
	pLayout->addWidget(m_ConnentLabel);
	pLayout->addWidget(m_setting);
	pLayout->addWidget(m_MinimizeButton);
	pLayout->addWidget(m_MaximizeButton);
	pLayout->addWidget(m_CloseButton);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(5,0,15,0);

	setLayout(pLayout);

	initTitleUi();

	connect(m_MinimizeButton,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
	connect(m_MaximizeButton,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
	connect(m_CloseButton,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
	connect(m_openFile,SIGNAL(triggered()),this,SLOT(menuAddFile()));
	connect(m_openDir,SIGNAL(triggered()),this,SLOT(menuOpenDir()));
	connect(m_about,SIGNAL(triggered()),this,SLOT(menuAbout()));
	connect(m_openUrl,SIGNAL(triggered()),this,SLOT(menuOpenUrl()));
//	connect(m_ConnentLabel,SIGNAL(clicked()),this,SLOT(showCurLanguage()));
}
TitleBar::~TitleBar()
{

}
void TitleBar::initTitleUi()
{
	//m_ConnentLabel->setText(tr("English"));
	m_MinimizeButton->setToolTip(tr("Minimize"));
	m_CloseButton->setToolTip(tr("Close"));

	m_open->setTitle(tr("Open"));
	m_openFile->setText(tr("Open File"));
	m_openDir->setText(tr("Open Directory"));
	m_openUrl->setText(tr("Open Url"));

	m_language->setTitle(tr("Language"));

	m_settings->setText(tr("Settings"));
	m_setting->setToolTip(tr("Main Menu"));
	//m_userManual->setText(tr("User Manual"));
	m_about->setText(tr("About"));

	for (int i = 0;i < m_lanItem.size();++i)
	{
		QString lan = list.at(i);
		if (lan == "Chinese Simplified")
		{
			m_lanItem.at(i)->setText(tr("Chinese Simplified"));
		}else if (lan == "English")
		{
			m_lanItem.at(i)->setText(tr("English"));
		}else if (lan == "Chinese Traditional")
		{
			m_lanItem.at(i)->setText(tr("Chinese Traditional"));
		}else if (lan == "Russian")
		{
			m_lanItem.at(i)->setText(tr("Russian"));
		}else if (lan == "Korean")
		{
			m_lanItem.at(i)->setText(tr("Korean"));
		}else if (lan == "Polish")
		{
			m_lanItem.at(i)->setText(tr("Polish"));
		}else if (lan == "French")
		{
			m_lanItem.at(i)->setText(tr("French"));
		}else if (lan == "Japanese")
		{
			m_lanItem.at(i)->setText(tr("Japanese"));
		}else if(lan == "Spanish")
		{
			m_lanItem.at(i)->setText(tr("Spanish"));
		}else if(lan == "Portuguese")
		{
			m_lanItem.at(i)->setText(tr("Portuguese"));
		}else if(lan == "Italian")
		{
			m_lanItem.at(i)->setText(tr("Hebrew"));
		}else if(lan == "Turkish")
		{
			m_lanItem.at(i)->setText(tr("Turkish"));
		}else if(lan == "Bulgaria")
		{
			m_lanItem.at(i)->setText(tr("Bulgaria"));
		}else if(lan == "German") 
		{
			m_lanItem.at(i)->setText(tr("German"));
		}else if(lan == "Dutch")
		{
			m_lanItem.at(i)->setText(tr("Dutch"));
		}else if(lan == "Ukraine") 
		{
			m_lanItem.at(i)->setText(tr("Ukraine"));
		}else if(lan == "Italian")
		{
			m_lanItem.at(i)->setText(tr("Italian"));
		}else if(lan == "Persian")
		{
			m_lanItem.at(i)->setText(tr("Persian"));
		}
	}
}

void TitleBar::setVersion(QString versionNumber)
{
	m_VersionNumber = versionNumber;

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	emit m_MaximizeButton->click();
}
void TitleBar::mousePressEvent(QMouseEvent *event)
{
	if (m_MaximizeButton->isVisible())
	{
		m_isPressed = true;
		m_StartMovePos = event->globalPos();
	}
	return QWidget::mousePressEvent(event);
}
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	QWidget *curWidget = this->window();
	if (m_isPressed)
	{
		if (!curWidget->isMaximized())
		{
			QPoint movePos = event->globalPos() - m_StartMovePos;
			QPoint widgetPos = this->parentWidget()->pos();
			m_StartMovePos = event->globalPos();
			this->parentWidget()->move(widgetPos.x()+movePos.x(),widgetPos.y()+movePos.y());
		}
	}
	return QWidget::mouseMoveEvent(event);
}
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
		{
			QWidget *pWidget = qobject_cast<QWidget *>(obj);
			if (pWidget)
			{
				m_ConnentLabel->setText(pWidget->windowTitle());
				return true;
			}
		}
	case QEvent::WindowIconChange:
		{
			QWidget *pWidget = qobject_cast<QWidget *>(obj);
			if (pWidget)
			{
				QIcon icon = pWidget->windowIcon();
				m_IconLabel->setPixmap(icon.pixmap(m_IconLabel->size()));
				return true;
			}
		}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj,event);
}
void TitleBar::onClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_MinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_MaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_CloseButton)
		{
			pWindow->close();
		}
	}
}
void TitleBar::updateMaximize()
{
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized();
		if (bMaximize)
		{
			m_MaximizeButton->setToolTip(tr("Restore"));
			m_MaximizeButton->setProperty("maximizeProperty", "restore");
		}
		else
		{
			m_MaximizeButton->setProperty("maximizeProperty", "maximize");
			m_MaximizeButton->setToolTip(tr("Maximize"));
		}
		m_MaximizeButton->setStyle(QApplication::style());
	}
}
void TitleBar::menuAddFile()
{
	_playList->mAddFile();
}
void TitleBar::menuOpenDir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"./");
	QStringList traverseFileList = _playList->traverseDir(dir);
	if (!traverseFileList.isEmpty())
	{
		_playList->createFileNode(traverseFileList);
	}
	traverseFileList.clear();
}
void TitleBar::menuAbout()
{
	AboutMsgBox::showMyMessageBox(this,tr("About"),tr("Version:")+m_VersionNumber,BUTTON_OK,true,tr("All Right Reserved(C)2018"));
}
void TitleBar::menuOpenUrl()
{
	int result = m_OpenUrl->showMyMessageBox(this,_playList,tr("Open Url"),true);
	if(result == OK){
		if (!urlPath.isEmpty())
		{
			emit UrlPath(urlPath);
		}
 	}
}
void TitleBar::onCurLan(){
	lanItem *obj = (lanItem *)QObject::sender();
	QString lan = list.at(obj->index);
	QString code = m_lang->lanToCode(lan);

	emit curlanCode(code,obj->index);
}
