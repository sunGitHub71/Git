#pragma once
#ifndef CUSSLIDERTEST_H
#define CURSLIDERTEST_H

#include <QWidget>
#include "cusslider.h"

class CusSliderTest : public QWidget{
	Q_OBJECT
public:
	CusSliderTest(QWidget *parent = NULL);
	~CusSliderTest();

private:
	CusSlider *m_cusSlider;
};
#endif