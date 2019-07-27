#pragma once
#ifndef ABOUTMSGBOX_H
#define ABOUTMSGBOX_H

#include <QWidget>
#include <QEventLoop>
#include "basewindow.h"

enum ChosseResult
{
	ID_OK = 0,			
	ID_CANCEL					
};
enum MessageButtonType
{
	BUTTON_OK = 0,		
	BUTTON_OK_AND_CANCEL,		
	BUTTON_CLOSE			
};

class AboutMsgBox : public BaseWindow{
	Q_OBJECT
public:
	AboutMsgBox(QWidget *parent = 0);
	~AboutMsgBox();
public:
	void setWindowTitle(QString title, int titleFontSize = 10);
	void setContentText(QString contentText);
	void setVersionText(QString versionText);
	void setButtonType(MessageButtonType buttonType);
	int static showMyMessageBox(QWidget* parent, const QString &title,const QString &contentText , MessageButtonType messageButtonType , bool isModelWindow,QString versionText);
private:
	void initWindow();
	void initTitleBar();
	int exec();

	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);

private slots:
	void onOkClicked();
	void onCancelClicked();

private:
	QEventLoop* m_eventLoop;
	ChosseResult m_chooseResult;
	QPushButton *m_okBtn;
	QPushButton *m_cancelBtn;
	QLabel *m_contentLb;
	QLabel *m_versionLb;
	QLabel *m_msgIcon;
};

#endif