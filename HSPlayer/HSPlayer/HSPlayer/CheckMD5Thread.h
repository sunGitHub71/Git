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
	void MsgSignal(QStringList tep);   //�����ļ����ȴ������̣߳� ������
	void MsgSignalUpdate(QStringList tep);	  //�����
	void MsgSignalOver();					//�ļ����ͽ���
public:
	CheckMD5Thread(QObject* parent);
	~CheckMD5Thread();
	void setFileString(QStringList filePaths);
	void run();
	
public slots:
	void stopImmediately();

protected:
	QStringList filePathList;				//�ļ���ַ�б�
private:
	QMutex m_lock;
	bool m_isCanRun;
};

#endif