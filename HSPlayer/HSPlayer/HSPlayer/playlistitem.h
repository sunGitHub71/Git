#pragma once
#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QWidget>
#include <QLabel>

class PlayListItem : public QWidget {
	Q_OBJECT
public:
	PlayListItem(QWidget *parent = NULL);
	~PlayListItem();
	void setListItemText(QString filePath,QString videoTotalTime);
private:
	QWidget *m_container;
	QLabel *m_leftIcon;
	QLabel *m_fileName;
	QLabel *m_totalTime;
	QLabel *m_fileSize;
	QFrame *m_rightFrame;
	long videoTotalTime;
};

#endif