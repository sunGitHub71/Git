#pragma once
#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QPushButton>
#include "popupitem.h"

#define BTNNUM 4

class PopupWindow : public QWidget {
	Q_OBJECT
public:
	PopupWindow(int index = 0,QWidget *parent = 0);
	~PopupWindow();
	virtual void mousePressEvent(QMouseEvent *event);
	void setCurrentItem(QPushButton *Btn);

public:
	QWidget *m_popupWrap;

	PopupItem *popupItem[BTNNUM];

private slots:
	//void setCurrentItem();
};

#endif 