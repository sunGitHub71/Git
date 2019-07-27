#pragma once
#ifndef CUSSLIDER_H
#define CUSSLIDER_H

#include <QWidget>
#include <QSlider>

class CusSlider : public QSlider{
	Q_OBJECT
public:
	CusSlider(QWidget *parent = NULL);
	~CusSlider();
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
private:
	bool m_isPressed;
	//int pos;
};

#endif
