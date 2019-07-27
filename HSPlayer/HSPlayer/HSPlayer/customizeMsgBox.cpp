#include "customizemsgbox.h"
#include "resource_tr.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QCloseEvent>

CustomizeMsgBox::CustomizeMsgBox(QWidget *parent)
	:BaseWindow(parent){

		setFixedSize(300,150);
		m_okBtn = new QPushButton(tr("Yes"),this);
		m_cancelBtn = new QPushButton(tr("No"),this);
		m_contentLb = new QLabel(this);
		m_contentLb->setWordWrap(true);
		m_contentLb->setAlignment(Qt::AlignCenter);
		m_contentLb->setStyleSheet("color:#cccccc;");
	
		QVBoxLayout *vl2 = new QVBoxLayout;
		vl2->setContentsMargins(0,0,0,0);
		vl2->setSpacing(0);
		vl2->addWidget(m_contentLb);

		QFrame *f1 = new QFrame;
		f1->setObjectName("f1");
		QHBoxLayout *hl = new QHBoxLayout;
		hl->setContentsMargins(10,0,10,0);
		hl->setSpacing(20);
		hl->addLayout(vl2);
		f1->setLayout(hl);

		m_okBtn->setObjectName("pButtonOk");
		m_okBtn->setStyleSheet("#pButtonOk{background-image:url(" + getPath() + BTN_COMFIRM_NOR + ");} #pButtonOk:hover {background-image:url(" + getPath() + BTN_COMFIRM_PRESS + ")}");
		m_okBtn->setMinimumSize(QSize(70, 25));
		m_okBtn->setMaximumSize(QSize(70, 25));

		m_cancelBtn->setObjectName("pButtonCancel");
		m_cancelBtn->setStyleSheet("#pButtonCancel{background-image:url(" + getPath() + BTN_CANCEL_NOR + ");} #pButtonCancel:hover {background-image:url(" + getPath() + BTN_CANCEL_PRESS + ")}");
		m_cancelBtn->setMinimumSize(QSize(70, 25));
		m_cancelBtn->setMaximumSize(QSize(70, 25));

		QFrame *f2 = new QFrame;
		f2->setFixedHeight(38);
		f2->setObjectName("f2");
		QHBoxLayout *hl1 = new QHBoxLayout;
		hl1->setContentsMargins(0,0,10,10);
		hl1->setSpacing(10);
		hl1->addStretch();
		hl1->addWidget(m_okBtn);
		hl1->addWidget(m_cancelBtn);
		f2->setLayout(hl1);

		QVBoxLayout *vl = new QVBoxLayout;
		vl->setContentsMargins(0,25,0,0);
		vl->setSpacing(0);
		vl->addWidget(f1);
		vl->addWidget(f2);
		setLayout(vl);

		initWindow();
}

CustomizeMsgBox::~CustomizeMsgBox(){

}

void CustomizeMsgBox::initWindow(){
	initTitleBar();
	Qt::WindowFlags flags = this->windowFlags();
	this->setWindowFlags(flags | Qt::Window);

	connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkClicked()));
	connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

void CustomizeMsgBox::initTitleBar(){
	m_titleBar->move(0, 0);
	m_titleBar->setWindowBorderWidth(0);
	m_titleBar->setBackgroundColor(45,45,45);
	m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	m_titleBar->setTitleContent(tr("Remind"));
}

void CustomizeMsgBox::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()) , 3 , 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(QColor("#262626")));
	return QWidget::paintEvent(event);
}

void CustomizeMsgBox::setWindowTitle(QString title , int titleFontSize)
{
	m_titleBar->setTitleContent(title, titleFontSize);
}

void CustomizeMsgBox::setContentText(QString contentText)
{
	m_contentLb->setText(contentText);
}
void CustomizeMsgBox::setButtonType(MessageButtonType buttonType)
{
	switch (buttonType)
	{
	case BUTTON_OK:
		{
			m_okBtn->setText(tr("Yes"));
			m_cancelBtn->setVisible(false);
		}
		break;
	case BUTTON_OK_AND_CANCEL:
		{
			m_okBtn->setText(tr("Yes"));
			m_cancelBtn->setText(tr("No"));
		}
		break;
	default:
		break;
	}
}
int CustomizeMsgBox::showMyMessageBox(QWidget* parent, const QString &title, const QString &contentText,MessageButtonType messageButtonType, bool isModelWindow)
{
	CustomizeMsgBox * myMessageBox = new CustomizeMsgBox(parent);
	myMessageBox->setWindowTitle(title);
	myMessageBox->setContentText(contentText);
	myMessageBox->setButtonType(messageButtonType);
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

int CustomizeMsgBox::exec()
{
	this->setWindowModality(Qt::WindowModal); 
	show();

	m_eventLoop = new QEventLoop(this);
	m_eventLoop->exec();

	return m_chooseResult;
}

void CustomizeMsgBox::onOkClicked()
{
	m_chooseResult = ID_OK;
	close();
}

void CustomizeMsgBox::onCancelClicked()
{
	m_chooseResult = ID_CANCEL;
	close();
}

void CustomizeMsgBox::closeEvent(QCloseEvent *event)
{
	if (m_eventLoop != NULL)
	{
		m_eventLoop->exit();
	}
	event->accept();
}