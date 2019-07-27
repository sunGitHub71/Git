#include "playlist.h"
#include "LogUtility.h"
#include "resource_tr.h"
#include "customizemsgbox.h"
#include "AVPlayerDef.h"
#include "HSAVPlayer.h"
#include <QDir>
#include <Windows.h>
#include <QStyleOption>
#include <QSettings>
#include <QStyle>
#include <QDebug>
#include <QFileDialog>
#include <QDirIterator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QContextMenuEvent>

#define PLAYLIST_WIDTH 250
#define PLAYLIST_HEIGHT 82

PlayList::PlayList(QWidget *parent)
	:QWidget(parent)
	,m_isSearch(true)
	,m_listIndex(-1)
	,m_isSeaBtnClicked(false)
	,m_keyWord("")
	,m_listStatus(NORMALIST)
{

	this->setFixedWidth(249);
	setObjectName("PlayList");
	setStyleSheet("#PlayList{border-bottom:1px solid #000000;border-left:1px solid #000000;}");
	m_playListTop = new QWidget;
	m_playListTop->setObjectName("playListTop");
	m_playListTop->setFixedHeight(34);
	m_playListTop->setStyleSheet("#playListTop{background-color:#383838;border:1px solid #000000;border-left:none;border-right:none;}");

	m_playListLabel = new QLabel;
	m_playListLabel->setObjectName("playListLabel");

	m_addFileButton = new QPushButton;
	m_addFileButton->setFocusPolicy(Qt::NoFocus);
	m_addFileButton->setShortcut(QString("Ctrl+O"));
	m_addFileButton->setObjectName("addFile");
	m_addFileButton->setStyleSheet("#addFile{background-image:url(" + getPath() + BTN_ADD_NOR + ")} #addFile:hover {background-image:url(" + getPath() + BTN_ADD_PRESS + ")}");

	m_deleteFileButton = new QPushButton;
	m_deleteFileButton->setFocusPolicy(Qt::NoFocus);
	m_deleteFileButton->setObjectName("deleteFile");
	m_deleteFileButton->setStyleSheet("#deleteFile{background-image:url(" + getPath() + BTN_DELT_NOR + ")} #deleteFile:hover {background-image:url(" + getPath() + BTN_DELT_PRESS + ")}");

	m_selFileButton = new QPushButton;
	m_selFileButton->setFocusPolicy(Qt::NoFocus);
	m_selFileButton->setObjectName("selectFile");

	m_selFileButton->setStyleSheet("#selectFile{background-image:url(" + getPath() + BTN_MODE_NOR + ")} #selectFile:hover {background-image:url(" + getPath() + BTN_MODE_PRESS + ")}");

	m_searchFileButton = new QPushButton;
	m_searchFileButton->setFocusPolicy(Qt::NoFocus);
	m_searchFileButton->setObjectName("searchFile");
	m_searchFileButton->setStyleSheet("#searchFile{background-image:url(" + getPath() + BTN_SEARCH_NOR + ")}");

	m_playMode = new QMenu;
	m_single = new QAction(this);
	m_single->setCheckable(true);
	m_single->setChecked(true);
	m_order = new QAction(this);
	m_order->setCheckable(true);
	m_repeatOne = new QAction(this);
	m_repeatOne->setCheckable(true);
	m_repeatAll = new QAction(this);
	m_repeatAll->setCheckable(true);

	m_actionGroup = new QActionGroup(this);
	m_actionGroup->addAction(m_single);
	m_actionGroup->addAction(m_order);
	m_actionGroup->addAction(m_repeatOne);
	m_actionGroup->addAction(m_repeatAll);

	m_playMode->addAction(m_single);
	m_playMode->addAction(m_order);
	m_playMode->addAction(m_repeatOne);
	m_playMode->addAction(m_repeatAll);

	m_selFileButton->setMenu(m_playMode);

	m_playListCenter = new QWidget;
	m_playListCenter->setFixedHeight(81);
	m_playListCenter->setStyleSheet("background-color:#4d4d4d;");
	m_playListCenter->hide();

	m_centerTop = new QWidget(m_playListCenter);
	m_centerTop->setFixedHeight(28);
	m_centerTop->setStyleSheet("border-bottom:1px solid #595959");

	m_fileName = new QPushButton;
	m_fileName->setObjectName("fileName");
	m_fileName->setStyleSheet("#fileName{color:#d5cd00;border:none;border-bottom:2px solid #d5cd00;padding:6px;}");
	m_time = new QPushButton;
	m_time->setObjectName("time");
	m_time->setStyleSheet("#time{border:none;font-family:MicrosoftYaHeiLight;color:#aaaaaa;padding:6px;}");

	QHBoxLayout *hl1 = new QHBoxLayout;
	hl1->setContentsMargins(0,0,0,0);
	hl1->setSpacing(0);
	hl1->addWidget(m_fileName);
	hl1->addWidget(m_time);
	m_centerTop->setLayout(hl1);

	m_fileNameWidget = new QWidget;
	m_fileNameWidget->setFixedHeight(50);

	m_editFileName = new QLineEdit;
	m_editFileName->setFixedSize(230,30);
	m_editFileName->setStyleSheet("background-color:#383838;border:1px;border-radius:5px;");

	m_seaFileName = new QPushButton;
	m_seaFileName->setCursor(Qt::PointingHandCursor);
	m_seaFileName->setFixedSize(18,18);
	m_seaFileName->setObjectName("seaFileName");
	m_seaFileName->setStyleSheet("#seaFileName{background-image:url(" + getPath() + BTN_SEARCHBOX_NOR + ")} #seaFileName:hover {background-image:url(" + getPath() + BTN_SEARCHBOX_PRESS + ")}");
	QMargins margins = m_editFileName->textMargins();
	m_editFileName->setTextMargins(margins.left()+10, margins.top(), m_seaFileName->width(), margins.bottom());

	QHBoxLayout *hl2 = new QHBoxLayout;
	hl2->addStretch();
	hl2->addWidget(m_seaFileName);
	hl2->setContentsMargins(0,0,10,0);
	hl2->setSpacing(0);
	m_editFileName->setLayout(hl2);

	QVBoxLayout *vl2 = new QVBoxLayout;
	vl2->addWidget(m_editFileName);
	vl2->setSpacing(0);
	vl2->setContentsMargins(10,10,10,10);
	m_fileNameWidget->setLayout(vl2);

	m_timeWidget = new QWidget;
	m_timeWidget->setFixedHeight(50);

	m_dateTimeEdit = new DateTimeEdit(m_timeWidget);
	m_dateTimeEdit->setFixedSize(190,30);
	m_dateTimeEdit->setObjectName("DateTimeEdit");
	m_dateTimeEdit->setStyleSheet("#DateTimeEdit{background-color:#383838;border:1px;border-top-left-radius:5px; border-bottom-left-radius:5px;color:#cccccc;}QDateTimeEdit::down-arrow{image:url(" + getPath() + BTN_DATE_NOR + ")} QDateTimeEdit::down-arrow:hover{image:url(" + getPath() + BTN_DATE_PRESS + ")}QDateTimeEdit::drop-down{border:0px solid red;}");

	m_seaTime = new QPushButton;
	m_seaTime->setCursor(Qt::PointingHandCursor);
	m_seaTime->setFixedSize(38,30);
	m_seaTime->setObjectName("searchTime");
	m_seaTime->setStyleSheet("#searchTime{background-image:url(" + getPath() + BTN_SEARCHBOX_NOR + ");background-color:#383838;background-position:center;border-top-right-radius:5px;border-bottom-right-radius:5px;}#searchTime:hover {background-image:url(" + getPath() + BTN_SEARCHBOX_PRESS + ")}");

	m_seaTimeWidget = new QWidget(m_timeWidget);

	QHBoxLayout *hl3 = new QHBoxLayout;
	hl3->addWidget(m_dateTimeEdit);
	hl3->addWidget(m_seaTime);
	hl3->setContentsMargins(0,0,0,0);
	hl3->setSpacing(0);
	m_seaTimeWidget->setLayout(hl3);

	QHBoxLayout *vl3 = new QHBoxLayout;
	vl3->setContentsMargins(10,10,10,10);
	vl3->setSpacing(0);
	vl3->addWidget(m_seaTimeWidget);
	m_timeWidget->setLayout(vl3);

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setContentsMargins(0,0,0,0);
	vl1->setSpacing(0);
	vl1->addWidget(m_centerTop);
	vl1->addWidget(m_fileNameWidget);
	vl1->addWidget(m_timeWidget);
	m_timeWidget->hide();
	m_playListCenter->setLayout(vl1);

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,0,0,0);
	hl->setSpacing(0);
	hl->addWidget(m_playListLabel);
	hl->addStretch();
	hl->addWidget(m_addFileButton);
	hl->addWidget(m_deleteFileButton);
	hl->addWidget(m_selFileButton);
	hl->addWidget(m_searchFileButton);
	m_playListTop->setLayout(hl);

	m_playListBottom = new QListView;
	m_playListBottom->setDragEnabled(true);
	m_playListBottom->setDragDropMode(QAbstractItemView::DragOnly);
	m_playListBottom->setFocusPolicy(Qt::NoFocus);
	m_playListBottom->setFrameStyle(QFrame::NoFrame);
	m_playListBottom->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_playListBottom->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);  
	m_playListBottom->setObjectName("playListBottom");
	//m_playListBottom->setStyleSheet("QScrollBar::up-arrow:vertical{background:url(" + getPath() + BTN_TOP_NOR + ")}\
	//													QScrollBar::up-arrow:vertical:hover{background:url(" + getPath() + BTN_TOP_PRESS + ")}\
	//													QScrollBar::down-arrow:vertical {background:url(" + getPath() + BTN_DOWN_NOR +")}\
	//													QScrollBar::down-arrow:vertical:hover {background:url(" + getPath() + BTN_DOWN_PRESS +")}");

	QAbstractItemModel *oldModel = m_playListBottom->model();
	m_listModel = new PlayListModel;
	m_playListBottom->setModel((QAbstractItemModel*)m_listModel);

	QAbstractItemDelegate * oldDelegate =  m_playListBottom->itemDelegate();
	m_playListBottom->setItemDelegate(new PlayListDelegate(this));
	delete oldDelegate;

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(1,0,0,1);
	vl->setSpacing(0);
	vl->addWidget(m_playListTop);
	vl->addWidget(m_playListCenter);
	vl->addWidget(m_playListBottom);
	setLayout(vl);

	HS_Initial();
	HS_Free();

	rightButtonMenu();
	initPlayListUi();

	connect(m_searchFileButton,SIGNAL(clicked()),this,SLOT(Opensearch()));
	connect(m_fileName,SIGNAL(clicked()),this,SLOT(setClick()));
	connect(m_time,SIGNAL(clicked()),this,SLOT(setClick()));
	connect(m_playListBottom,SIGNAL(pressed(const QModelIndex &)),this,SLOT(getModelIndex(const QModelIndex &)));
	connect(m_deleteFile,SIGNAL(triggered()),this,SLOT(deleteCurFile()));
	connect(m_clearList,SIGNAL(triggered()),this,SLOT(clearCurFileList()));
	connect(m_deleteFileButton,SIGNAL(clicked()),this,SLOT(clearCurFileList()));
	connect(m_addFileButton,SIGNAL(clicked()),this,SLOT(addFile()));
	connect(m_playOrPause,SIGNAL(triggered()),this,SIGNAL(rightPlay()));
	connect(m_playListBottom,SIGNAL(doubleClicked ( const QModelIndex & )),this,SIGNAL(doubleClicked(const QModelIndex &)));
	connect(m_seaFileName,SIGNAL(clicked()),this,SLOT(startSearch()));
	connect(this,SIGNAL(endSearch()),this,SLOT(restorePlayList()));
	connect(m_single,SIGNAL(triggered()),this,SIGNAL(singlePlay()));
	connect(m_order,SIGNAL(triggered()),this,SIGNAL(orderPlay()));
	connect(m_repeatOne,SIGNAL(triggered()),this,SIGNAL(repeatOnePlay()));
	connect(m_repeatAll,SIGNAL(triggered()),this,SIGNAL(repeatAllPlay()));
}
PlayList::~PlayList()
{

}
void PlayList::paintEvent(QPaintEvent *event){
	QStyleOption opt;

	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}
