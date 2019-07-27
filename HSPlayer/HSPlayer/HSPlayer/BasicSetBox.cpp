#include "basicsetbox.h"
#include "resource_tr.h"
#include "basicSetItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QPainter>
#include <QListView>
#include <QGridLayout>
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>

extern CAPTURE_SET_ITEM globalCaptureSetItem;
extern BASIC_SET_ITEM globalBasicSetItem;
extern HOTKEY_SET_ITEM globalHotkeySetItem;

BasicSetBox::BasicSetBox(QWidget *parent,int index)
	:BaseWindow(parent)
	,m_index(0)
{
	setFixedSize(570,488);
	m_okBtn = new QPushButton(this);
	m_okBtn->setFixedSize(60,28);
	m_okBtn->setObjectName("OkBtn");
	m_okBtn->setStyleSheet("#OkBtn{background-image:url(" + getPath() + BTN_COMFIRM_NOR + ");} #OkBtn:hover {background-image:url(" + getPath() + BTN_COMFIRM_PRESS + ");}");

	m_cancelBtn = new QPushButton(this);
	m_cancelBtn->setFixedSize(60,28);
	m_cancelBtn->setObjectName("CancelBtn");
	m_cancelBtn->setStyleSheet("#CancelBtn{background-image:url(" + getPath() + BTN_CANCEL_NOR + ");} #CancelBtn:hover {background-image:url(" + getPath() + BTN_CANCEL_PRESS + ");}");

	double w = this->width()/3;

	QFrame *fr = new QFrame;
	QHBoxLayout *hlBtn = new QHBoxLayout;
	hlBtn->setContentsMargins(0,0,10,0);
	hlBtn->setSpacing(10);
	hlBtn->addStretch();
	hlBtn->addWidget(m_okBtn);
	hlBtn->addWidget(m_cancelBtn);
	fr->setLayout(hlBtn);
	
	m_warp = new QFrame;
	m_warp->setObjectName("Warp");
	m_warp->setStyleSheet("#Warp{border:none;border-bottom:1px solid #111111;}");

	QFrame *basic = new QFrame;
	m_basicBtn = new CusButton(getPath() + BTN_BASICSET_NOR,getPath() + BTN_BASICSET_PRESS,getPath() + BTN_BASICSET_PRESS);
	
	QGridLayout *gl3 = new QGridLayout;
	gl3->setContentsMargins(0,0,0,0);
	gl3->setSpacing(0);
	gl3->addWidget(m_basicBtn,0,0,1,1);
	basic->setLayout(gl3);

	QFrame *capture = new QFrame;
	m_captureBtn = new CusButton(getPath() + BTN_CAPTURE_NOR,getPath() + BTN_CAPTURE_PRESS,getPath() + BTN_CAPTURE_PRESS);

	capture->setFixedSize(w,90);

	QGridLayout *gl4 = new QGridLayout;
	gl4->setContentsMargins(0,0,0,0);
	gl4->setSpacing(0);
	gl4->addWidget(m_captureBtn,0,0,1,1);
	capture->setLayout(gl4);
	
	QFrame *hotkey = new QFrame;
	m_hotkeyBtn = new CusButton(getPath() + BTN_HOTKEY_NOR,getPath() + BTN_HOTKEY_PRESS,getPath() + BTN_HOTKEY_PRESS);

	hotkey->setFixedSize(w,90);

	QGridLayout *gl5 =  new QGridLayout;
	gl5->setContentsMargins(0,0,0,0);
	gl5->setSpacing(0);
	gl5->addWidget(m_hotkeyBtn,0,0,1,1);
	hotkey->setLayout(gl5);

	QHBoxLayout *hl3 = new QHBoxLayout;
	hl3->setContentsMargins(0,0,0,0);
	hl3->setSpacing(0);
	hl3->addWidget(basic);
	hl3->addWidget(capture);
	hl3->addWidget(hotkey);
	m_warp->setLayout(hl3);
	
	m_mainSetLayout = new QStackedWidget;
	m_mainSetLayout->setObjectName("SetLayout");
	m_mainSetLayout->setStyleSheet("#SetLayout{border-top:1px solid #444444;}");

	m_basicWidget = new QWidget;
	m_basicWidget->setObjectName("BasicWidget");
	lb1 = new QLabel;
	lb1->setObjectName("StickOnTop");
	lb1->setStyleSheet("#StickOnTop {font-size:16px;}");
	lb1->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	m_stickOnTopWhenPlay = new QRadioButton;
	m_stickOnTopWhenPlay->setProperty("fontStyle",QVariant("fontColor"));
	m_neverStickOnTop = new QRadioButton;
	m_neverStickOnTop->setProperty("fontStyle",QVariant("fontColor"));
	m_alwaysStickOnTop = new QRadioButton;
	m_alwaysStickOnTop->setProperty("fontStyle",QVariant("fontColor"));

	m_stickGroup = new QButtonGroup(this);
	m_stickGroup->addButton(m_stickOnTopWhenPlay,0);
	m_stickGroup->addButton(m_neverStickOnTop,1);
	m_stickGroup->addButton(m_alwaysStickOnTop,2);
	m_stickGroup->setExclusive(true);
	m_neverStickOnTop->setChecked(true);

	QVBoxLayout *vl4 = new QVBoxLayout;
	vl4->setContentsMargins(32,0,0,0);
	vl4->setSpacing(10);
	vl4->addWidget(m_stickOnTopWhenPlay);
	vl4->addWidget(m_neverStickOnTop);
	vl4->addWidget(m_alwaysStickOnTop);

	QVBoxLayout *vl5 = new QVBoxLayout;
	vl5->setContentsMargins(0,0,0,0);
	vl5->setSpacing(16);
	vl5->addWidget(lb1);
	vl5->addLayout(vl4);

	lb2 = new QLabel;
	lb2->setAlignment(Qt::AlignVCenter);
	lb2->setObjectName("LocateBy");
	lb2->setStyleSheet("#LocateBy {font-size:16px;}");
	lb2->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	m_locateByTimestamp = new QRadioButton;
	m_locateByTimestamp->setProperty("fontStyle",QVariant("fontColor"));
	m_locateByFrame = new QRadioButton;
	m_locateByFrame->setProperty("fontStyle",QVariant("fontColor"));
	m_saveListExit = new QCheckBox;
	m_saveListExit->setObjectName("SaveListExit");
	//m_hardWareDecode = new QCheckBox;
	//m_hardWareDecode->setObjectName("HardWareDecode");

	m_basicRestore = new QPushButton(tr("Restore"));
	m_basicRestore->setObjectName("basicRestore");

	QFrame *fr2 = new QFrame;

	QVBoxLayout *vl6 = new QVBoxLayout;
	vl6->setContentsMargins(32,0,0,0);
	vl6->setSpacing(10);
	vl6->addWidget(m_locateByTimestamp);
	vl6->addWidget(m_locateByFrame);
	fr2->setLayout(vl6);

	QVBoxLayout *vl7 = new QVBoxLayout;
	vl7->setContentsMargins(0,0,0,0);
	vl7->setSpacing(15);
	vl7->addWidget(lb2);
	vl7->addWidget(fr2);

	QFrame *fr3 = new QFrame;

	QFrame *fr4 = new QFrame;
	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,32,40,0);
	hl->setSpacing(0);
	hl->addStretch();
	hl->addWidget(m_basicRestore);
	fr4->setLayout(hl);

	QVBoxLayout *vl8 = new QVBoxLayout;
	vl8->setContentsMargins(0,0,0,0);
	vl8->setSpacing(15);
	vl8->addLayout(vl5);
	vl8->addLayout(vl7);
	vl8->addWidget(m_saveListExit);
	vl8->addWidget(fr4);
	//vl8->addWidget(m_hardWareDecode);
	fr3->setLayout(vl8);

	QVBoxLayout *vl9 = new QVBoxLayout;
	vl9->setContentsMargins(50,20,0,0);
	vl9->setSpacing(0);
	vl9->addWidget(fr3);
	vl9->addStretch();

	m_basicWidget->setLayout(vl9);

	m_mainSetLayout->addWidget(m_basicWidget);
