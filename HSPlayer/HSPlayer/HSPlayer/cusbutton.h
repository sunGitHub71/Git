#pragma once
#ifndef CUSBUTTON_H
#define CUSBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <Qlabel>

enum BtnStatus {
	HOVER = 0,
	PRESSED,
	NORMAL
};

class CusButton : public QWidget {
	Q_OBJECT
public:
	CusButton(QString normal,QString hover,QString pressed,QWidget *parent = 0);
	~CusButton();

protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

public:
	void setBtnText(QString text);
	//void setBtnStatus(bool isPressed){m_isPressed = isPressed;};
	void setBtnStatus();
	void statusInit();
public:
	int index;
signals:
	void btnClicked();
private:
	QFrame *m_btnWrap;
	QLabel *m_btnIcon;
	QLabel *m_btnLabel;
	QPixmap m_normalIcon;
	QPixmap m_hoverIcon;
	QPixmap m_pressedIcon;
	BtnStatus m_btnStatus;

	QString m_normal;
	QString m_hover;
	QString m_pressed;

	bool m_isPressed;
};

#endif