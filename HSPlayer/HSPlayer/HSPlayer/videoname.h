#pragma once
#ifndef VIDEONAME_H
#define VIDEONAME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class VideoName : public QWidget {
	Q_OBJECT

public:
	VideoName(QWidget *parent = NULL);
	~VideoName();
	void initVideoNameUi();
	void showVideoStatus(QString fileName);
	void videoNameInit();
	void setDigitalBtn(bool isStyleChange);
	void setBtnEnable(bool isUsed){_isUsed = isUsed;};
	bool getBtnEnable(){return _isUsed;};
	void setIsStopCapture(bool isStopCapture){m_isContinousCapture = isStopCapture;};
	void keyPressEvent(QKeyEvent *event);
public:
	QWidget *m_videoName;
	QLabel *m_videoNameLabel;
	QPushButton *m_digitalZoomBtn;
	QPushButton *m_captureBtn;
	QPushButton *m_continuousCaptureBtn;
	QPushButton *m_fullScreenBtn;
	bool m_isStyleChange;
	bool _isUsed;
	bool m_isContinousCapture;
signals:
	void continousCapture(bool isContinousCapture);
	void fullScreen();
private slots:
	void getIscontinuousCapture();
};

#endif