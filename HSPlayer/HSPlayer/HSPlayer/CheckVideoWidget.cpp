#include "CheckVideoWidget.h"


CheckVideo_TableModel::CheckVideo_TableModel(QObject *parent)
	: QAbstractTableModel(parent), arr_row_list(NULL)
{
	hover_row = 0;
}

CheckVideo_TableModel::~CheckVideo_TableModel()
{

}

void CheckVideo_TableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
	horizontal_header_list = horizontalHeaderList;
}


int CheckVideo_TableModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
{	//防止未使用参数提示
	Q_UNUSED(parent);
	if (vertical_header_list.size() > 0)
	{
		return vertical_header_list.size();
	}
	if (NULL == arr_row_list)
	{
		return 0;
	}
	else
	{
		return arr_row_list->size();
	}
}

int CheckVideo_TableModel::columnCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	Q_UNUSED(parent);
	if(horizontal_header_list.size() > 0)
		return horizontal_header_list.size();

	if(NULL == arr_row_list)
		return 0;
	else
		return arr_row_list->at(0).size();
}

QVariant CheckVideo_TableModel::GetData(int row,int column)
{
	if(NULL == arr_row_list)
		return QVariant();
	else if(arr_row_list->size() < 1)
		return QVariant();
	else if ( arr_row_list->size() < row )
		return QVariant();
	else
		return arr_row_list->at(row).at(column);
}

QVariant CheckVideo_TableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if(NULL == arr_row_list)
		return QVariant();

	if(arr_row_list->size() < 1)
		return QVariant();

	int row = index.row();  //行号
	if (row < 0 || row >= arr_row_list->size())
		return QVariant();

	switch (role) {
	case Qt::BackgroundColorRole:
		{
			if (row == hover_row) { // 鼠标滑过背景色
				return QColor(229, 229, 231);
			}
		}
		break;
	case Qt::DisplayRole:       // 文本
		{  
			if(index.row() >= arr_row_list->size())
				return QVariant();
			if(index.column() >= arr_row_list->at(0).size())
				return QVariant();
			return arr_row_list->at(index.row()).at(index.column());                 
		}
	case Qt::TextAlignmentRole: // 对齐方式
		{  
			return int(Qt::AlignCenter);   
		}
	default:
		return QVariant();
	}

	return QVariant();
}

// 表头数据 ; 用来显示水平/垂直表头的数据
QVariant CheckVideo_TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role==Qt::DisplayRole)  
	{  
		if(orientation==Qt::Horizontal) // 水平表头  
		{  
			if(horizontal_header_list.size() > section)
				return horizontal_header_list[section];
			else
				return QVariant(); 
		}  
		else
		{
			if(vertical_header_list.size() > section)
				return vertical_header_list[section]; // 垂直表头  
			else
				return QVariant();
		}
	}  

	return QVariant(); 
}

void CheckVideo_TableModel::setModalDatas(QList< QStringList > *rowlist)
{
	arr_row_list = rowlist;
}

//更新表格
void CheckVideo_TableModel::refrushModel()
{
	beginResetModel();
	endResetModel();
}

// 用来设置数据，根据角色（颜色、文本、对齐方式、选中状态等）判断需要设置的内容
bool CheckVideo_TableModel::setData( const QModelIndex &index, const QVariant &value, int role )  
{  
	Q_UNUSED(role);
	Q_UNUSED(value);

	if(!index.isValid())  
		return false;  

	return true;  
} 

// 实时刷新 鼠标停留和离开某一行
void CheckVideo_TableModel::setHoverRow(int hover_row)
{
	this->hover_row = hover_row;
}

CheckVideo_TableView::CheckVideo_TableView(QWidget *parent /* = 0 */)
	: QTableView(parent)
{
	current_row = 0;
	m_currentRow = 0;
	_init();
}

CheckVideo_TableView::~CheckVideo_TableView()
{
	
}

