#pragma once
#ifndef OPENURL_H
#define OPENURL_H

#include <QWidget>
#include <QLabel>
#include <QEventLoop>
#include <QComboBox>
#include <QListView>
#include <QStringListModel>
#include "basewindow.h"

class PlayList;

enum Result
{
	OK = 0,			
	CANCEL					
};

class openUrl : public BaseWindow {
	Q_OBJECT
public:
	openUrl(QWidget *parent = 0);
	~openUrl();
	void setPlaylist(PlayList * playlist){m_playlist = playlist;};
public:
	void setWindowTitle(QString title, int titleFontSize = 10);
	void isPlaySuccess(bool isPlaySuccess){m_isPlaySuccess = isPlaySuccess;};
	void setComboboxItem();
	int showMyMessageBox(QWidget* parent,PlayList * thePlaylist ,const QString &title, bool isModelWindow);
private:
	void initWindow();
	void initTitleBar();
	int exec();

	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);

private slots:
	void onOkClicked();
	void onCancelClicked();
	//void onTest();
private:
	QPushButton *m_okBtn;
	QPushButton *m_cancelBtn;
	QEventLoop *m_eventLoop;
	Result m_chooseResult;
	QLabel *m_url;
	QLabel *m_connectionMode;
	QLabel *m_portNo;
	QLabel *m_example;
	QComboBox *m_urlInput;
	QComboBox *m_connectionModeSel;
	QComboBox *m_portNoInput;
	QListView *m_listItem;
	QStringListModel *m_model;
	bool m_isPlaySuccess;
	PlayList * m_playlist;
signals:
	void signalsTest();
};

#endif