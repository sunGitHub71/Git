#pragma once
#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget{
	Q_OBJECT
public:
	ListWidget(QWidget *parent = NULL);
	~ListWidget();
protected:
	void mousePressEvent(QMouseEvent *event);
private:
	int index;
};

#endif