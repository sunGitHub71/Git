#pragma once
#ifndef STRETCHWND_H
#define STRETCHWND_H
#include <QWidget>

#define  PADDING 15
typedef enum Direction { 
	RIGHTBOTTOM = 0, 
	NONE
};

class StretchWnd : public QWidget{
	Q_OBJECT
public:
	StretchWnd(QWidget *parent = 0);
	~StretchWnd();
	void region(const QPoint &cursorGlobalPoint);
	QPoint getPoint();
protected:
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
private:
	bool isLeftPressDown;  
	QPoint dragPosition;   
	Direction dir;
	int	m_curWidth;
	int m_curHeight;

};

#endif