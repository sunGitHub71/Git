#pragma 
#ifndef CUSLINEEDIT_H
#define CUSLINEEDIT_H

#include <QLineEdit>

class CusLineEdit : public QLineEdit {
	Q_OBJECT
public:
	CusLineEdit(QWidget *parent = NULL);
	~CusLineEdit();
protected:
	virtual void focusInEvent(QFocusEvent *event);
	virtual void focusOutEvent(QFocusEvent *event);
};

#endif