//	m_mainSetLayout->setCurrentWidget(m_basicWidget);

	m_captureWidget = new QWidget;

	lb3 = new QLabel;
	lb3->setObjectName("OutPutSetting");
	lb3->setStyleSheet("#OutPutSetting {font-size:16px;}");
	lb3->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	lb4 = new QLabel;
	lb4->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb4->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_picFormat = new QComboBox;
	m_picFormat->setView(new QListView());
	m_picFormat->setFixedSize(102,24);
	m_picFormat->setObjectName("PicFormat");
	
	lb5 = new QLabel;
	lb5->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb5->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_savingPath = new QLineEdit;
	m_savingPath->setFixedSize(160,24);
	m_savingPath->setReadOnly(true);

	m_selectPath = new QPushButton;
	m_selectPath->setFixedSize(40,24);
	m_selectPath->setObjectName("SelectPath");

	QMargins margins = m_savingPath->textMargins();
	m_savingPath->setTextMargins(margins.left() + 5,margins.top(),margins.right(),margins.bottom());

	m_savingPath->setObjectName("SavingPath");

	QHBoxLayout *hl2 = new QHBoxLayout;
	hl2->setContentsMargins(0,0,0,0);
	hl2->setSpacing(10);
	hl2->addWidget(m_savingPath);
	hl2->addWidget(m_selectPath);

	lb6 = new QLabel;
	lb6->setObjectName("ContinuousCaptrue");
	lb6->setStyleSheet("#ContinuousCaptrue {font-size:16px;}");
	lb6->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb6->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	lb7 = new QLabel;
	lb7->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb7->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_mode = new QComboBox;
	m_mode->setView(new QListView());
	m_mode->setObjectName("Mode");
	m_mode->setFixedSize(102,24);

	lb8 = new QLabel;
	lb8->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb8->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_interval = new QSpinBox;
	m_interval->setFixedSize(100,24);
	m_interval->setObjectName("Interval");
	
	lb9 = new QLabel;
	lb9->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb9->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	lb10 = new QLabel;
	lb10->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb10->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_maxPicNum = new QSpinBox;
	m_maxPicNum->setFixedSize(100,24);
	m_maxPicNum->setObjectName("MaxPicNum");

	QHBoxLayout *hl1 = new QHBoxLayout;
	hl1->setContentsMargins(0,0,0,0);
	hl1->setSpacing(10);
	hl1->addWidget(m_interval);
	
	hl1->addWidget(lb9);

	QGridLayout *gl = new QGridLayout;
	gl->addWidget(lb3,0,0,1,1);
	gl->addWidget(lb4,1,0,1,1);
	gl->addWidget(m_picFormat,1,1,1,1);
	gl->addWidget(lb5,2,0,1,1);
	gl->addLayout(hl2,2,1,1,1);
	gl->addWidget(lb6,4,0,1,1);
	gl->addWidget(lb7,5,0,1,1);
	gl->addWidget(m_mode,5,1,1,1);
	gl->addWidget(lb8,6,0,1,1);
	gl->addLayout(hl1,6,1,1,1);
	gl->addWidget(lb10,7,0,1,1);
	gl->addWidget(m_maxPicNum,7,1,1,1);
	gl->setSpacing(10);

	QGroupBox *gb = new QGroupBox;
	gb->setLayout(gl);

	m_captureRestore = new QPushButton(tr("Restore"));
	m_captureRestore->setObjectName("captureRestore");
	QFrame *fr5 = new QFrame;
	QHBoxLayout *hl4 = new QHBoxLayout;
	hl4->setContentsMargins(0,32,0,0);
	hl4->setSpacing(0);
	hl4->addStretch();
	hl4->addWidget(m_captureRestore);
	fr5->setLayout(hl4);

	QVBoxLayout *vl10 = new QVBoxLayout;
	vl10->setContentsMargins(40,10,60,0);
	vl10->setSpacing(0);
	vl10->addWidget(gb);
	vl10->addWidget(fr5);
	vl10->addStretch();
	m_captureWidget->setLayout(vl10);

	m_mainSetLayout->addWidget(m_captureWidget);

	m_hotkeyWidget = new QWidget;

	lb11 = new QLabel;
	lb11->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb11->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_openFileEdit = new CusLineEdit;
	m_openFileEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb12 = new QLabel;
	lb12->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb12->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_fastForwardEdit = new CusLineEdit;
	m_fastForwardEdit->setProperty("LineEditType",QVariant("LineEditStyle"));
	
	lb13 = new QLabel;
	lb13->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb13->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_openDirEdit = new CusLineEdit;
	m_openDirEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb14 = new QLabel;
	lb14->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb14->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_slowForwardEdit = new CusLineEdit;
	m_slowForwardEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb17 = new QLabel;
	lb17->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb17->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_playOrPauseEdit = new CusLineEdit;
	m_playOrPauseEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb19 = new QLabel;
	lb19->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb19->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_stopEdit = new CusLineEdit;
	m_stopEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb21 = new QLabel;
	lb21->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb21->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_frameForwardEdit = new CusLineEdit;
	m_frameForwardEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb22 = new QLabel;
	lb22->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb22->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_captureEdit = new CusLineEdit;
	m_captureEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb24 = new QLabel;
	lb24->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb24->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_normalOrFullScreenEdit = new CusLineEdit;
	m_normalOrFullScreenEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	lb28 = new QLabel;
	lb28->setProperty("LabelFontStyle",QVariant("LabelFontColor"));
	lb28->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_exitEdit = new CusLineEdit;
	m_exitEdit->setProperty("LineEditType",QVariant("LineEditStyle"));

	m_hotkeyRestore = new QPushButton(tr("Restore"));
	m_hotkeyRestore->setObjectName("hotkeyRestore");

	QGridLayout *gl2 = new QGridLayout;
	gl2->setContentsMargins(10,20,40,0);
	gl2->addWidget(lb11,0,0,1,1);
	gl2->addWidget(m_openFileEdit,0,1,1,1);
	gl2->addWidget(lb12,0,2,1,1);
	gl2->addWidget(m_fastForwardEdit,0,3,1,1);
	gl2->addWidget(lb13,1,0,1,1);
	gl2->addWidget(m_openDirEdit,1,1,1,1);
	gl2->addWidget(lb14,1,2,1,1);
	gl2->addWidget(m_slowForwardEdit,1,3,1,1);
	gl2->addWidget(lb17,3,0,1,1);
	gl2->addWidget(m_playOrPauseEdit,3,1,1,1);
	gl2->addWidget(lb19,2,2,1,1);
	gl2->addWidget(m_stopEdit,2,3,1,1);
	gl2->addWidget(lb21,2,0,1,1);
	gl2->addWidget(m_frameForwardEdit,2,1,1,1);
	gl2->addWidget(lb22,3,2,1,1);
	gl2->addWidget(m_captureEdit,3,3,1,1);
	gl2->addWidget(lb24,4,0,1,1);
	gl2->addWidget(m_normalOrFullScreenEdit,4,1,1,1);
	gl2->addWidget(lb28,4,2,1,1);
	gl2->addWidget(m_exitEdit,4,3,1,1);
	gl2->addWidget(m_hotkeyRestore,8,3,1,1);

	m_hotkeyWidget->setLayout(gl2);

	m_mainSetLayout->addWidget(m_hotkeyWidget);

	
	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,25,0,10);
	vl->setSpacing(0);
	vl->addWidget(m_warp);
	vl->addWidget(m_mainSetLayout);
	vl->addWidget(fr);
	setLayout(vl);

	if (index == 0)
	{
		m_basicBtn->statusInit();
	}else if (index == 1)
	{
		m_captureBtn->statusInit();
	}else if (index == 2)
	{
		m_hotkeyBtn->statusInit();
	}
	m_mainSetLayout->setCurrentIndex(index);

	initWindow();
	initSetUi();
	initSetPage();
	
	connect(m_basicBtn,SIGNAL(btnClicked()),this,SLOT(mainLayoutChange()));
	connect(m_captureBtn,SIGNAL(btnClicked()),this,SLOT(mainLayoutChange()));
	connect(m_hotkeyBtn,SIGNAL(btnClicked()),this,SLOT(mainLayoutChange()));
	connect(m_selectPath,SIGNAL(clicked()),this,SLOT(getFilePath()));
	connect(m_basicRestore,SIGNAL(clicked()),this,SLOT(restoreSetting()));
	connect(m_captureRestore,SIGNAL(clicked()),this,SLOT(restoreSetting()));
	connect(m_hotkeyRestore,SIGNAL(clicked()),this,SLOT(restoreSetting()));
}

