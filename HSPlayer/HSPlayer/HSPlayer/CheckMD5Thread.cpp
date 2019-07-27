#include <CheckMD5Thread.h>

int get_sei_buffer(unsigned char * data, int size, unsigned char * buffer, int *count, int *nType)
{
	unsigned char * sei = data;
	int sei_type = 0;
	unsigned sei_size = 0;
	//payload type  
	do {
		sei_type += *sei;
		*nType = sei_type;
	} while (*sei++ == 255);
	//数据长度  
	do {
		sei_size += *sei;
	} while (*sei++ == 255);

	if (sei_size <= (data + size - sei) &&
		sei_type == 240 && sei_size > 0)
	{
		if (buffer != NULL && count != NULL)
		{
			if (*count > (int)sei_size)
			{
				memcpy(buffer, sei, sei_size);
			}
		}

		*count = sei_size;

		return sei_size;
	}
	return -1;
}

int getAllContent(FILE *fp, int strLen, unsigned *arr, unsigned *len, char *bufChar)
{
	if(!fp || !arr || !len) return 0;
	*len = 0;
	long pos = 0;
	long posEnd = 0;
	uchar *buf = (uchar*)malloc(1024*1024);
	uchar *buf2 = (uchar*)malloc(1024*1024);
	fseek(fp, 0, SEEK_END);
	posEnd = ftell(fp) -strLen;

	int res = 0;
	while (pos <= posEnd)
	{
		int flag = 0;
		fseek(fp, pos, SEEK_SET);//文件开头0字节位置
		res = fread(buf, sizeof(char), 1024*1024, fp);
		if (res < 7) break;
		for (int i =0; i < res; i++)
		{
			/*
			*SEI中取出水印
			*h264:00 00 00 01 06 0f 40
			*h265:00 00 00 01 0e 01 0f 40
			*/

			if(buf[i] == 0x00 && buf[i+1] == 0x00 && buf[i+2] == 0x00 && buf[i+3] == 0x01)
			{
				if (buf[i+4] == 0x06 && buf[i+5] == 0xf0)
				{	
					// H264
					memcpy(buf2, buf+i, res-i);
					//buf2 = (uchar*)buf+i;
					int nCount = 0;
					int nType = 0;
					int size = 0;

					unsigned char * sei = (unsigned char *)(buf2 + 5);
					nCount = size = res;
					get_sei_buffer(sei, ((unsigned char*)buf2 + size - sei), (uchar *)bufChar, &nCount, &nType);
					if ( 240 == nType)
					{
						flag = 1;
						break;
					}
				}
				else if (buf[i+4] == 0x4e && buf[i+5] == 0x01 && buf[i+6] == 0xf0)
				{
					//H265
					memcpy(buf2, buf+i, res-i);
					//buf2 = (uchar*)buf+i;
					int nCount = 0;
					int nType = 0;
					int size = 0;

					unsigned char * sei = (unsigned char *)(buf2 + 6);
					nCount = size = res;
					get_sei_buffer(sei, ((unsigned char*)buf2 + size - sei), (uchar *)bufChar, &nCount, &nType);
					if ( 240 == nType)
					{
						flag = 1;
						break;
					}
				}
			}
			
			
		}
		if (flag == 1)
		{
			break;
		}
		pos+=res;
	}
	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
	if (buf2 != NULL)
	{
		free(buf2);
		buf2 = NULL;
	}
	
	fseek(fp, 0, SEEK_SET);
	return 0;
}

int Decrypt(char string[], int stringLength, const char key[], int keyLength)
{
	int i = 0, j = 0, m = 0, n = 0, k = 3;
	m = stringLength;
	n = keyLength;
	if (string == NULL || key == NULL || n < m)
	{
		return -1;
	}
	for( i = 6; i < n; i++ )
	{
		if ( i%k == 1 )
		{
			if ( j < m )
			{
				string[j] = key[i];
				j++;
			}
			else
			{
				break;
			}
			
		}
	}
	string[m] = '\0';
	return 0;
}


CheckMD5Thread::CheckMD5Thread(QObject* parent)
	: QThread(parent)
{

}

CheckMD5Thread::~CheckMD5Thread()
{

}

void CheckMD5Thread::setFileString(QStringList filePaths)
{
	filePathList = filePaths;
}

void CheckMD5Thread::stopImmediately()
{
	QMutexLocker locker(&m_lock);
	m_isCanRun = false;
}

