#include "cusslidertest.h"
#include <QVBoxLayout>

CusSliderTest::CusSliderTest(QWidget *parent)
	:QWidget(parent){

	setFixedSize(400,200);
	m_cusSlider = new CusSlider(this);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setContentsMargins(100,0,0,0);
	vl->setSpacing(0);
	vl->addWidget(m_cusSlider);
	setLayout(vl);

}

CusSliderTest::~CusSliderTest(){

}