void CheckVideo_TableView::_init()
{
	this->setStyleSheet( "CheckVideo_TableView{font:13px arial; background-color: rgb(69, 69, 69);border:1px solid rgba(255, 255, 255, 77);}"
		"CheckVideo_TableView::item{color:rgb(255, 255, 255);background:rgb(38, 39, 43);border:none;}"
		"CheckVideo_TableView::item:hover{color:rgb(255, 255, 255);background:rgb(38, 39, 43);}");

	m_model = new CheckVideo_TableModel(this);
	this->setModel(m_model);
	this->initHeader();
	m_model->setModalDatas(&grid_data_list);
	
	this->setAlternatingRowColors(true);
	this->setFrameShape(QFrame::StyledPanel); //设置无边框
	this->setShowGrid(false); //设置不显示格子线
	this->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
	this->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->verticalHeader()->setVisible(false);
	this->horizontalHeader()->setHighlightSections(false);
	this->horizontalHeader()->setObjectName("HeaderView");
	this->horizontalHeader()->setStyleSheet("QHeaderView{background-color:rgb(45, 45, 45);padding-top:0px;padding-bottom:0px;font: 13px arial;color: rgb(255, 255, 255);}"
		"QHeaderView:section{ height:25px;background-color:rgb(45, 45, 45);border-top:0px solid #000;border-right:0px solid #000;border-left:1px solid #FFFFFF;}");
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	this->horizontalHeader()->setStretchLastSection(true);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	this->setAutoScroll(true);
	this->setMouseTracking(true);
	this->setColumnWidth(0, 180);
	this->setColumnWidth(1, 70);
	this->setColumnWidth(2, 50);
	this->setColumnHidden(4, true);
	//connect(this, &CheckVideo_TableView::entered, this, &CheckVideo_TableView::showToolTip);
}

void CheckVideo_TableView::initHeader()
{
	//最后列隐藏，文件路径
	QStringList header;
	header << tr("File Name") << tr("Percent") << tr("Result")
		<< tr("Watermark Sign") << tr("");
	m_model->setHorizontalHeaderList(header);
}

void CheckVideo_TableView::addRow(QStringList rowList)
{
	grid_data_list.append(rowList);
	m_model->refrushModel();
}

void CheckVideo_TableView::updateFile(QStringList rowList)
{
	for (int i = 0; i < grid_data_list.size(); i++)
	{
		if (rowList[4] == grid_data_list[i].at(4))
		{
			grid_data_list.replace(i, rowList);
			m_model->refrushModel();
			break;
		}

	}
}

QVariant CheckVideo_TableView::getData(int row, int column)
{
	return m_model->GetData(row, column);
}

int CheckVideo_TableView::rowCount()
{
	return m_model->rowCount(QModelIndex());
}

void CheckVideo_TableView::showToolTip(const QModelIndex &index /* = QModelIndex() */)
{
	int row = index.row();
	int column = index.column();
	QStringList name = grid_data_list[row];
	if ( name.size() <= column )
	{
		return;
	}
	QString file_name = name.at(4);
	if(file_name.isEmpty())
		return;
	QPalette palette;
	palette.setColor(QPalette::ToolTipText,QColor(0, 0, 0));
	QToolTip::showText(QCursor::pos(),file_name ); 
	QToolTip::setPalette(palette);
}

void CheckVideo_TableView::clear()
{
	grid_data_list.clear();
	m_model->refrushModel();
}

void CheckVideo_TableView::mouseMoveEvent ( QMouseEvent * even)
{
	int row = indexAt(even->pos()).row();
	int column = indexAt(even->pos()).column();
	if (row < 0 || column <0)
	{
		return;
	}
	updateRow(row,column);
}

// 描  述: 鼠标离开某行数      
//-----------------------------------------------------------------------------
void CheckVideo_TableView::leaveEvent ( QEvent * event )
{
	Q_UNUSED(event);

	// 设置行
	m_model->setHoverRow(-1);
	// 刷新
	int column_count= m_model->columnCount();
	for (int i = column_count- 1; i >= 0; i--)
	{
		update(m_model->index(current_row, i));
	}
	// 离开置为-1
	current_row = -1;
}

