#pragma once
#ifndef DATETIMEEDIT_H
#define DATETIMEEDIT_H

#include <QDateTimeEdit>
#include <QCalendarWidget>

class DateTimeEdit : public QDateTimeEdit{
	Q_OBJECT
public:
	DateTimeEdit(QWidget *parent = NULL);
	~DateTimeEdit();
	void setCurDateTime();
	void setCalenderLan(QString lan);
public:
	QCalendarWidget *m_calender;
};


#endif