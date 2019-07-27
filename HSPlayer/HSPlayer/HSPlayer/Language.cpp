#include "language.h"
#include "resource_tr.h"
#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include <QLocale>
#include <QDebug>

Language::Language(QObject *parent)
	:QObject(parent){
	_myTranslator = NULL;
	_qtTranslator = NULL;

	_curCode = "en_US"; //Ĭ�� Ӣ��

}

Language::~Language(){
	
	if(_myTranslator)
	{
		delete _myTranslator;
		_myTranslator = NULL;
	}

	if(_qtTranslator)
	{
		delete _qtTranslator;
		_qtTranslator = NULL;
	}
}

void Language::init(){

	_createLanCodeMap();
	_createCodeLanMap();
}

//���ص�ǰ֧�ֵ������б�
const QStringList & Language::suportedLanguages(){
	//��������Ŀ¼�������������Ӧ��qm�ļ�������Ϊ�ǵ�ǰ֧�ֵ����ԣ���qm�ļ�������,�����ϲŻ���ʾ����
	if(_suportedLanguages.size()==0)
	{
		QDir dir(getPath() + "/translation/player/");
		QList<QFileInfo> files(dir.entryInfoList());
		for (int i=0;i<files.size();i++)
		{
			const QFileInfo & fi = files.at(i);

			if(fi.suffix()=="qm")
			{
				QString fileName = fi.baseName();
				QString code = fileName.right(5);
		
				if(code.left(2) != "qt")
				{
					if(_codeLanMap.find(code)!=_codeLanMap.end())
					{
						_suportedLanguages << _codeLanMap[code];
					}
				}
			}
		}

		_suportedLanguages.sort();
	}

	return _suportedLanguages;
}

QString Language::curLanguage(){
	
	if(_codeLanMap.find(_curCode)!=_codeLanMap.end())
	{
		return _codeLanMap[_curCode];
	}

	Q_ASSERT(false);
	return "";
}

QString Language::lanToCode(const QString & lan){
	if(_lanCodeMap.find(lan)!=_lanCodeMap.end())
	{
		return _lanCodeMap[lan];
	}

	return "";
}

QString Language::codeToLan(const QString & code){
	if(_codeLanMap.find(code)!=_codeLanMap.end())
	{
		return _codeLanMap[code];
	}

	return "";
}

QString Language::curCode() const{
	return _curCode;
}

void Language::_createLanCodeMap(){
	QString lan;
	lan = tr("Chinese Simplified");		_lanCodeMap[lan] = "zh_CN";   //���ļ���
	lan = tr("English");				_lanCodeMap[lan] = "en_US";   //Ӣ��
	lan = tr("Chinese Traditional");	_lanCodeMap[lan] = "zh_HK";   //���ķ���
	lan = tr("Russian");				_lanCodeMap[lan] = "ru_RU";   //����
	lan = tr("Korean");					_lanCodeMap[lan] = "ko_KR";   //����
	lan = tr("Polish");					_lanCodeMap[lan] = "pl_PL";   //����
	lan = tr("French");					_lanCodeMap[lan] = "fr_FR";   //����
	lan = tr("Japanese");				_lanCodeMap[lan] = "ja_JP";   //�ձ���
	lan = tr("Spanish");				_lanCodeMap[lan] = "es_ES";   //��������
	lan = tr("Portuguese");				_lanCodeMap[lan] = "pt_PT";   //��������
	lan = tr("Italian");				_lanCodeMap[lan] = "it_IT";   //�������
	lan = tr("Hebrew");					_lanCodeMap[lan] = "he_IL";   //ϣ������
	lan = tr("Turkish");				_lanCodeMap[lan] = "tr_TR";   //��������
	lan = tr("Bulgaria");				_lanCodeMap[lan] = "bg_BG";   //��������
	lan = tr("Persian");				_lanCodeMap[lan] = "fa_IR";   //��˹��
	lan = tr("German");					_lanCodeMap[lan] = "de_DE";   //����
	lan = tr("Dutch");					_lanCodeMap[lan] = "af_ZA";   //������
	lan = tr("Ukraine");				_lanCodeMap[lan] = "uk_UA";   //�ڿ�����
}

void Language::_createCodeLanMap(){
	QString code;
	code = "zh_CN";		_codeLanMap[code] = tr("Chinese Simplified");   //���ļ���
	code = "en_US";		_codeLanMap[code] = tr("English");				//Ӣ��
	code = "zh_HK";		_codeLanMap[code] = tr("Chinese Traditional");  //���ķ���
	code = "ru_RU";		_codeLanMap[code] = tr("Russian");				//����
	code = "ko_KR";		_codeLanMap[code] = tr("Korean");				//����
	code = "pl_PL";		_codeLanMap[code] = tr("Polish");				//����
	code = "fr_FR";		_codeLanMap[code] = tr("French");				//����
	code = "ja_JP";		_codeLanMap[code] = tr("Japanese");				//�ձ���
	code = "es_ES";		_codeLanMap[code] = tr("Spanish");				//��������
	code = "pt_PT";		_codeLanMap[code] = tr("Portuguese");			//��������
	code = "it_IT";		_codeLanMap[code] = tr("Italian");				//�������
	code = "he_IL";		_codeLanMap[code] = tr("Hebrew");				//ϣ������
	code = "tr_TR";		_codeLanMap[code] = tr("Turkish");				//��������
	code = "bg_BG";		_codeLanMap[code] = tr("Bulgaria");				//��������
	code = "fa_IR";		_codeLanMap[code] = tr("Persian");				//��˹��
	code = "de_DE";		_codeLanMap[code] = tr("German");				//����
	code = "af_ZA";		_codeLanMap[code] = tr("Dutch");				//������
	code = "uk_UA";		_codeLanMap[code] = tr("Ukraine");				//�ڿ�����
}