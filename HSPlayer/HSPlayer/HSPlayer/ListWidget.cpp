#include "listwidget.h"
#include <QDebug>
#include <QMouseEvent>

ListWidget::ListWidget(QWidget *parent)
	:QListWidget(parent)
{
	this->setCurrentRow(10);  
	addItem("1");  
	addItem("2");  
	addItem("3");  
	addItem("4");  
	addItem("5");  
	addItem("6");  
	addItem("7");  
	addItem("8");  
	addItem("9");  
	addItem("10"); 
}
ListWidget::~ListWidget(){

}
void ListWidget::mousePressEvent(QMouseEvent *event){
	
}