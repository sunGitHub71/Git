#include "playlistitem.h"
#include "resource_tr.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>

PlayListItem::PlayListItem(QWidget *parent)
	:QWidget(parent)
{
	m_container = new QWidget(this);

	m_leftIcon = new QLabel;
	m_leftIcon->setFixedWidth(100);
	m_leftIcon->setStyleSheet("background-color:red;");

	m_fileName = new QLabel(tr("fileName"));
	m_totalTime = new QLabel(tr("totalTime"));
	m_fileSize = new QLabel(tr("fileSize"));

	m_rightFrame = new QFrame;

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(10,0,0,0);
	vl->setSpacing(10);
	vl->addWidget(m_fileName);
	vl->addWidget(m_totalTime);
	vl->addWidget(m_fileSize);
	m_rightFrame->setLayout(vl);

	QHBoxLayout *hl = new QHBoxLayout;
	hl->setContentsMargins(0,0,0,0);
	hl->setSpacing(0);
	hl->addWidget(m_leftIcon);
	hl->addWidget(m_rightFrame);
	m_container->setLayout(hl);

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->setContentsMargins(10,10,10,10);
	vl1->setSpacing(0);
	vl1->addWidget(m_container);

	setLayout(vl1);
}
PlayListItem::~PlayListItem(){

}
void PlayListItem::setListItemText(QString filePath,QString videoTotalTime){
	QFileInfo info,picInfo;
	info = QFileInfo(filePath);
	QString fileName = info.fileName();
	QString fileSuffix = info.suffix();
	double fileSize = (double)info.size()/1024/1024;

	QString picName = getPath() + "/Skin/PlayListPic/" + fileName.replace(fileSuffix,"jpg");
	picInfo = QFileInfo(picName);

	int fontSize = fontMetrics().width(info.fileName());

	if (fontSize > 100)
	{
		QString begin = info.fileName().left(3);
		QString end = info.fileName().right(5);

		QString str = begin + "..." + end;
		m_fileName->setText(str);
	}else {
		 m_fileName->setText(info.fileName());
	}

	m_fileSize->setText(QString::number(fileSize,'f',1) + "MB");
	m_fileSize->setStyleSheet("color:#aaaaaa");
	
	if (!picInfo.exists())
	{
		m_leftIcon->setStyleSheet("background-color:black;");
		m_leftIcon->setText(tr("Invalid"));
		m_leftIcon->setAlignment(Qt::AlignCenter);
	}else {
		m_leftIcon->setStyleSheet("border-image:url(" + picName + ")");
	}
	
	m_totalTime->setText(videoTotalTime);
	m_totalTime->setStyleSheet("color:#aaaaaa");
}
