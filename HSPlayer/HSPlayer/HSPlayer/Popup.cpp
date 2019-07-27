#include "popup.h"
#include "resource_tr.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

PopupWindow::PopupWindow(int index,QWidget *parent)
	:QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

	m_popupWrap = new QWidget;
	m_popupWrap->setFixedSize(219,51);
	m_popupWrap->setObjectName("PopupWrap");
	m_popupWrap->setStyleSheet("#PopupWrap{background-color:#4d4d4d;border:1px solid #666666;}");

	PopupItem *item = NULL;
	for (int i = 0;i < BTNNUM;++i)
	{
		item = new PopupItem(m_popupWrap);
		item->index = i;

		item->m_btn->setObjectName(QString("WindowDivision%1").arg(i + 1));
		item->m_lb->setText(QString("%1x%1").arg(i + 1));

		popupItem[i] = item;
		popupItem[i]->m_lb->setStyleSheet("margin-bottom:16px;font-size:12px;color:#cccccc;");
		popupItem[i]->setGeometry(20+(50*i),8,34,50);
	}
	QString viewIconPath = "";
	if (index == 0)
	{
		viewIconPath = getPath() + BTN_1_PRESS;
	}else if (index == 1)
	{
		viewIconPath = getPath() + BTN_2_PRESS;
	}else if (index == 2)
	{
		viewIconPath = getPath() + BTN_3_PRESS;
	}else if (index == 3)
	{
		viewIconPath = getPath() + BTN_4_PRESS;
	}
	popupItem[index]->m_btn->setStyleSheet("background-image:url(" + viewIconPath + ");");

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_popupWrap);
	setLayout(vl);
}

PopupWindow::~PopupWindow(){

}

void PopupWindow::mousePressEvent(QMouseEvent *event){
	setAttribute(Qt::WA_NoMouseReplay);
	return QWidget::mousePressEvent(event);
}

void PopupWindow::setCurrentItem(QPushButton *Btn)
{
	for (int i = 0;i < BTNNUM;++i)
	{
		popupItem[i]->m_btn->setStyleSheet(QString("#WindowDivision%1{background-image:url(" + getPath() + "/Skin/player/viewSelect/" + "btn_%2.png" + ");}").arg(i+1).arg(i+1));
		if (Btn == popupItem[i]->m_btn)
		{
			popupItem[i]->m_btn->setStyleSheet(QString("#WindowDivision%1{background-image:url(" + getPath() + "/Skin/player/viewSelect/" + "btn_%2_press.png" + ");}").arg(popupItem[i]->index + 1).arg(popupItem[i]->index + 1));
		}
	}
}
