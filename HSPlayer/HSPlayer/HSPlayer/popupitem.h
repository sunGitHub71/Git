#pragma  once
#ifndef POPUPITEM_H
#define POPUPITEM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class PopupItem : public QWidget {
	Q_OBJECT
public:
	PopupItem(QWidget *parent = NULL);
	~PopupItem();
	//virtual void mousePressEvent(QMouseEvent *event);

public:
	QPushButton *m_btn;
	QLabel *m_lb;
	int index;
};

#endif