BasicSetBox::~BasicSetBox(){

}

void BasicSetBox::mainLayoutChange(){
	CusButton *btn = (CusButton *)QObject::sender();
	
	if (btn == m_basicBtn)
	{
		m_mainSetLayout->setCurrentWidget(m_basicWidget);
		m_captureBtn->setBtnStatus();
		m_hotkeyBtn->setBtnStatus();
	}else if (btn == m_captureBtn)
	{
		m_mainSetLayout->setCurrentWidget(m_captureWidget);
		m_hotkeyBtn->setBtnStatus();
		m_basicBtn->setBtnStatus();
	}else if (btn == m_hotkeyBtn)
	{
		m_mainSetLayout->setCurrentWidget(m_hotkeyWidget);
		m_captureBtn->setBtnStatus();
		m_basicBtn->setBtnStatus();
	}
	m_index = m_mainSetLayout->currentIndex();
}

void BasicSetBox::getFilePath(){
	QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
	if (path.isEmpty())
	{
		m_savingPath->setText("C:/HSPlayer");
	}else {
		m_savingPath->setText(path);
	}
}

void BasicSetBox::initWindow(){
	initTitleBar();
	Qt::WindowFlags flags = this->windowFlags();
	this->setWindowFlags(flags | Qt::Window);

	connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkClicked()));
	connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}