void PlayList::rightButtonMenu()
{
	m_popMenu = new QMenu();

	m_playOrPause = new QAction(this);
	m_deleteFile = new QAction(this);
	m_clearList = new QAction(this);
}
void PlayList::initPlayListUi()
{
	m_playListLabel->setText(tr("playList"));
	m_addFileButton->setToolTip(tr("add File"));
	m_deleteFileButton->setToolTip(tr("Delete File"));
	m_selFileButton->setToolTip(tr("Play Mode"));
	m_searchFileButton->setToolTip(tr("Search File"));
	m_fileName->setText(tr("FileName"));
	m_time->setText(tr("Time"));
	m_editFileName->setPlaceholderText(tr("Please Enter FileName"));
	m_playOrPause->setText(tr("Play/Pause"));
	m_deleteFile->setText(tr("DeleteFile"));
	m_clearList->setText(tr("ClearList"));
	m_single->setText(tr("single"));
	m_order->setText(tr("order"));
	m_repeatOne->setText(tr("repeatOne"));
	m_repeatAll->setText(tr("repeatAll"));
}
void PlayList::contextMenuEvent(QContextMenuEvent *event)
{
	if(!m_playListBottom->isVisible()){
		return;
	}

	m_popMenu->clear();

	QPoint point = this->mapToGlobal(event->pos());

	QPoint lt = m_playListBottom->mapToGlobal(QPoint(0,0));
	QPoint rb = m_playListBottom->mapToGlobal(m_playListBottom->rect().bottomRight());

	QPoint mousePoint = m_playListBottom->mapFromGlobal(QCursor::pos());
	int rows = m_listModel->rowCount(QModelIndex());
	int h = rows*PLAYLIST_HEIGHT;

	if (QRect(lt,rb).contains(point))
	{
		if (mousePoint.y() <= h)
		{
			m_popMenu->addAction(m_playOrPause);
			m_popMenu->addSeparator();
			m_popMenu->addAction(m_deleteFile);
			m_popMenu->addAction(m_clearList);
		}
		m_popMenu->exec(QCursor::pos());
		event->accept();
	}
}
void PlayList::Opensearch()
{
	if(m_isSearch){ 
		m_playListCenter->show();
		m_searchFileButton->setStyleSheet("#searchFile{background-color:#4d4d4d;background-image:url(" + getPath() + BTN_SEARCH_PRESS + ")}");
		m_isSearch = false;
	}else {
		m_playListCenter->hide();
		m_searchFileButton->setStyleSheet("#searchFile{background-color:#383838;background-color:#383838;background-image:url(" + getPath() + BTN_SEARCH_NOR + ")}");
		m_isSearch = true;
		emit endSearch();
	}
	m_dateTimeEdit->setCalenderLan(m_curLanguage);
}
void PlayList::setClick()
{
	QPushButton *Btn = (QPushButton *)QObject::sender();

	if (Btn == m_fileName)
	{	m_fileNameWidget->show();
	m_timeWidget->hide();
	m_fileName->setStyleSheet("color:#d5cd00;border:none;border-bottom:2px solid #d5cd00;padding:6px;");
	m_time->setStyleSheet("#time{border:none;font-family:MicrosoftYaHeiLight;color:#aaaaaa;padding:6px;}");
	}else if (Btn == m_time)
	{
		m_fileNameWidget->hide();
		m_timeWidget->show();
		m_time->setStyleSheet("color:#d5cd00;border:none;border-bottom:2px solid #d5cd00;padding:6px;");
		m_fileName->setStyleSheet("#fileName{border:none;font-family:MicrosoftYaHeiLight;color:#aaaaaa;padding:6px;}");	

		m_dateTimeEdit->setCurDateTime();
		emit endSearch();
	}
}
QStringList PlayList::traverseDir(QString path)
{
	QDir dir(path);

	if(!dir.exists()){
		return QStringList();
	}else if (path == "")
	{
		return QStringList();
	}

	QStringList filters;
	filters<<QString("*.avi*") << QString("*.mp4") << QString("*.h264") << QString("*.h265")<< QString("*.avie") << QString("*.mov");

	QDirIterator dirIterator(path,filters,QDir::Files | QDir::NoSymLinks);
	m_traverseFileList.clear();

	while(dirIterator.hasNext())
	{
		dirIterator.next();
		QFileInfo fileInfo = dirIterator.fileInfo();
		QString absoluteFilePath = fileInfo.absoluteFilePath();
		m_traverseFileList.append(absoluteFilePath);
	}
	return m_traverseFileList;
}
bool PlayList::writeIni(QString path,bool isWrite)
{
	if(path.isEmpty()){
		return false;
	}else {
		QSettings settings(path,QSettings::IniFormat);
		settings.beginGroup("path");
		//settings.clear();	clear会清理所有内容，因为在配置文件中增加了其他信息，因此不建议使用clear
		settings.remove("");	//移出group下所有 或者使用remov("path")

		if (isWrite)
		{
			QStringList tempList = getAllFilePath();
			for (int i = 0;i < tempList.size();++i)
			{
				settings.setValue(QString("filePath%1").arg(i),tempList.at(i));
			}
		}
		HW_WRITE_LOG(log_info,"isWrite: %d",isWrite);
		settings.endGroup();

		settings.beginGroup("language");
		QString curLan = m_curLanguage;
		if (!curLan.isEmpty()){
			settings.setValue("currentLanCode",curLan);
		}
		settings.endGroup();

		return true;
	}
}
bool PlayList::writeIni(QString path){
	if (path.isEmpty())
	{
		return false;
	}else {
		//url列表
		QSettings settings(path,QSettings::IniFormat);
		settings.beginGroup("url");
		settings.setValue(QString("urlConnection"),m_urlConnection);
		settings.endGroup();
		return true;
	}
	return false;
	
}
QStringList PlayList::readIni(QString path)
{
	if(path.isEmpty()){
		return QStringList();
	}else {
		QSettings config(path,QSettings::IniFormat);
		QString	value = config.value(QString("path/") + "filePath0").toString();

		int i = 0;
		if (value != "")
		{
			m_iniFilePathList.append(value);
		}
		while(value != ""){
			i++;
			value = config.value(QString("path/") + QString("filePath%1").arg(i)).toString();
			if (value != "")
			{
				m_iniFilePathList.append(value);
			}
		}
		return m_iniFilePathList;
	}
	return QStringList();
}
QString PlayList::readCurLanguage(QString path)
{
	if (path.isEmpty())
	{
		return "";
	}else {
		QSettings config(path,QSettings::IniFormat);
		QString	value = config.value(QString("language/") + "currentLanCode").toString();
		return value;
	}
}

