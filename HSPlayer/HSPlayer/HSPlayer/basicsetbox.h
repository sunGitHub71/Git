#ifndef BASICSETBOX_H
#define BASICSETBOX_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QEventLoop>
#include <QFrame>
#include <QStackedWidget>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QButtonGroup>
#include "basewindow.h"
#include "basicSetItem.h"
#include "cuslineedit.h"
#include "cusbutton.h"

enum ChooseResult
{
	ID_OK_BTN = 0,						
	ID_CANCEL_BTN						
};

enum MsgButtonType
{
	ONLY_BUTTON_OK = 0,					
	BUTTON_OK_CANCEL,			
	ONLY_BUTTON_CLOSE	
};

class BasicSetBox : public BaseWindow {
	Q_OBJECT
public:
	BasicSetBox(QWidget *parent = NULL,int index = 0);
	~BasicSetBox();

public:
	void setWindowTitle(QString title, int titleFontSize = 10);
	void setButtonType(MsgButtonType buttonType);
	void setMessageContent(QString messageContent);
	int  showMyMessageBox(QWidget* parent, const QString &title,MsgButtonType messageButtonType , bool isModelWindow = false);
	void initValue();
	static bool WriteSetIni(QString path,BASIC_SET_ITEM *basicSet,CAPTURE_SET_ITEM *captureSet,HOTKEY_SET_ITEM *hotkeySet);
	static bool readSetIni(QString path);
	void initSetPage();
	void initSetUi();
	int getCurIndex(){return m_index;};

private:
	void initWindow();
	void initTitleBar();
	int exec();

	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);

private slots:
	void onOkClicked();
	void onCancelClicked();
	void mainLayoutChange();
	void getFilePath();
	void restoreSetting();

private:
	QEventLoop* m_eventLoop;
	ChooseResult m_chooseResult;
	QPushButton *m_okBtn;
	QPushButton *m_cancelBtn;
	QWidget *m_setTop;

	QFrame *m_warp;

	QFrame *m_basic;
	CusButton *m_basicBtn;
	QLabel *m_basicLabel;

	QFrame *m_capture;
	CusButton *m_captureBtn;
	QLabel *m_captureLabel;

	QFrame *m_hotkey;
	CusButton *m_hotkeyBtn;
	QLabel *m_hotkeyLabel;

	QStackedWidget *m_mainSetLayout;
	QWidget *m_basicWidget;
	QWidget *m_captureWidget;
	QWidget *m_hotkeyWidget;

	QLabel *lb1;
	QLabel *lb2;
	QButtonGroup *m_stickGroup;
	QRadioButton *m_stickOnTopWhenPlay;
	QRadioButton *m_neverStickOnTop;
	QRadioButton *m_alwaysStickOnTop;

	QButtonGroup *m_locateGroup;
	QRadioButton *m_locateByTimestamp;
	QRadioButton *m_locateByFrame;

	QCheckBox *m_saveListExit;
	QCheckBox *m_hardWareDecode;

	QLabel *lb3;
	QLabel *lb4;
	QLabel *lb5;
	QLabel *lb6;
	QLabel *lb7;
	QLabel *lb8;
	QLabel *lb9;
	QLabel *lb10;
	QLabel *lb11;
	QLabel *lb12;
	QLabel *lb13;
	QLabel *lb14;
	QLabel *lb15;
	QLabel *lb16;
	QLabel *lb17;
	QLabel *lb18;
	QLabel *lb19;
	QLabel *lb20;
	QLabel *lb21;
	QLabel *lb22;
	QLabel *lb23;
	QLabel *lb24;
	QLabel *lb25;
	QLabel *lb26;
	QLabel *lb27;
	QLabel *lb28;
	QComboBox *m_picFormat;
	QLineEdit *m_savingPath;
	QPushButton *m_selectPath;
	QComboBox *m_mode;
	QSpinBox *m_interval;
	QSpinBox *m_maxPicNum;

	CusLineEdit *m_openFileEdit;
	CusLineEdit *m_fastForwardEdit;
	CusLineEdit *m_openDirEdit;
	CusLineEdit *m_slowForwardEdit;
	CusLineEdit *m_openUrlEdit;
	CusLineEdit *m_restoreNomalSpeedEdit;
	CusLineEdit *m_playOrPauseEdit;
	CusLineEdit *m_lastFrameEdit;
	CusLineEdit *m_stopEdit;
	CusLineEdit *m_firstFrameEdit;
	CusLineEdit *m_frameForwardEdit;
	CusLineEdit *m_captureEdit;
	CusLineEdit *m_frameBackWardEdit;
	CusLineEdit *m_normalOrFullScreenEdit;
	CusLineEdit *m_addVolumeEdit;
	CusLineEdit *m_lessVolumeEdit;
	CusLineEdit *m_repeatAtoBEdit;
	CusLineEdit *m_exitEdit;

	QString m_capturePath;
	QPushButton *m_basicRestore;
	QPushButton *m_captureRestore;
	QPushButton *m_hotkeyRestore;

	int m_index;

};


#endif