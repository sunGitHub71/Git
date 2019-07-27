#include "calender.h"

Calender::Calender(QWidget *parent) 
	: QCalendarWidget(parent){
	setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	setFixedWidth(240);
	setDateRange(QDate(2017,1,1),QDate(2050,1,1));

	setToday();
}

Calender::~Calender(){

}

void Calender::setToday(){
	QDate curdate = QDate::currentDate();
	this->setSelectedDate(curdate);
}