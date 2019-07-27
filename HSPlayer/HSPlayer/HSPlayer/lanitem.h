#pragma once
#ifndef LANITEM_H
#define LANITEM_H

#include <QAction>

class lanItem : public QAction{
	Q_OBJECT
public:
	lanItem(QWidget *parent = NULL);
	~lanItem();
public:
	int index;
};

#endif