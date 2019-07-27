#pragma once
#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>

enum MoveDir
{
	RIGHT_TOP = 0,				
	RIGHT_BOTTOM,
	LEFT_BOTTOM,
	LEFT_TOP
};

class VideoWidget : public QWidget {
	Q_OBJECT
public:
	VideoWidget(QWidget *parent = 0);
	~VideoWidget();
	QRect* selectedWndRect();
	QRect getCurSelectedRect();
	int getDrawDir();
	void setDraw(bool isDraw){m_isDraw = isDraw;};
	bool getDraw(){return m_isDraw;};
	void setShowInfo(QString showInfo){m_showInfo = showInfo;};
	QString getShowInfo(){return m_showInfo;};
	void setIsShowInfo(bool isShowInfo){m_isShowInfo = isShowInfo;};
	bool getIsShowInfo(){return m_isShowInfo;};
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
public:
	int index;
private:
	bool m_isPressed;
	QPoint m_start;
	QPoint m_end;

	int x;
	int y;
	int w;
	int h;

	QRect *m_wndRect;
	QRect m_CurWndRect;
	MoveDir m_dir;

	bool m_isDraw;
	QString m_showInfo;
	bool m_isShowInfo;

signals:
	void drawEnd();
	void toolBarShow(VideoWidget *item,QPoint pos);
};

#endif