void CheckMD5Thread::run()
{
	m_isCanRun = true;
	QString itemFileName;
	QString itemFile;
	QString itemPercent;
	QString itemResults;
	QString itemVs;
	QStringList item;
	//将数据进行检测操作
	for (int i = 0; i < filePathList.size(); i++)
	{
		itemFileName = filePathList[i].mid(filePathList[i].lastIndexOf("\\")+1);
		itemPercent = "";
		itemResults = "";
		itemVs = "";
		itemFile = filePathList[i];
		item.clear();
		item.append(itemFileName);
		item.append(itemPercent);
		item.append(itemResults);
		item.append(itemVs);
		item.append(itemFile);
		//发送信号
		emit MsgSignal(item);
		QMutexLocker locker(&m_lock);
		if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
		{
			return;
		}
	}
	

	quint64 totalBytes = 0;
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = 0;
	quint64 loadSize = 1024 * 4;


	for (int i = 0; i < filePathList.size(); i++)
	{
		char* file;
		QByteArray ba = filePathList[i].toLocal8Bit();
		file = ba.data();
		FILE *fp = fopen(file, "rb");
		unsigned remoteArr[MAX_LEN] = {0};
		unsigned remoteArrLen = MAX_LEN;
		

		char charBuffer[80] = {};
		getAllContent(fp, 6, remoteArr, &remoteArrLen , charBuffer);
		itemFileName = filePathList[i].mid(filePathList[i].lastIndexOf("\\")+1);
					itemPercent = "";
					itemResults = "";
					itemVs = QString(QLatin1String((char*)charBuffer));
					itemFile = filePathList[i];
					item.clear();
					item.append(itemFileName);
					item.append(itemPercent);
					item.append(itemResults);
					item.append(itemVs);
					item.append(itemFile);
					//发送信号
					emit MsgSignalUpdate(item);
		fclose(fp);

		QCryptographicHash ch(QCryptographicHash::Md5);
		QByteArray buf;
		totalBytes = 0;
		bytesToWrite = 0;
		bytesWritten = 0;
		QString filePath = filePathList[i];
		QFile localFile(filePath);
		if (!localFile.open(QFile::ReadOnly))
		{
			return;
		}
		//MD5值128个比特位，32位长度
		/*
		*说明：理论上应该是32位，但是我们后端加密时会再文件末尾产生换行符因此需用33截取处理
		*	后端采用第三方，因此此处应该长期不需要改回32位
		*/
		int beginNum = localFile.size() - 128;
		localFile.seek(beginNum);
		QByteArray buffMD5 = localFile.read(128);
		char *MD5Encryption = buffMD5.data();

		char string[33] = "";
		int stringLength = 32;
		//解密算法
		Decrypt(string, stringLength, MD5Encryption, 128);

		localFile.close();

		localFile.open(QFile::ReadOnly);
		totalBytes = localFile.size();
		bytesToWrite = totalBytes-128;

		itemFileName = filePath.mid(filePath.lastIndexOf("\\")+1);
		itemFile = filePath;
		while (1)
		{
			if(bytesToWrite > 0)
			{
				buf = localFile.read(qMin(bytesToWrite, loadSize));
				ch.addData(buf);
				bytesWritten += buf.length();
				bytesToWrite -= buf.length();
				buf.resize(0);
			}
			else
			{
				break;
			}
			int percent = bytesWritten*100/totalBytes;
			//将进度传出去


			itemPercent = QString::number(percent) + "%";

			item.clear();
			item.append(itemFileName);
			item.append(itemPercent);
			item.append(itemResults);
			item.append(itemVs);
			item.append(itemFile);

			//发送信号
			emit MsgSignalUpdate(item);

			if(bytesWritten == totalBytes)
			{
				itemPercent = "100%";
				item.clear();
				item.append(itemFileName);
				item.append(itemPercent);
				item.append(itemResults);
				item.append(itemVs);
				item.append(itemFile);
				emit MsgSignalUpdate(item);
				break;
			}
			QMutexLocker locker(&m_lock);
			if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
			{
				return;
			}
		}

		localFile.close();
		QByteArray md5 = ch.result();
		//toHex()返回字节编码的十六进制拷贝
		//if (md5.toHex() == QByteArray(string))
		QString a = QString(md5.toHex().data());
		if (QString(md5.toHex().data()).compare(string, Qt::CaseInsensitive) == 0)
		{
			//代表成功，
			itemPercent = "100%";
			itemResults = tr("original");

		}
		else
		{
			itemPercent = "100%";
			itemResults = tr("un original");
		}
		
		item.clear();
		item.append(itemFileName);
		item.append(itemPercent);
		item.append(itemResults);
		item.append(itemVs);
		item.append(itemFile);
		emit MsgSignalUpdate(item);
		QMutexLocker locker(&m_lock);
		if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
		{
			return;
		}
	}
	//结束发送结束信息
	emit MsgSignalOver();
}