void BasicSetBox::initTitleBar(){
	m_titleBar->move(0, 0);
	m_titleBar->setWindowBorderWidth(0);
	m_titleBar->setBackgroundColor(45,45,45);
	m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	m_titleBar->setTitleContent(tr("Remind"));
}
void BasicSetBox::initSetUi(){
	m_okBtn->setText(tr("Yes"));
	m_cancelBtn->setText(tr("No"));
	m_basicBtn->setBtnText(tr("Basic"));
	m_captureBtn->setBtnText(tr("Capture"));
	m_hotkeyBtn->setBtnText(tr("Hotkey"));
	lb1->setText(tr("Stick on Top:"));
	m_stickOnTopWhenPlay->setText(tr("Stick on Top When Playing"));
	m_neverStickOnTop->setText(tr("Never Stick on Top"));
	m_alwaysStickOnTop->setText(tr("Always Stick on Top"));
	m_locateByTimestamp->setText(tr("Locate by Timestamp"));
	m_locateByFrame->setText(tr("Locate by Frame"));
	m_saveListExit->setText(tr("Save File List When Exit"));
	lb2->setText(tr("Locate by:"));
	lb3->setText(tr("Output Settings:"));
	lb4->setText(tr("Format:"));
	lb5->setText(tr("Saving Path:"));
	m_selectPath->setText(tr("Browse"));
	lb6->setText(tr("Continous Capture Setting:"));
	lb7->setText(tr("Mode:"));
	lb8->setText(tr("Interval:"));
	lb9->setText(tr("second"));
	lb10->setText(tr("Max Capture Num:"));
	lb11->setText(tr("Open File:"));
	lb12->setText(tr("Fast Forward:"));
	lb13->setText(tr("Open Directory:"));
	lb14->setText(tr("Slow Forward:"));
	lb17->setText(tr("Play/Pause:"));
	lb19->setText(tr("Stop:"));
	lb21->setText(tr("Frame Forward:"));
	lb22->setText(tr("Capture:"));
	lb24->setText(tr("Normal/Full Screen:"));
	lb28->setText(tr("Exit:"));

	m_picFormat->addItem(tr("jpg"));

	m_mode->addItem(tr("By Time"));
	m_mode->addItem(tr("By Frame"));

	m_interval->setMinimum(1);
	m_maxPicNum->setMinimum(1);
}
void BasicSetBox::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()) , 3 , 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(QColor("#262626")));
	return QWidget::paintEvent(event);
}
void BasicSetBox::setWindowTitle(QString title , int titleFontSize)
{
	m_titleBar->setTitleContent(title,titleFontSize);
}
void BasicSetBox::setButtonType(MsgButtonType buttonType)
{
	switch (buttonType)
	{
	case ONLY_BUTTON_OK:
		{
			m_okBtn->setText(tr("Yes"));
			m_cancelBtn->setVisible(false);
		}
		break;
	case BUTTON_OK_CANCEL:
		{
			m_okBtn->setText(tr("Yes"));
			m_cancelBtn->setText(tr("No"));
		}
		break;
	default:
		break;
	}
}
int BasicSetBox::showMyMessageBox(QWidget* parent, const QString &title,MsgButtonType messageButtonType, bool isModelWindow)
{
	setWindowTitle(title);
	setButtonType(messageButtonType);
	if (isModelWindow)
	{
		return this->exec();
	}
	else
	{
		this->show();
	}
	return -1;
}
int BasicSetBox::exec()
{
	this->setWindowModality(Qt::WindowModal); 
	show();

	m_eventLoop = new QEventLoop(this);
	m_eventLoop->exec();

	return m_chooseResult;
}
void BasicSetBox::onOkClicked()
{
	m_chooseResult = ID_OK_BTN;

	globalBasicSetItem.isStickOnTopWhenPlay = m_stickOnTopWhenPlay->isChecked();
	globalBasicSetItem.isNeverStickOnTop = m_neverStickOnTop->isChecked();
	globalBasicSetItem.isAlwayOnTop = m_alwaysStickOnTop->isChecked();
	globalBasicSetItem.locateByFrame = m_locateByFrame->isChecked();
	globalBasicSetItem.locateByTimestamp = m_locateByTimestamp->isChecked();
	globalBasicSetItem.saveListWhenLeave = m_saveListExit->isChecked();

	globalCaptureSetItem.savePath = m_savingPath->text();
	globalCaptureSetItem.format = m_picFormat->currentIndex();
	globalCaptureSetItem.interval = m_interval->value();
	globalCaptureSetItem.Mode = m_mode->currentIndex();
	globalCaptureSetItem.maxCaptureNum = m_maxPicNum->value();

	globalHotkeySetItem.openFile = m_openFileEdit->text();
	globalHotkeySetItem.fastForward = m_fastForwardEdit->text();
	globalHotkeySetItem.openDir = m_openDirEdit->text();
	globalHotkeySetItem.slowForward = m_slowForwardEdit->text();
	globalHotkeySetItem.playOrPause = m_playOrPauseEdit->text();
	globalHotkeySetItem.stop = m_stopEdit->text();
	globalHotkeySetItem.frameForward = m_frameForwardEdit->text();
	globalHotkeySetItem.capture = m_captureEdit->text();
	globalHotkeySetItem.normalAndFullScreen = m_normalOrFullScreenEdit->text();
	globalHotkeySetItem.exit = m_exitEdit->text();
	
	close();
}
bool BasicSetBox::WriteSetIni(QString path,BASIC_SET_ITEM *basicSet,CAPTURE_SET_ITEM *captureSet,HOTKEY_SET_ITEM *hotkeySet){
	if (path.isEmpty())
	{
		return false;
	}else {
		QSettings iniFile(path,QSettings::IniFormat);
		
		iniFile.beginGroup("basicSet");
		iniFile.setValue("stickOnTopWhenPlay",basicSet->isStickOnTopWhenPlay);
		iniFile.setValue("neverStickOnTop",basicSet->isNeverStickOnTop);
		iniFile.setValue("alwaysOnTop",basicSet->isAlwayOnTop);
		iniFile.setValue("locateByFrame",basicSet->locateByFrame);
		iniFile.setValue("locateByTimestamp",basicSet->locateByTimestamp);
		iniFile.setValue("saveListWhenLeave",basicSet->saveListWhenLeave);
		iniFile.setValue("hardwareDecode",basicSet->hardwareDocode);
		iniFile.endGroup();

		iniFile.beginGroup("captureSet");
		iniFile.setValue("captureFormat",captureSet->format);
		iniFile.setValue("savePath",captureSet->savePath);
		iniFile.setValue("captureMode",captureSet->Mode);
		iniFile.setValue("interval",captureSet->interval);
		iniFile.setValue("maxCaptureNum",captureSet->maxCaptureNum);
		iniFile.endGroup();

		iniFile.beginGroup("hotkeySet");
		iniFile.setValue("openFile",hotkeySet->openFile);
		iniFile.setValue("fastForward",hotkeySet->fastForward);
		iniFile.setValue("openDir",hotkeySet->openDir);
		iniFile.setValue("slowForward",hotkeySet->slowForward);
		iniFile.setValue("openUrl",hotkeySet->openUrl);
		iniFile.setValue("restoreNormalSpeed",hotkeySet->restoreNormalSpeed);
		iniFile.setValue("playOrPause",hotkeySet->playOrPause);
		iniFile.setValue("lastFrame",hotkeySet->lastFrame);
		iniFile.setValue("stop",hotkeySet->stop);
		iniFile.setValue("firstFrame",hotkeySet->firstFrame);
		iniFile.setValue("frameForward",hotkeySet->frameForward);
		iniFile.setValue("capture",hotkeySet->capture);
		iniFile.setValue("frameBackward",hotkeySet->frameBackward);
		iniFile.setValue("normalAndFullScreen",hotkeySet->normalAndFullScreen);
		iniFile.setValue("addVolume",hotkeySet->addVolume);
		iniFile.setValue("lessVolume",hotkeySet->lessVolume);
		iniFile.setValue("repeatAtoB",hotkeySet->repeatAtoB);
		iniFile.setValue("exit",hotkeySet->exit);
		iniFile.endGroup();
			
		return true;
	}
}
bool BasicSetBox::readSetIni(QString path){
	if (path.isEmpty())
	{
		return false;
	}else {
		QSettings iniFile(path,QSettings::IniFormat);
		QString GroupName = "basicSet/";
		globalBasicSetItem.isStickOnTopWhenPlay = iniFile.value(GroupName + QString("stickOnTopWhenPlay")).toBool();
		globalBasicSetItem.isNeverStickOnTop = iniFile.value(GroupName + QString("neverStickOnTop")).toBool();
		globalBasicSetItem.isAlwayOnTop = iniFile.value(GroupName + QString("alwaysOnTop")).toBool();
		globalBasicSetItem.locateByFrame = iniFile.value(GroupName + QString("locateByFrame")).toBool();
		globalBasicSetItem.locateByTimestamp = iniFile.value(GroupName + QString("locateByTimestamp")).toBool();
		globalBasicSetItem.saveListWhenLeave = iniFile.value(GroupName + QString("saveListWhenLeave")).toBool();
		//globalBasicSetItem.hardwareDocode = iniFile.value(GroupName + QString("hardwareDecode")).toBool();

		GroupName = "captureSet/";
		globalCaptureSetItem.format = iniFile.value(GroupName + QString("captureFormat")).toInt();
		globalCaptureSetItem.savePath = iniFile.value(GroupName + QString("savePath")).toString();
		globalCaptureSetItem.Mode = iniFile.value(GroupName + QString("captureMode")).toInt();
		globalCaptureSetItem.interval = iniFile.value(GroupName + QString("interval")).toInt();
		globalCaptureSetItem.maxCaptureNum = iniFile.value(GroupName + QString("maxCaptureNum")).toInt();

		GroupName = "hotkeySet/";
		globalHotkeySetItem.openFile = iniFile.value(GroupName + QString("openFile")).toString();
		globalHotkeySetItem.fastForward = iniFile.value(GroupName + QString("fastForward")).toString();
		globalHotkeySetItem.openDir = iniFile.value(GroupName + QString("openDir")).toString();
		globalHotkeySetItem.slowForward = iniFile.value(GroupName + QString("slowForward")).toString();
		globalHotkeySetItem.openUrl = iniFile.value(GroupName + QString("openUrl")).toString();
		globalHotkeySetItem.restoreNormalSpeed = iniFile.value(GroupName + QString("openUrl")).toString();
		globalHotkeySetItem.playOrPause = iniFile.value(GroupName + QString("playOrPause")).toString();
		globalHotkeySetItem.lastFrame = iniFile.value(GroupName + QString("lastFrame")).toString();
		globalHotkeySetItem.stop = iniFile.value(GroupName + QString("stop")).toString();
		globalHotkeySetItem.firstFrame = iniFile.value(GroupName + QString("firstFrame")).toString();
		globalHotkeySetItem.frameForward = iniFile.value(GroupName + QString("frameForward")).toString();
		globalHotkeySetItem.capture = iniFile.value(GroupName + QString("capture")).toString();
		globalHotkeySetItem.frameBackward = iniFile.value(GroupName + QString("frameBackward")).toString();
		globalHotkeySetItem.normalAndFullScreen = iniFile.value(GroupName + QString("normalAndFullScreen")).toString();
		globalHotkeySetItem.addVolume = iniFile.value(GroupName + QString("addVolume")).toString();
		globalHotkeySetItem.lessVolume = iniFile.value(GroupName + QString("lessVolume")).toString();
		globalHotkeySetItem.repeatAtoB = iniFile.value(GroupName + QString("repeatAtoB")).toString();
		globalHotkeySetItem.exit = iniFile.value(GroupName + QString("exit")).toString();

		return true;
	}
}
void BasicSetBox::initSetPage(){
	readSetIni(getPath() + BASICSET_INI);

	m_stickOnTopWhenPlay->setChecked(globalBasicSetItem.isStickOnTopWhenPlay);
	m_neverStickOnTop->setChecked(globalBasicSetItem.isNeverStickOnTop);
	m_alwaysStickOnTop->setChecked(globalBasicSetItem.isAlwayOnTop);
	m_locateByFrame->setChecked(globalBasicSetItem.locateByFrame);
	m_locateByTimestamp->setChecked(globalBasicSetItem.locateByTimestamp);
	m_saveListExit->setChecked(globalBasicSetItem.saveListWhenLeave);

	m_picFormat->setCurrentIndex(globalCaptureSetItem.format);
	m_savingPath->setText(globalCaptureSetItem.savePath);
	m_mode->setCurrentIndex(globalCaptureSetItem.Mode);
	m_interval->setValue(globalCaptureSetItem.interval);
	m_maxPicNum->setValue(globalCaptureSetItem.maxCaptureNum);

	m_openFileEdit->setText(globalHotkeySetItem.openFile);
	m_fastForwardEdit->setText(globalHotkeySetItem.fastForward);
	m_openDirEdit->setText(globalHotkeySetItem.openDir);
	m_slowForwardEdit->setText(globalHotkeySetItem.slowForward);
	m_playOrPauseEdit->setText(globalHotkeySetItem.playOrPause);
	m_stopEdit->setText(globalHotkeySetItem.stop);
	m_frameForwardEdit->setText(globalHotkeySetItem.frameForward);
	m_captureEdit->setText(globalHotkeySetItem.capture);
	m_normalOrFullScreenEdit->setText(globalHotkeySetItem.normalAndFullScreen);
	m_exitEdit->setText(globalHotkeySetItem.exit);
}
void BasicSetBox::onCancelClicked()
{
	m_chooseResult = ID_CANCEL_BTN;
	close();
}

