#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include "ui_mainlayout.h"
#include <QPushButton>
#include <QDir>
#include <QLabel>

class MainLayout : public QWidget
{
	Q_OBJECT

public:
	MainLayout(QWidget *parent = 0);
	~MainLayout();
	//void painterEvent(QPainter *event);
	void initMainLayoutUi();
	bool scanData(const QDir &fromDir, const QStringList &filters);
	void setName(QString name);
private:
	Ui::MainLayout ui;

private:
	QWidget *m_mainLayout;
	QWidget *m_mainLayoutCenter;
	QLabel *m_mainLayoutLabel;
	QPushButton *m_openFile;
	QStringList fileList;

private slots:
	void openFile();

signals:
	void curOpenList(QStringList curList);

};

#endif // MAINLAYOUT_H
