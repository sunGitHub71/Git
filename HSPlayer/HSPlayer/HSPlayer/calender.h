#pragma  once
#ifndef CALENDER_H
#define CALENDER_H

#include <QCalendarWidget>


class Calender : public QCalendarWidget {
	Q_OBJECT

public:
	Calender(QWidget *parent = NULL);
	~Calender();
public slots:
	void setToday();
};
#endif