QString PlayList::readVersion(QString path)
{
	if (path.isEmpty())
	{
		return "";
	}
	else
	{
		QSettings config(path,QSettings::IniFormat);
		QString	value = config.value(QString("version/") + "number").toString();
		return value;
	}

}

QString PlayList::readName(QString path)
{
	if (path.isEmpty())
	{
		return "";
	}
	else
	{
		QSettings config(path,QSettings::IniFormat);
		QString	value = config.value(QString("program/") + "name").toString();
		return value;
	}
}

QString PlayList::readUrlIni(QString path){
	if (path.isEmpty())
	{
		return QString();
	}else {
		QSettings config(path,QSettings::IniFormat);
		QString	value = config.value(QString("url/") + "urlConnection").toString();
		return value;
	}
}

bool PlayList::scanData(const QDir &fromDir, const QStringList &filters)
{
     QFileInfoList fileInfoList = fromDir.entryInfoList(filters, QDir::Files);
     foreach(QFileInfo fileInfo, fileInfoList)
     {
         if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
             continue;
         if (fileInfo.isDir())
         {
             if (!scanData(fileInfo.filePath(), filters))
                 return false;
         }
         else
         {
             fileList.append(fileInfo.filePath());
         }
     }
    return true;
}

void PlayList::addFile()
{
	QFileDialog file;
	file.setOption(QFileDialog::DontUseNativeDialog);
	QString selectedFilter;
	QString add_File = file.getOpenFileName(this, tr("Open"),"", tr("AllFile(*.avi;*.mp4;*.h264;*.h265;*.avie;*.mov)"), &selectedFilter);
	QStringList addFileList;
	addFileList.append(add_File);
	if (!addFileList.isEmpty())
	{
		createFileNode(addFileList);
	}
	/*QFileInfo fi = QFileInfo(addFile1);
	fileList.clear();


	QString file_path = fi.absolutePath();
	QStringList filters;
	filters.append("*.avi");
	filters.append("*.mp4");
	filters.append("*.h264");
	filters.append("*.h265");
	filters.append("*.avie");
	filters.append("*.mov");

	QDir fromDir = file_path;
	scanData(fromDir, filters);

	if(!fileList.isEmpty())
	{
		createFileNode(fileList);
	}*/
}
void PlayList::mAddFile()
{
	addFile();
}
void PlayList::getModelIndex(const QModelIndex &index )
{
	MyModelItem * pInfo = (MyModelItem *)index.internalPointer();

	if(pInfo)
	{
		m_curFilePath = pInfo->filePath;
	}
}
QString PlayList::getCurFilePath()
{
	return m_curFilePath;
}
int PlayList::getCurSelectedIndex()
{
	m_listIndex = m_playListBottom->currentIndex().row();
	return m_listIndex;
}
QStringList PlayList::getAllFilePath()
{
	QVector<MyModelItem *> itemVec = m_listModel->getCurVec();

	MyModelItem *item = new MyModelItem;

	QStringList allFilePath;

	for (int i = 0;i < itemVec.size();++i)
	{
		*item = *itemVec[i];
		allFilePath.append(item->filePath);
	}
	return allFilePath;
}
void PlayList::deleteCurFile()
{
	int index = m_playListBottom->currentIndex().row();

	if (index >= 0)
	{
		bool ret = m_listModel->removeRow(index,QModelIndex());
		if(ret)
			emit deleteCurOver();

		m_listStatus = DELETECUR;
	}
}
void PlayList::deletePlayListItem(){
	int index = m_playListBottom->currentIndex().row();
	if (index >= 0)
	{
		m_listModel->removeRow(index,QModelIndex());
	}
}
void PlayList::clearCurFileList()
{
	if (m_listModel->rowCount(QModelIndex()) != 0)
	{
		int result = CustomizeMsgBox::showMyMessageBox(this,tr("Remind"),tr("The Playlist will be clear,are you sure?"),BUTTON_OK_AND_CANCEL,true);
		if (result == ID_OK)
		{
			bool ret = m_listModel->removeRowAll(QModelIndex());
			if(ret)
				emit deleteAllOver();

			m_listStatus = CLEARLIST;
		}	
	}
}
void PlayList::startSearch()
{
	QString keyWord = m_editFileName->text();

	if(m_editFileName->isVisible()){
		if (keywordChange(keyWord))
			m_allFilePath = getAllFilePath();
	}

	QStringList seaResult = searchFileList(keyWord,m_allFilePath);

	m_listModel->removeRowAll(QModelIndex());

	createFileNode(seaResult);

	m_isSeaBtnClicked = true;
}
void PlayList::restorePlayList()
{
	m_editFileName->setText("");

	if (m_isSeaBtnClicked)
	{
		if (m_listStatus == DELETECUR)
		{
			m_listModel->removeRowAll(QModelIndex());
			m_allFilePath.removeOne(m_curFilePath);
			createFileNode(m_allFilePath);
		}else if (m_listStatus == CLEARLIST)
		{
			m_listModel->removeRowAll(QModelIndex());
		}else {
			m_listModel->removeRowAll(QModelIndex());
			createFileNode(m_allFilePath);
		}
		m_listStatus = NORMALIST;
	}
	m_isSeaBtnClicked = false;
}
QStringList PlayList::isItemDelete(QStringList theList){
	if (!theList.isEmpty())
	{
		//匹配Ip
		QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
		for (int i = 0;i < theList.size();++i)
		{
			QFileInfo info(theList.at(i));
			if (!info.exists() && !theList.at(i).contains(rx))
			{
				theList.removeAt(i);
			}
		}
		return theList;
	}
	return QStringList();
}
void PlayList::createFileNode(QStringList allFilePath)
{
	QVector<MyModelItem*> vec;
	//allFilePath是否有被删除项 如果有 则从容器中删除该项
	QStringList list = isItemDelete(allFilePath);
	for (int i = 0;i < list.size();++i)
	{
		MyModelItem *model = new MyModelItem;

		QFileInfo info(list.at(i));
		QFileInfo picInfo;
		if (info.exists())
		{
			model->filePath = list.at(i);
			QString fileName = info.fileName();
			model->fileName = fileName;

			double fileSize = (double)info.size()/1024/1024;
			if (fileSize < 1024)
			{
				QString Size = QString::number(fileSize,'f',1);
				model->fileSize = Size + " " + "MB";
			}else {
				fileSize = fileSize/1024;
				QString bigSize = QString::number(fileSize,'f',1);
				model->fileSize = bigSize + " " + "GB";
			}

			QString fileSuffix = info.suffix();
			QString picName = getPath() + "/Skin/player/PlayListPic/" + fileName.replace(fileSuffix,"jpg");
			picInfo = QFileInfo(picName);

			HANDLE m_localPlayHandle = NULL;

			if (m_localPlayHandle == NULL)
			{
				HS_OpenRecFile(list.at(i).toUtf8().data(),&m_localPlayHandle);
			}

			long totalTime = 0;

			HS_GetFileTotalTime(m_localPlayHandle,&totalTime);

			if (!picInfo.exists())
			{
				QByteArray fileBate = list.at(i).toLocal8Bit();
				char *msg = fileBate.data();

				QByteArray picBate = picName.toLocal8Bit();
				char *picMsg = picBate.data();

				long ret = HS_SnapshotFromFile(msg,picMsg,0,0,40);
			}

			HS_CloseRecFile(m_localPlayHandle);
			m_localPlayHandle = NULL;

			model->pic = QPixmap(picName);
			model->totalTime = timeDisplay(totalTime);
		}else {
			//添加URL
			QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
			if (list.at(i).contains(rx))
			{
				model->filePath = list.at(i);
				model->fileName =  list.at(i);
				model->totalTime = "00:00:00";

				QStringList str1 = list.at(i).split("@");
				QStringList str2 = str1.at(1).split("/");
				QString strIp = str2.at(0);
				model->pic = QPixmap(getPath() + "/Skin/player/PlayListPic/" + strIp + ".jpg");
			}
		}
		vec.append(model);
	}
	m_listModel->setCurVec(vec);
}
void PlayList::insertItem(int index,QString item){
	if (index >= 0)
	{
		MyModelItem *model = new MyModelItem;
		model->filePath = item;
		model->fileName =  item;
		model->totalTime = "00:00:00";

		QStringList str1 = item.split("@");
		QStringList str2 = str1.at(1).split("/");
		QString strIp = str2.at(0);
		model->pic = QPixmap(getPath() + "/Skin/player/PlayListPic/" + strIp + ".jpg");

		m_listModel->insertRow(index,model);
	}
}
QStringList PlayList::fileFilter(QStringList oriFile)
{
	QStringList temp;
	QStringList filters;
	filters << QString("avi") << QString("mp4") << QString("h264") << QString("h265")<< QString("avie") << QString("mov");

	QFileInfo info;

	if(!oriFile.isEmpty())
	{
		for (int i = 0;i < oriFile.size();++i)
		{
			info = QFileInfo(oriFile.at(i));
			QString fileSuffix = info.suffix();

			if (filters.indexOf(fileSuffix) != -1)
			{
				QString tempStr = oriFile.at(i);
				tempStr.replace("/","\\");
				temp.append(tempStr);
			}
		}
	}
	return temp;
}
bool PlayList::removeTempFile(const QString &folderDir)
{
	QDir dir(folderDir);
	QFileInfoList fileList;
	QFileInfo curFile;

	if(!dir.exists()){
		return false;
	}

	fileList = dir.entryInfoList(QDir::Dirs|QDir::Files|QDir::Readable|QDir::Writable|QDir::Hidden|QDir::NoDotAndDotDot,QDir::Name);
	while(!fileList.isEmpty())
	{
		int infoNum = fileList.size();
		for(int i = infoNum-1;i >= 0;i--)
		{
			curFile = fileList[i];
			if(curFile.isFile())
			{
				QFile fileTemp(curFile.filePath());
				fileTemp.remove();
				fileList.removeAt(i);
			}

			if(curFile.isDir())
			{
				QDir dirTemp(curFile.filePath());
				QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs|QDir::Files|QDir::Readable|QDir::Writable|QDir::Hidden|QDir::NoDotAndDotDot,QDir::Name);
				if(fileList1.size() == 0)
				{
					dirTemp.rmdir(".");
					fileList.removeAt(i);
				}else{
					for(int j = 0;j < fileList1.size();j++)
					{
						if(!(fileList.contains(fileList1[j])))
						{
							fileList.append(fileList1[j]);
						}
					}
				}
			}
		}
	}
	return true;
}
QStringList PlayList::searchFileList(QString fileName,QStringList fileNameList)
{
	QStringList destList;
	QFileInfo info;

	if (!fileNameList.isEmpty())
	{
		for (int i = 0;i < fileNameList.size();++i)
		{
			info = QFileInfo(fileNameList.at(i));
			QString curFileName = info.fileName();
			if (!fileName.isEmpty())
			{
				if (fileName == curFileName || curFileName.contains(fileName))
				{
					destList.append(fileNameList.at(i));
				}
			}
		}
	}
	return destList;
}
bool PlayList::keywordChange(QString keyWord)
{
	if (m_keyWord != keyWord)
	{
		m_keyWord = keyWord;
		return true;
	}else {
		return false;
	}
}
QString PlayList::timeDisplay(long totalTime)
{
	long hour = totalTime/3600;
	long minutes = (totalTime - hour*3600)/60;
	long second = totalTime - hour*3600 - minutes*60;

	QString strHour = hour > 9 ? QString::number(hour) : "0" + QString::number(hour);
	QString strMinutes = minutes > 9 ? QString::number(minutes) : "0" + QString::number(minutes);
	QString strSecond = second > 9 ? QString::number(second) : "0" + QString::number(second);

	QString str = strHour + ":" + strMinutes + ":" + strSecond;

	return str;
}