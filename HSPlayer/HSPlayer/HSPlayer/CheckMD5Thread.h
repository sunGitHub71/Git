#ifndef CHECKMD5THREAD_H
#define CHECKMD5THREAD_H

#include <stdio.h>
#include <QThread>
#include <QCryptographicHash>
#include <QStringList>
#include <QMutex>
#include <QFile>
#include <QMutexLocker>
#define MAX_LEN 10000

class CheckMD5Thread : public QThread
{
	Q_OBJECT

signals:
	void MsgSignal(QStringList tep);   //将读文件进度传回主线程， 更新行
	void MsgSignalUpdate(QStringList tep);	  //添加行
	void MsgSignalOver();					//文件发送结束
public:
	CheckMD5Thread(QObject* parent);
	~CheckMD5Thread();
	void setFileString(QStringList filePaths);
	void run();
	
public slots:
	void stopImmediately();

protected:
	QStringList filePathList;				//文件地址列表
private:
	QMutex m_lock;
	bool m_isCanRun;
};

#endif