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

	_curCode = "en_US"; //默认 英文

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

//返回当前支持的语言列表
const QStringList & Language::suportedLanguages(){
	//遍历语言目录，如果里面有相应的qm文件，则认为是当前支持的语言，有qm文件的语言,界面上才会显示出来
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
	lan = tr("Chinese Simplified");		_lanCodeMap[lan] = "zh_CN";   //中文简体
	lan = tr("English");				_lanCodeMap[lan] = "en_US";   //英语
	lan = tr("Chinese Traditional");	_lanCodeMap[lan] = "zh_HK";   //中文繁体
	lan = tr("Russian");				_lanCodeMap[lan] = "ru_RU";   //俄文
	lan = tr("Korean");					_lanCodeMap[lan] = "ko_KR";   //韩语
	lan = tr("Polish");					_lanCodeMap[lan] = "pl_PL";   //波兰
	lan = tr("French");					_lanCodeMap[lan] = "fr_FR";   //法语
	lan = tr("Japanese");				_lanCodeMap[lan] = "ja_JP";   //日本语
	lan = tr("Spanish");				_lanCodeMap[lan] = "es_ES";   //西班牙语
	lan = tr("Portuguese");				_lanCodeMap[lan] = "pt_PT";   //葡萄牙语
	lan = tr("Italian");				_lanCodeMap[lan] = "it_IT";   //意大利语
	lan = tr("Hebrew");					_lanCodeMap[lan] = "he_IL";   //希伯来语
	lan = tr("Turkish");				_lanCodeMap[lan] = "tr_TR";   //土耳其语
	lan = tr("Bulgaria");				_lanCodeMap[lan] = "bg_BG";   //保加利亚
	lan = tr("Persian");				_lanCodeMap[lan] = "fa_IR";   //波斯语
	lan = tr("German");					_lanCodeMap[lan] = "de_DE";   //德语
	lan = tr("Dutch");					_lanCodeMap[lan] = "af_ZA";   //荷兰语
	lan = tr("Ukraine");				_lanCodeMap[lan] = "uk_UA";   //乌克兰语
}

void Language::_createCodeLanMap(){
	QString code;
	code = "zh_CN";		_codeLanMap[code] = tr("Chinese Simplified");   //中文简体
	code = "en_US";		_codeLanMap[code] = tr("English");				//英语
	code = "zh_HK";		_codeLanMap[code] = tr("Chinese Traditional");  //中文繁体
	code = "ru_RU";		_codeLanMap[code] = tr("Russian");				//俄文
	code = "ko_KR";		_codeLanMap[code] = tr("Korean");				//韩语
	code = "pl_PL";		_codeLanMap[code] = tr("Polish");				//波兰
	code = "fr_FR";		_codeLanMap[code] = tr("French");				//法语
	code = "ja_JP";		_codeLanMap[code] = tr("Japanese");				//日本语
	code = "es_ES";		_codeLanMap[code] = tr("Spanish");				//西班牙语
	code = "pt_PT";		_codeLanMap[code] = tr("Portuguese");			//葡萄牙语
	code = "it_IT";		_codeLanMap[code] = tr("Italian");				//意大利语
	code = "he_IL";		_codeLanMap[code] = tr("Hebrew");				//希伯来语
	code = "tr_TR";		_codeLanMap[code] = tr("Turkish");				//土耳其语
	code = "bg_BG";		_codeLanMap[code] = tr("Bulgaria");				//保加利亚
	code = "fa_IR";		_codeLanMap[code] = tr("Persian");				//波斯语
	code = "de_DE";		_codeLanMap[code] = tr("German");				//德语
	code = "af_ZA";		_codeLanMap[code] = tr("Dutch");				//荷兰语
	code = "uk_UA";		_codeLanMap[code] = tr("Ukraine");				//乌克兰语
}