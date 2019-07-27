#include "stretchwnd.h"
#include "resource_tr.h"
#include <QMouseEvent>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QStyle>

StretchWnd::StretchWnd(QWidget *parent)
	:QWidget(parent){
	setFixedHeight(14);
	setStyleSheet("background-color:#262626;border-right:1px solid #000000;border-bottom:1px solid #000000;");

	isLeftPressDown = false;
	this->dir = NONE;
	this->setMouseTracking(true);
	//m_curWidth = 920;
	//m_curHeight = 646;
}
StretchWnd::~StretchWnd(){

}
void StretchWnd::paintEvent(QPaintEvent *event){
	QStyleOption opt;

	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	if (!parentWidget()->isMaximized())
	{
		QPainter painter(this);
		QRect iconRect(width() - 14,0,12,12);
		QPixmap icon(getPath() + BTN_ICON);
		painter.drawPixmap(iconRect,icon);
	}
	QWidget::paintEvent(event);
}
void StretchWnd::region(const QPoint &cursorGlobalPoint){
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (!parentWidget()->isMaximized())
	{
		if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
			dir = RIGHTBOTTOM;
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}else {
			dir = NONE;
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
}
void StretchWnd::mouseReleaseEvent(QMouseEvent *event){
	if(event->button() == Qt::LeftButton) {
		isLeftPressDown = false;
		if(dir != NONE) {
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
}
void StretchWnd::mousePressEvent(QMouseEvent *event){
	switch(event->button()) {
	case Qt::LeftButton:
		isLeftPressDown = true;
		if(dir != NONE) {
			this->mouseGrabber();
		} else {
			dragPosition = event->globalPos() - this->frameGeometry().topLeft();
		}
		break;
	default:
		QWidget::mousePressEvent(event);
	}
}
void StretchWnd::mouseMoveEvent(QMouseEvent *event){
	QPoint gloPoint = event->globalPos();
	QRect rect = this->parentWidget()->rect();
	QPoint parPoint = this->parentWidget()->pos();
	QPoint tl = parPoint;
	QPoint rb = mapToGlobal(rect.bottomRight());

	if(!isLeftPressDown) {
		this->region(gloPoint);
	} else {
		if(dir != NONE) {
			QRect rMove(tl, rb);
			if (!this->parentWidget()->isMaximized())
			{
				if (dir == RIGHTBOTTOM)
				{
					m_curWidth = gloPoint.x() - tl.x();
					m_curHeight = gloPoint.y() - tl.y();
					
					rMove.setWidth(m_curWidth);
					rMove.setHeight(m_curHeight);
				}
				this->parentWidget()->setGeometry(rMove);
				this->parentWidget()->repaint();
			}
		} 
	}
}
QPoint StretchWnd::getPoint(){
	QPoint point(m_curWidth,m_curHeight);

	return point;
}