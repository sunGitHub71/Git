#include "playlistmodel.h"
#include "resource_tr.h"
#include <QPainter>
#include <QMimeData>
#include <QFontMetrics>
#include <QPen>

PlayListModel::PlayListModel(QObject *parent)
	:QAbstractListModel(parent){

}
PlayListModel::~PlayListModel(){
	for (int i = 0;i < m_dataModel.size();++i)
	{
		delete m_dataModel[i];
	}
	m_dataModel.clear();
}
void PlayListModel::setCurVec(const QVector<MyModelItem*> &vec){
	beginResetModel();
	for (int i = 0;i < vec.size();++i)
	{
		MyModelItem *item = new MyModelItem;
		*item = *vec[i];
	
		if (m_filePathList.indexOf(item->filePath) == -1)
		{
			m_filePathList.append(item->filePath);
			m_dataModel.push_back(item);
		}		
	}
	endResetModel();
}
int PlayListModel::rowCount(const QModelIndex& parent = QModelIndex()) const{
	return m_dataModel.size();
}
int PlayListModel::columnCount(const QModelIndex &parent) const{
	return 1;
}
QVariant PlayListModel::data(const QModelIndex &index, int role ) const{
	if(role == Qt::ToolTipRole)
	{
		MyModelItem * item = (MyModelItem*)index.internalPointer();
		if (item)
		{
			return item->fileName;
		}
	}
	return QVariant();
}
bool PlayListModel::setData(const QModelIndex & index,const QVariant & value,int role){
	return true;
}
QModelIndex PlayListModel::index(int row, int column,const QModelIndex &parent) const{
	if (!hasIndex(row,column,parent))
		return QModelIndex();

	return createIndex(row,column,(void*)m_dataModel[row]);
}
bool PlayListModel::removeRow(int row, const QModelIndex & parent = QModelIndex()){
	beginResetModel();
	m_dataModel.remove(row);
	m_filePathList.removeAt(row);
	endResetModel();
	return true;
}
bool PlayListModel::insertRow(int row, MyModelItem* const model, const QModelIndex & parent){
	beginResetModel();
	m_dataModel.insert(row, model);
	m_filePathList.insert(row,model->filePath);
	endResetModel();
	return true;
}
bool PlayListModel::removeRowAll(const QModelIndex & parent){
	beginResetModel();
	m_dataModel.remove(0, m_dataModel.size());
	m_filePathList.clear();
	endResetModel();
	return true;
}
QMimeData * PlayListModel::mimeData(const QModelIndexList &indexes) const{
	if(indexes.count() <= 0)
		return 0;

	MyModelItem* nodeInfo = static_cast<MyModelItem*>(indexes.at(0).internalPointer());
	QMimeData *data = new QMimeData;
	if (nodeInfo)
		data->setData("pointer/MyModelItem",QByteArray::number((int)nodeInfo));
	return data;
}
Qt::ItemFlags PlayListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled;
}
PlayListDelegate::PlayListDelegate(QObject *parent)
	:QStyledItemDelegate(parent){

}
PlayListDelegate::~PlayListDelegate(){

}
void PlayListDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
	
	QRect rect = option.rect;
	QRect rectBk = QRect(rect.left() + 1,rect.top(),rect.width(),rect.height());

	QBrush itemBkBrush;

	if (option.state & QStyle::State_Selected || option.state & QStyle::State_MouseOver)
	{
		itemBkBrush = QBrush(QColor("#6e6767"));
	}else {
		itemBkBrush = QBrush(QColor(60,60,60));
	}

	painter->fillRect(rectBk,itemBkBrush);
	MyModelItem * pInfo = (MyModelItem *)index.internalPointer();
	if (pInfo)
		{
			QRect rowRect;
			QRect picRect;
			QRect textRect;
			
			rowRect = QRect(rectBk.x(),rectBk.y(),rectBk.width(),82);
			picRect = QRect(rowRect.left() + 10,rowRect.top() + 10,100,62);
			textRect = QRect(picRect.left() + picRect.width() + 10,picRect.top(),120,20);
			
			QPixmap picPath = pInfo->pic;
			if(picPath.isNull()){
				painter->drawPixmap(picRect,getPath() + MAIN_LAYOUT);
			}else {
				painter->drawPixmap(picRect,picPath);
			}
			
			QFont font("MicrosoftYaHei",10,QFont::Normal,false);
			font.setFamily("Microsoft YaHei");
			painter->setFont(font);
			painter->setPen(QPen(QColor("#cccccc")));

			QString name = pInfo->fileName;
			QFontMetrics fm = painter->fontMetrics();
			int fontWidth = fm.width(name);
			if (fontWidth > 120)
			{
				QString begin = name.left(3);
				QString end = name.right(5);

				QString str = begin + "..." + end;
				painter->drawText(textRect,str);
			}else {
				painter->drawText(textRect,name);
			}
			
			painter->setPen(QPen(QColor("#aaaaaa")));
			textRect = QRect(picRect.left() + picRect.width() + 10,picRect.top() + 20,120,20);
			QString totalTime = pInfo->totalTime;
			painter->drawText(textRect,totalTime);

			textRect = QRect(picRect.left() + picRect.width() + 10,picRect.top() + 40,120,20);
			QString fileSize = pInfo->fileSize;
			painter->drawText(textRect,fileSize);
		}
}
QSize PlayListDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
	return QSize(250,82);
}