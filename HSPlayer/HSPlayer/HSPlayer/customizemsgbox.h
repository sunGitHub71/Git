#ifndef CUSTOMIZEMSGBOX_H
#define CUSTOMIZEMSGBOX_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QEventLoop>
#include "basewindow.h"

enum ChoseResult
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

class CustomizeMsgBox : public BaseWindow {
	Q_OBJECT

public:
	CustomizeMsgBox(QWidget *parent = NULL);
	~CustomizeMsgBox();

public:
	void setWindowTitle(QString title, int titleFontSize = 10);
	void setContentText(QString contentText);
	void setButtonType(MessageButtonType buttonType);
	void setMessageContent(QString messageContent);
	int static showMyMessageBox(QWidget* parent, const QString &title,const QString &contentText , MessageButtonType messageButtonType , bool isModelWindow);

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
	ChoseResult m_chooseResult;
	QPushButton *m_okBtn;
	QPushButton *m_cancelBtn;
	QLabel *m_contentLb;
};

#endif