#include "basewindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QStyleOption>

BaseWindow::BaseWindow(QWidget *parent)
	: QDialog(parent)
{
	//�������Qt::Dialog�������޷��Ƴ�
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground);
	initTitleBar();
	m_isFull = false;
}

BaseWindow::~BaseWindow()
{

}

void BaseWindow::initTitleBar()
{
	m_titleBar = new MyTitleBar(this);
	m_titleBar->move(0, 0);

	connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
	connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
	connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

}

void BaseWindow::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

	//���ñ���ɫ;
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(QColor(236, 241, 245)));

	return QWidget::paintEvent(event);
}

void BaseWindow::onButtonMinClicked()
{
	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide(); 
	}
	else
	{
		showMinimized();
	}
}

void BaseWindow::onButtonRestoreClicked()
{
	QPoint windowPos;
	QSize windowSize;
	m_titleBar->getRestoreInfo(windowPos, windowSize);
	this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked()
{
	/*m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
	QRect desktopRect = QApplication::desktop()->availableGeometry();
	QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
	setGeometry(FactRect);*/
	//���ӱ�ʶ���ж��Ƿ�ȫ��
	if (m_isFull)
	{
		m_isFull = false;
		m_titleBar->m_isFull = false;
		this->showNormal();
	}
	else
	{
		m_isFull = true;
		m_titleBar->m_isFull = true;
		/*
		showFullScreen()ֻ�Զ����������ã����Ӵ�����Ч
		���Ҫʹ������Խ�������ʱ����Ϊ�������ڣ�������ɺ��ٻָ�Ϊ�Ƕ�������
		*/
		this->showMaximized();
	}
	
}

void BaseWindow::onButtonCloseClicked()
{
	close();
}
