#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QListView>
#include <QStyledItemDelegate>
#include <QActionGroup>
#include <QPainter>
#include <Windows.h>
#include <QDir>
#include "datetimeedit.h"
#include "playlistmodel.h"

enum PlayListStatus{
	DELETECUR = 0,
	CLEARLIST,
	NORMALIST
};

class PlayList : public QWidget {
	Q_OBJECT

public:
	PlayList(QWidget *parent = NULL);
	~PlayList();

public:
	void paintEvent(QPaintEvent *event);
	QStringList traverseDir(QString path);
	QStringList readIni(QString path);
	QStringList searchFileList(QString fileName,QStringList fileNameList);
	void rightButtonMenu();
	void contextMenuEvent(QContextMenuEvent *event);
	bool writeIni(QString path,bool isWrite);
	bool writeIni(QString path);
	void createFileNode(QStringList allFilePath);
	void initPlayListUi();
	bool removeTempFile(const QString &folderDir);
	bool keywordChange(QString keyWord);
	QString getCurFilePath();
	QStringList getAllFilePath();
	QString timeDisplay(long totalTime);
	int getCurSelectedIndex();
	QStringList fileFilter(QStringList oriFile);
	void getCurLanguage(QString curLanguage){
		m_curLanguage = curLanguage;
	};
	QString readCurLanguage(QString path);
	QString readUrlIni(QString path);
	QString readVersion(QString path);
	QString readName(QString path);
	void mAddFile();
	void deletePlayListItem();
	void insertItem(int index,QString item);
	void getUrl(QString urlConnection){m_urlConnection = urlConnection;};
	QStringList isItemDelete(QStringList theList);
	bool scanData(const QDir &fromDir, const QStringList &filters);

private slots:
	void Opensearch();
	void setClick();
	void getModelIndex(const QModelIndex &index);
	void deleteCurFile();
	void clearCurFileList();
	void addFile();
	void startSearch();
	void restorePlayList();
	
signals:
	void deleteCurOver();
	void deleteAllOver();
	void rightPlay();
	void doubleClicked(const QModelIndex &);
	void endSearch();
	void singlePlay();
	void orderPlay();
	void repeatOnePlay();
	void repeatAllPlay();

private:
	QWidget *m_playListTop;

	QWidget *m_playListCenter;
	QWidget *m_centerTop;
	QPushButton *m_fileName;
	QPushButton *m_time;
	QLineEdit *m_editFileName;
	QLineEdit *m_editTime;
	QPushButton *m_seaFileName;
	QPushButton *m_date;
	QPushButton *m_seaTime;
	QWidget *m_fileNameWidget;
	QWidget *m_timeWidget;
	QWidget *m_seaTimeWidget;

	QListView *m_playListBottom;
	PlayListModel *m_listModel;
	PlayListDelegate *m_listDelegate;
	QLabel *m_playListLabel;
	QPushButton *m_addFileButton;
	QPushButton *m_deleteFileButton;
	QPushButton *m_selFileButton;
	QMenu *m_playMode;
	QAction *m_single;
	QAction *m_order;
	QAction *m_repeatOne;
	QAction *m_repeatAll;
	QActionGroup *m_actionGroup;

	QPushButton *m_searchFileButton;

	bool m_isSearch;
	bool m_isSeaBtnClicked;
	QStringList m_filePathList;
	QStringList m_fileNameList;
	QStringList m_traverseFileList;
	QStringList list;
	QStringList m_iniFilePathList;

	QMenu *m_popMenu;
	QAction *m_playOrPause;
	QAction *m_deleteFile;
	QAction *m_clearList;

	DateTimeEdit *m_dateTimeEdit;
	int m_listIndex;

	QString	m_keyWord;

	QString m_curFilePath;
	QStringList m_allFilePath;
	PlayListStatus m_listStatus;

	QString m_curLanguage;
	QString m_urlConnection;
	QStringList m_urlList;

	QStringList fileList;
};
#endif