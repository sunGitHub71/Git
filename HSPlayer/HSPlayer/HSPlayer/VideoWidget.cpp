#include "videowidget.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

VideoWidget::VideoWidget(QWidget *parent)
	:QWidget(parent)
{

	m_isPressed = false;
	m_wndRect = new QRect(0,0,0,0);
	QRect m_CurWndRect(0,0,0,0); 

	m_isDraw = false;
	m_isShowInfo = false;

	setMouseTracking(true);
}
VideoWidget::~VideoWidget(){

}
void VideoWidget::mousePressEvent(QMouseEvent *event){

	x = 0;
	y = 0;
	w = 0;
	h = 0;

	m_start = event->pos();
	m_isPressed = true;

	x = m_start.x();
	y = m_start.y();

	QWidget::mousePressEvent(event);
}
void VideoWidget::mouseMoveEvent(QMouseEvent *event){
	if (m_isPressed)
	{
		m_end = event->pos();

		w = qAbs(x - m_end.x());
		h = qAbs(y - m_end.y());

		if (x - m_end.x() < 0 && y - m_end.y() > 0)
		{
			m_dir = RIGHT_TOP;	
		}else if (x - m_end.x() < 0 && y - m_end.y() < 0)
		{
			m_dir = RIGHT_BOTTOM;	
		}else if (x - m_end.x() > 0 && y - m_end.y() < 0)
		{
			m_dir = LEFT_BOTTOM;
		}else if (x - m_end.x() > 0 && y - m_end.y() > 0)
		{
			m_dir = LEFT_TOP;
		}
		m_wndRect->setRect(x,y,w,h);	
	}
	
	emit toolBarShow(this,event->pos());
	
	QWidget::mouseMoveEvent(event);
}
void VideoWidget::mouseReleaseEvent(QMouseEvent *event){
	m_isPressed = false;
	if (m_dir == RIGHT_BOTTOM)
	{
		m_CurWndRect.setRect(x,y,w,h);
	}else if (m_dir == LEFT_TOP)
	{
		m_CurWndRect.setRect(m_end.x(),m_end.y(),w,h);
	}else if (m_dir == RIGHT_TOP)
	{
		m_CurWndRect.setRect(m_end.x() - w,m_end.y(),w,h);
	}else if (m_dir == LEFT_BOTTOM)
	{
		m_CurWndRect.setRect(m_end.x(),m_end.y() - h,w,h);
	}
	
	m_wndRect->setRect(0,0,0,0);

	emit drawEnd();

	QWidget::mouseReleaseEvent(event);
}
QRect * VideoWidget::selectedWndRect(){

	return m_wndRect;
}
int VideoWidget::getDrawDir(){
	
	return m_dir;
}
QRect  VideoWidget::getCurSelectedRect(){
		
	return m_CurWndRect;
}