// 选择一行
void CheckVideo_TableView::mousePressEvent(QMouseEvent *event)
{
	if ( grid_data_list.size() > 0 )
	{
		int row = indexAt(event->pos()).row();
		if ( row < 0 )
		{
			return;
		}

		QTableView::mousePressEvent(event);
	}
}

void CheckVideo_TableView::updateRow(int row,int column)
{
	// 设置行
	m_model->setHoverRow(row);

	//// 刷新所有列
	int column_count= m_model->columnCount();
	for (int i = column_count- 1; i >= 0; i--)
	{
		update(m_model->index(m_currentRow, i));
		update(m_model->index(row, i));
	}

	this->showToolTip(m_model->index(row, column));  //自定义方法用来进行QToolTip的显示

	// 记录
	m_currentRow = row;
}



CheckVideoWidget::CheckVideoWidget(QWidget *parent)
	:BaseWindow(parent)
{
	//this->setFixedSize(830, 450);
	this->setFixedSize(900, 550);
	m_startCheckBtn = new QPushButton(tr("Start Check"), this);
	m_startCheckBtn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);border-image:url(./Skin/player/playButton/checkBtn_unClicked.png)}"
		"QPushButton:hover{border-image:url(./Skin/player/playButton/checkBtn_move.png)}"
		"QPushButton:disabled{color:rgb(158, 112, 252);border-image:url(./Skin/player/playButton/checkBtn_un.png)}");
	m_startCheckBtn->setFixedSize(100, 30);
	m_stopCheckBtn = new QPushButton(tr("Stop Check"), this);
	m_stopCheckBtn->setFixedSize(100, 30);
	m_stopCheckBtn->setEnabled(false);
	m_stopCheckBtn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);border-image:url(./Skin/player/playButton/checkBtn_unClicked.png)}"
		"QPushButton:hover{border-image:url(./Skin/player/playButton/checkBtn_move.png)}"
		"QPushButton:disabled{color:rgb(158, 112, 252);border-image:url(./Skin/player/playButton/checkBtn_un.png)}");

	QLabel *titleCheckLabel = new QLabel(tr("Select file to be check"), this);
	titleCheckLabel->setObjectName("titleCL");
	titleCheckLabel->setFixedHeight(54);
	QLabel *titleInfoLabel = new QLabel(tr("Watermark Info"), this);
	titleInfoLabel->setObjectName("titleFL");
	titleInfoLabel->setFixedHeight(54);
	this->setStyleSheet("QLabel{font:15px arial;color:rgb(255, 255, 255);}");

	m_videoList = new QListWidget(this);
	m_videoList->setFocusPolicy(Qt::NoFocus);
	//上次选择后保留的状态，鼠标离开后显示
	m_videoList->setStyleSheet("QListWidget{background:rgb(69, 69, 69);border:1px solid rgba(255, 255, 255, 77);}\n"
		"QListWidget::Item{color:rgb(255, 255, 255);background:rgb(38, 39, 43);font:13px arial;height:30px;}");
	//m_videoList->setFixedSize(250, 450);
	//m_videoList->setFixedWidth(250);
	m_videoList->setMouseTracking(true);

	m_checkView = new CheckVideo_TableView(this);
	//m_checkView->setFixedSize(400, 450);
	//m_checkView->setFixedWidth(400);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->setSpacing(0);
	leftLayout->addWidget(titleCheckLabel);
	leftLayout->addWidget(m_videoList);

	QVBoxLayout *centerLayout = new QVBoxLayout;
	centerLayout->setContentsMargins(0, 0, 0, 0);
	centerLayout->setSpacing(20);
	centerLayout->addStretch();
	centerLayout->addWidget(m_startCheckBtn);
	centerLayout->addWidget(m_stopCheckBtn);
	centerLayout->addStretch();

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->setContentsMargins(0, 0, 0, 0);
	rightLayout->setSpacing(0);
	rightLayout->addWidget(titleInfoLabel);
	rightLayout->addWidget(m_checkView);

	QHBoxLayout *bLayout = new QHBoxLayout;
	bLayout->setContentsMargins(20, 25, 20, 30);
	bLayout->setSpacing(20);
	bLayout->addLayout(leftLayout, 5);
	bLayout->addLayout(centerLayout, 2);
	bLayout->addLayout(rightLayout, 8);

	m_thread = new CheckMD5Thread(this);

	setLayout(bLayout);
	
	initTitleBar();
	
	connect(m_thread, SIGNAL(MsgSignal(QStringList)), this, SLOT(onCheckFile(QStringList)));
	connect(m_thread, SIGNAL(MsgSignalUpdate(QStringList)), this, SLOT(onCheckFileUpdate(QStringList)));
	connect(m_thread, SIGNAL(MsgSignalOver()), this, SLOT(onCheckOver()));
	connect(m_videoList, SIGNAL(itemEntered(QListWidgetItem *)), this, SLOT(onShowListTooltip(QListWidgetItem *)));
	connect(m_startCheckBtn, SIGNAL(clicked()), this, SLOT(onStartBtnClicked()));
	connect(m_stopCheckBtn, SIGNAL(clicked()), this, SLOT(onStopBtnClicked()));
}

