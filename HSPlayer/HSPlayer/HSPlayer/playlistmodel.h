#pragma once
#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QPixmap>
#include <QVector>
#include <QLabel>

class MyModelItem{
public:
	MyModelItem(){
		filePath = "";
		pic = QPixmap();
		fileName = "";
		totalTime = "";
		fileSize = "";
	}
public:
	QString filePath;
	QPixmap pic;
	QString fileName;
	QString totalTime;
	QString fileSize;
}; 

class PlayListModel : public QAbstractListModel{
	Q_OBJECT
public:
	PlayListModel(QObject *parent = 0);
	~PlayListModel();

	void setCurVec(const QVector<MyModelItem*> &vec);
	virtual int rowCount(const QModelIndex& parent) const;
	virtual int columnCount(const QModelIndex &parent) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	virtual QVariant data(const QModelIndex &index, int role ) const;
	QModelIndex index(int row, int column,const QModelIndex &parent) const;
	virtual bool setData ( const QModelIndex & index, const QVariant & value, int role );
	bool removeRow(int row, const QModelIndex & parent);
	bool removeRowAll(const QModelIndex & parent);
	bool insertRow(int row, MyModelItem* const model, const QModelIndex & parent = QModelIndex()); 
	QVector<MyModelItem *> getCurVec(){return m_dataModel;};
private:
	QVector<MyModelItem*> m_dataModel;
	QStringList m_filePathList;
};

class PlayListDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	PlayListDelegate(QObject *parent);
	~PlayListDelegate();


protected:
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
private:
	QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif