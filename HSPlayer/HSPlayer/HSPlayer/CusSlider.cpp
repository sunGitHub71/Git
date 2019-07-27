#include "cusslider.h"
#include <QDebug>
#include <QMouseEvent>

CusSlider::CusSlider(QWidget *parent)
	:QSlider(parent)
	,m_isPressed(false)
{
	setMaximum(100);
	setMinimum(0);
	setValue(0);
}

CusSlider::~CusSlider(){

}

//µ¥»÷
void CusSlider::mousePressEvent(QMouseEvent *event){
	
	m_isPressed = true;
}

void CusSlider::mouseMoveEvent(QMouseEvent *event){
	if (m_isPressed)
	{
		int pos = maximum() - (event->pos().y())*maximum()/height();
		setValue(pos);
		qDebug() << pos << endl;
	}
}

void CusSlider::mouseReleaseEvent(QMouseEvent *event){
	m_isPressed = false;
}