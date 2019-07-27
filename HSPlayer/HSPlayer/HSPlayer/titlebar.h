#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include "openurl.h"
#include "lanitem.h"
#include "language.h"

class PlayList;
class PlayCtrl;

class TitleBar : public QWidget {
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent = NULL);
	~TitleBar();
	void setPlayList(PlayList *playList){_playList = playList;};
	void setPlayStatus(bool playStatus){m_playStatus = playStatus;};

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void onClicked();
	void menuAddFile();
	void menuOpenDir();
	void menuAbout();
	void menuOpenUrl();
	void onCurLan();
private:
	void updateMaximize();
public:
	void initTitleUi();
	void setVersion(QString versionNumber);
public:
	QLabel *m_IconLabel;
	QPushButton *m_ConnentLabel;
	QPushButton *m_setting;
	QPushButton *m_MaximizeButton;
	QPushButton *m_MinimizeButton;
	QPushButton *m_CloseButton;
	QMenu *m_setBtn;
	QMenu *m_open;
	QAction *m_openFile;
	QAction *m_openDir;
	QAction *m_openUrl;
	QMenu *m_language;
	QAction *m_settings;
	QAction *m_userManual;
	QAction *m_about;
	QList<QAction *> m_lanList;
	QStringList list;
	QList<lanItem *> m_lanItem;

	bool m_isPressed;
	bool m_isMaxmized;
	QPoint m_StartMovePos;

	PlayList *_playList;
	PlayCtrl *_playCtrl;
	openUrl *m_OpenUrl;
	bool m_playStatus;

	Language *m_lang;

	QString m_VersionNumber;

signals:
	bool clicked();
	void UrlPath(QString path);
	void curlanCode(QString lan,int index);
};
#endif