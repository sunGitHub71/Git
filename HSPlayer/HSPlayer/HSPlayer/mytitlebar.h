#pragma once
#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

enum ButtonType
{
	MIN_BUTTON = 0,
	MIN_MAX_BUTTON ,
	ONLY_CLOSE_BUTTON ,
	MAX_BUTTON
};

class MyTitleBar : public QWidget
{
	Q_OBJECT

public:
	MyTitleBar(QWidget *parent = NULL);
	~MyTitleBar();

	
	void setBackgroundColor(int r, int g, int b);
	void setTitleIcon(QString filePath , QSize IconSize = QSize(25 , 25));
	void setTitleContent(QString titleContent , int titleFontSize = 9);
	void setTitleWidth(int width);
	void setButtonType(ButtonType buttonType);
	void setWindowBorderWidth(int borderWidth);
	void saveRestoreInfo(const QPoint point, const QSize size);
	void getRestoreInfo(QPoint& point, QSize& size);

private:
	void paintEvent(QPaintEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void initControl();
	void initConnections();

signals:
	void signalButtonMinClicked();
	void signalButtonRestoreClicked();
	void signalButtonMaxClicked();
	void signalButtonCloseClicked();

private slots:
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

public:
	bool m_isFull;			//全屏标志，全屏时候界面不可拖动 

private:
	QLabel* m_pIcon;				
	QLabel* m_pTitleContent;		
	QPushButton* m_pButtonMin;		
	QPushButton* m_pButtonRestore;	
	QPushButton* m_pButtonMax;			
	QPushButton* m_pButtonClose;

	int m_colorR;
	int m_colorG;
	int m_colorB;

	QPoint m_restorePos;
	QSize m_restoreSize;
	bool m_isPressed;
	QPoint m_startMovePos;
	QString m_titleContent;
	ButtonType m_buttonType;
	int m_windowBorderWidth;
};

#endif // MYTITLEBAR_H
