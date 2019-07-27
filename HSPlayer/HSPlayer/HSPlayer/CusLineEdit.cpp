#include "cuslineedit.h"
#include <QPainter>

CusLineEdit::CusLineEdit(QWidget *parent)
	:QLineEdit(parent){
	this->setReadOnly(true);
	setFixedSize(120,24);
	setObjectName("CusLineEdit");
	setStyleSheet("#CusLineEdit{border:1px solid #666666;background-color:rgb(51,51,51);} #CusLineEdit:hover{border:1px solid #d5cd00;}");

	QMargins margins = textMargins();
	setTextMargins(margins.left() + 5,margins.top(),margins.right(),margins.bottom());
}
CusLineEdit::~CusLineEdit(){

}
void CusLineEdit::focusInEvent(QFocusEvent *event){
	setStyleSheet("#CusLineEdit {border:1px solid #d5cd00;background-color:rgb(51,51,51);}");
	QLineEdit::focusInEvent(event);
}
void CusLineEdit::focusOutEvent(QFocusEvent *event){
	setStyleSheet("#CusLineEdit {border:1px solid #666666;background-color:rgb(51,51,51);}");
	QLineEdit::focusOutEvent(event);
}