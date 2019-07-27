#pragma once
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QTranslator>
#include <QStringList>
#include <map>

class Language : public QObject {
	Q_OBJECT
public:
	Language(QObject *parent = NULL);
	~Language();

	void init();
	const QStringList & suportedLanguages();
	QString curLanguage();
	QString curCode()const;
	QString lanToCode(const QString & lan);
	QString codeToLan(const QString & code);
private:
	void _createLanCodeMap();
	void _createCodeLanMap();
private:
	QTranslator *_myTranslator;
	QTranslator *_qtTranslator;

	QStringList _suportedLanguages;
	QString     _curCode; 

	std::map<QString,QString> _lanCodeMap; 
	std::map<QString,QString> _codeLanMap; 
};

#endif