#include "datetimeedit.h"
#include <QTextCharFormat>

DateTimeEdit::DateTimeEdit(QWidget *parent)
	:QDateTimeEdit(parent)
{
	
	setMinimumDate(QDate(2016, 1, 1));
	setMaximumDate(QDate(2050, 1, 1));
	setCalendarPopup(true);

	m_calender = new QCalendarWidget;

	//ÉèÖÃÓïÑÔ
	//m_calender->setLocale(QLocale(QLocale::French));
	m_calender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	m_calender->setFixedWidth(240);

	setCalendarWidget(m_calender);

	m_calender->disconnect(SIGNAL(clicked(QDate)));
}
DateTimeEdit::~DateTimeEdit()
{

}
void DateTimeEdit::setCurDateTime()
{
	QDateTime currDateTime = QDateTime::currentDateTime();
	setDateTime(currDateTime);
}

void DateTimeEdit::setCalenderLan(QString lan)
{
	if (lan.isEmpty())
	{
		return;
	}else if (lan == "zh_CN")
	{
		m_calender->setLocale(QLocale(QLocale::Chinese));
	}else if (lan == "en_US")
	{
		m_calender->setLocale(QLocale(QLocale::English));
	}else if (lan == "zh_HK")
	{
		m_calender->setLocale(QLocale(QLocale::Chinese));
	}else if (lan == "ru_RU")
	{
		m_calender->setLocale(QLocale(QLocale::Russian));
	}else if (lan == "ko_KR")
	{
		m_calender->setLocale(QLocale(QLocale::Korean));
	}else if (lan == "pl_PL")
	{
		m_calender->setLocale(QLocale(QLocale::Polish));
	}else if (lan == "fr_FR")
	{
		m_calender->setLocale(QLocale(QLocale::French));
	}else if (lan == "ja_JP")
	{
		m_calender->setLocale(QLocale(QLocale::Japanese));
	}else if (lan == "es_ES")
	{
		m_calender->setLocale(QLocale(QLocale::Spanish));
	}else if (lan == "pt_PT")
	{
		m_calender->setLocale(QLocale(QLocale::Portuguese));
	}else if (lan == "it_IT")
	{
		m_calender->setLocale(QLocale(QLocale::Italian));
	}else if (lan == "he_IL")
	{
		m_calender->setLocale(QLocale(QLocale::Hebrew));
	}else if (lan == "tr_TR")
	{
		m_calender->setLocale(QLocale(QLocale::Turkish));
	}else if (lan == "bg_BG")
	{
		m_calender->setLocale(QLocale(QLocale::Bulgarian));
	}else if (lan == "fa_IR")
	{
		m_calender->setLocale(QLocale(QLocale::Persian));
	}else if (lan == "de_DE")
	{
		m_calender->setLocale(QLocale(QLocale::German));
	}else if (lan == "af_ZA")
	{
		m_calender->setLocale(QLocale(QLocale::Dutch));
	}else if (lan == "uk_UA")
	{
		m_calender->setLocale(QLocale(QLocale::Ukrainian));
	}
}
