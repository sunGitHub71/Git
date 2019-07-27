#include "cusbutton.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPainter>

CusButton::CusButton(QString normal,QString hover,QString pressed,QWidget *parent)
	:QWidget(parent){
	
	setFixedSize(70,60);

	m_btnStatus = NORMAL;

	m_normalIcon.load(normal);
	m_hoverIcon.load(hover);
	m_pressedIcon.load(pressed);

	m_normal = normal;
	m_hover = hover;
	m_pressed = pressed;

	m_btnWrap = new QFrame;
	m_btnIcon = new QLabel;
	m_btnIcon->setFixedSize(70,m_normalIcon.height());
	m_btnIcon->setObjectName("btnIcon");

	m_btnLabel = new QLabel(tr("Label"));
	m_btnLabel->setFixedWidth(70);
	m_btnLabel->setAlignment(Qt::AlignCenter);
	m_btnLabel->adjustSize();

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_btnIcon);
	vl->addWidget(m_btnLabel);

	QGridLayout *gl = new QGridLayout;
	gl->setContentsMargins(0,0,0,0);
	gl->setSpacing(0);
	gl->addLayout(vl,0,0,1,1);
	setLayout(gl);

	m_isPressed = false;
}
CusButton::~CusButton(){

}
void CusButton::enterEvent(QEvent *event){
	m_btnStatus = HOVER;
	update();

	QWidget::enterEvent(event);
}
void CusButton::leaveEvent(QEvent *event){
	if (!m_isPressed)
	{
		m_btnStatus = NORMAL;
		update();
	}
	
	QWidget::leaveEvent(event);
}
void CusButton::mousePressEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton)
	{

		m_btnStatus = PRESSED;
		update();

		m_isPressed = true;

		emit btnClicked();
	}

	QWidget::mousePressEvent(event);
}
void CusButton::mouseReleaseEvent(QMouseEvent *event){

}
void CusButton::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	
	switch(m_btnStatus){
		case NORMAL:
			m_btnIcon->setStyleSheet("background-image:url(" + m_normal + ")");
			m_btnLabel->setStyleSheet("color:#555555");
			break;
		case HOVER:
			m_btnIcon->setStyleSheet("background-image:url(" + m_hover + ")");
			m_btnLabel->setStyleSheet("color:#d2bc00");
			break;
		case PRESSED:
			m_btnIcon->setStyleSheet("background-image:url(" + m_pressed + ")");
			m_btnLabel->setStyleSheet("color:#d2bc00");
			break;
	}

	painter.restore();

	QWidget::paintEvent(event);
}
void CusButton::setBtnText(QString text){
	if (text != "")
	{
		m_btnLabel->setText(text);
	}else {
		m_btnLabel->setText(tr("Label"));
	}
}
void CusButton::setBtnStatus(){
	m_btnStatus = NORMAL;
	m_isPressed = false;
	update();
}
void CusButton::statusInit(){
	m_isPressed = true;
	m_btnStatus = PRESSED;
	update();
}
