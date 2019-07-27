#include "popupitem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

PopupItem::PopupItem(QWidget *parent)
	:QWidget(parent)
{
	m_btn = new QPushButton(this);
	m_lb = new QLabel(this);
	m_lb->setAlignment(Qt::AlignCenter);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_btn);
	vl->addWidget(m_lb);

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setContentsMargins(0,0,0,0);
	vl1->setSpacing(0);
	vl1->addLayout(vl);
	setLayout(vl1);

	index = -1;
}

PopupItem::~PopupItem(){

}