void BasicSetBox::closeEvent(QCloseEvent *event)
{
	if (m_eventLoop != NULL)
	{
		m_eventLoop->exit();
	}
	event->accept();
}
void BasicSetBox::restoreSetting(){
	QPushButton *btn = (QPushButton *)QObject::sender();
		if (btn == m_basicRestore)
		{
			m_stickOnTopWhenPlay->setChecked(false);
			m_neverStickOnTop->setChecked(true);
			m_alwaysStickOnTop->setChecked(false);
			m_locateByFrame->setChecked(true);
			m_locateByTimestamp->setChecked(false);
			m_saveListExit->setChecked(true);
		}else if (btn == m_captureRestore)
		{
			m_picFormat->setCurrentIndex(0);
			m_mode->setCurrentIndex(0);
			m_savingPath->setText("C:/HSPlayer");
			m_interval->setValue(1);
			m_maxPicNum->setValue(5);
		}else if (btn == m_hotkeyRestore)
		{
			/*m_openDirEdit->setText("Ctrl+O");
			m_fastForwardEdit->setText("Ctrl+Right");
			m_openDirEdit->setText("Ctrl+D");
			m_slowForwardEdit->setText("Ctrl+Left");
			m_fastForwardEdit->setText("Right");
			m_stopEdit->setText("ctrl+S");
			m_playOrPauseEdit->setText("Space");
			m_captureEdit->setText("F11");
			m_normalOrFullScreenEdit->setText("Ctrl+F");
			m_exitEdit->setText("Ctrl+W");*/
		}
}