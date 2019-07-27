#pragma once
#ifndef CHECKVIDEOWIDGET_H
#define CHECKVIDEOWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QEventLoop>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QCoreApplication>
#include <QCheckBox>
#include <QAbstractTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QToolTip>
#include <QDebug>
#include <QTextCodec>
#include <QCryptographicHash>
#include <QStyledItemDelegate>
#include "process.h"
#include "basewindow.h"
#include "CheckMD5Thread.h"
#include "playlist.h"


class CheckVideo_TableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	CheckVideo_TableModel(QObject *parent = 0);
	~CheckVideo_TableModel();
	void setHorizontalHeaderList(QStringList horizontalHeaderList);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;  
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void setModalDatas(QList< QStringList > *rowlist);
	void refrushModel();
	bool setData( const QModelIndex &index, const QVariant &value, int role );
	void setHoverRow(int hover_row);
	QVariant GetData(int row,int column);

signals:

	void updateCount(int count);

private:

	int hover_row;              // 鼠标滑到行数(实时更新)

	QStringList horizontal_header_list;
	QStringList vertical_header_list;
	QList< QStringList > *arr_row_list;  // 每行数据

};

class CheckVideo_TableView : public QTableView
{
	Q_OBJECT
public:
	CheckVideo_TableView(QWidget *parent = 0);
	~CheckVideo_TableView();
private:
	void _init();
public:
	void addRow(QStringList rowList);
	int rowCount();
	void showToolTip(const QModelIndex &index = QModelIndex());
	QVariant getData(int row, int column);
	void updateFile(QStringList rowList);
	QList<QStringList> grid_data_list;
	void clear();
protected:
	void mouseMoveEvent ( QMouseEvent * event);
	void leaveEvent ( QEvent * event );
	void mousePressEvent(QMouseEvent *event);
	

private:
	void initHeader();
	void updateRow(int row,int column);
private:
	int current_row;        // 鼠标滑到行数(实时更新)
	CheckVideo_TableModel  *m_model;
	int m_currentRow;

};

class CheckVideoWidget : public BaseWindow
{
	Q_OBJECT
public:
	CheckVideoWidget(QWidget *parent = 0);
	~CheckVideoWidget();
	void setFileList(QStringList fileList);
private slots:
	void onStartBtnClicked();
	void onCheckFile(QStringList fileInfo);			//添加行
	void onCheckFileUpdate(QStringList fileInfo);	//更新行信息
	void onStopBtnClicked();
	void onCheckOver();								//文化检查结束，恢复按钮
	void onShowListTooltip(QListWidgetItem *item);
private:
	void paintEvent(QPaintEvent *event);
	void initTitleBar();
	void initFile();
public:
	QPushButton *m_startCheckBtn;			//开始校验按钮
	QPushButton	*m_stopCheckBtn;			//停止校验按钮

	QListWidget	*m_videoList;				//文件列表
	QCheckBox	*checkAllBox;				//全选按钮

	CheckVideo_TableView	*m_checkView;	//反馈信息表格	

	QStringList	allFileList;				//所有的文件信息
	QStringList	checkFileList;				//选中的文件

	CheckMD5Thread *m_thread;

};
#endif