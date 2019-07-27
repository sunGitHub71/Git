#include "mainlayout.h"
#include "resource_tr.h"
#include <QVBoxLayout>
#include <QFileDialog>

MainLayout::MainLayout(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_mainLayout = new QWidget;
	m_mainLayout->setObjectName("MainLayout");
	QString str = getPath() + MAIN_LAYOUT;
	m_mainLayout->setStyleSheet("#MainLayout{background-image:url(" + str + ");background-repeat:no-repeat;background-position:center;}");

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(0,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_mainLayout);
	setLayout(vl);

	m_mainLayoutCenter = new QWidget(m_mainLayout);
	m_mainLayoutLabel = new QLabel();
	m_mainLayoutLabel->setAlignment(Qt::AlignLeft);
	m_mainLayoutLabel->setStyleSheet("font-size:60px;font-family:MicrosoftYaHei;color:#fefefe;font-weight:bold;");

	m_openFile = new QPushButton;
	m_openFile->setObjectName("OpenFile");
	m_openFile->setStyleSheet("color:#999999;font-size:24px;background-color:rgba(255,255,255,0);border:1px solid #999999;width:250px;height:80px;margin-top:40px;");

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setContentsMargins(0,0,0,0);
	vl1->setSpacing(0);
	vl1->addWidget(m_mainLayoutLabel);
	vl1->addWidget(m_openFile);
	m_mainLayoutCenter->setLayout(vl1);

	QVBoxLayout *vl2 = new QVBoxLayout;
	vl2->setContentsMargins(0,0,0,0);
	vl2->setSpacing(0);
	vl2->addStretch();
	vl2->addWidget(m_mainLayoutCenter);
	vl2->addStretch();

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,0,0,0);
	hl->setSpacing(0);
	hl->addStretch();
	hl->addLayout(vl2);
	hl->addStretch();
	m_mainLayout->setLayout(hl);

	initMainLayoutUi();

	connect(m_openFile,SIGNAL(clicked()),this,SLOT(openFile()));

}
MainLayout::~MainLayout()
{

}
void MainLayout::initMainLayoutUi(){
	m_openFile->setText(tr("OpenFile"));
}

void MainLayout::setName(QString name)
{
	m_mainLayoutLabel->setText(name);
}

bool MainLayout::scanData(const QDir &fromDir, const QStringList &filters)
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
 
void MainLayout::openFile(){
	QFileDialog file;
	file.setOption(QFileDialog::DontUseNativeDialog);
	QString selectedFilter;
	QString open_File = file.getOpenFileName(this, tr(""),"", tr("AllFile(*.avi;*.mp4;*.h264;*.h265;*.avie;*.mov)"), &selectedFilter);
	QStringList openFileList;
	openFileList.append(open_File);
	if (!openFileList.isEmpty())
	{
		emit curOpenList(openFileList);
	}
	/*QFileInfo fi = QFileInfo(openFile1);
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
		emit curOpenList(fileList);
	}*/

}