CheckVideoWidget::~CheckVideoWidget()
{
	m_thread->stopImmediately();
	m_thread->wait();
}

void CheckVideoWidget::onShowListTooltip(QListWidgetItem *item)
{
	QString fileText = item->text();
	QPalette palette;
	palette.setColor(QPalette::ToolTipText,QColor(0, 0, 0));
	QToolTip::showText(QCursor::pos(),fileText ); 
	QToolTip::setPalette(palette);
}

void CheckVideoWidget::onStartBtnClicked()
{
	checkFileList.clear();
	m_checkView->clear();
	for (int i = 0; i < m_videoList->count(); i++)
	{
		if (m_videoList->item(i)->checkState() == Qt::Checked)
		{
			//选中则添加
			checkFileList.append(allFileList[i]);
		}
	}
	if (checkFileList.size() == 0)
	{
		return;
	}
	//启动线程
	m_thread->setFileString(checkFileList);
	m_thread->start();
	m_stopCheckBtn->setEnabled(true);
	m_startCheckBtn->setEnabled(false);
}

void CheckVideoWidget::onStopBtnClicked()
{
	m_thread->stopImmediately();
	m_startCheckBtn->setEnabled(true);
	m_stopCheckBtn->setEnabled(false);
}

void CheckVideoWidget::onCheckOver()
{
	m_startCheckBtn->setEnabled(true);
	m_stopCheckBtn->setEnabled(false);
}

void CheckVideoWidget::onCheckFile(QStringList fileInfo)
{
	m_checkView->addRow(fileInfo);
}

void CheckVideoWidget::onCheckFileUpdate(QStringList fileInfo)
{
	m_checkView->updateFile(fileInfo);
}

void CheckVideoWidget::initTitleBar(){
	m_titleBar->move(0, 0);
	m_titleBar->setWindowBorderWidth(0);
	m_titleBar->setBackgroundColor(45,45,45);
	//m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
	m_titleBar->setButtonType(MAX_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	m_titleBar->setTitleContent(tr("Verification"));
}

void CheckVideoWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()) , 3 , 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.fillPath(pathBack, QBrush(QColor("#555555")));
	return QWidget::paintEvent(event);
}

void CheckVideoWidget::initFile()
{
	m_videoList->clear();
	for (int i = 0; i < allFileList.size(); i++)
	{
		//截取路径只显示文件名
		QString itemFile = allFileList[i].mid(allFileList[i].lastIndexOf("\\")+1);
		QListWidgetItem *item = new QListWidgetItem;
		item->setText(itemFile);
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
		item->setCheckState(Qt::Unchecked);
		m_videoList->addItem(item);
	}
}

void CheckVideoWidget::setFileList(QStringList fileList)
{
	allFileList.clear();
	allFileList = fileList;
	//加载文件列表
	initFile();
		
}
