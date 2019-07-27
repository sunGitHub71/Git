#pragma once
#ifndef BASICSETITEM_H
#define BASICSETITEM_H
#include <QString>

typedef struct _tagBasicSetItem{
	bool isStickOnTopWhenPlay;
	bool isNeverStickOnTop;
	bool isAlwayOnTop;
	bool locateByTimestamp;
	bool locateByFrame;
	bool saveListWhenLeave;
	bool hardwareDocode;
}BASIC_SET_ITEM;


typedef struct _tagCaptureSetItem{
	int format;
	QString savePath;
	int Mode;
	int interval;
	int maxCaptureNum;
}CAPTURE_SET_ITEM;

typedef struct _tagHotkeySetItem{
	QString openFile;
	QString fastForward;
	QString openDir;
	QString slowForward;
	QString openUrl;
	QString restoreNormalSpeed;
	QString playOrPause;
	QString lastFrame;
	QString frameForward;
	QString firstFrame;
	QString capture;
	QString stop;
	QString frameBackward;
	QString normalAndFullScreen;
	QString addVolume;
	QString lessVolume;
	QString repeatAtoB;
	QString exit;
}HOTKEY_SET_ITEM;
#endif