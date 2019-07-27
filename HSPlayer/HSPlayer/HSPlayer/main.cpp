#include "hsplayer.h"
#include "resource_tr.h"
#include "LogUtility.h"
#include <QtGui/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Hw_Set_Log_File((QCoreApplication::applicationDirPath()+"/HSPlayer.log").toUtf8().data(),(10*1024*1024),20,"");
	Hw_Set_Log_Level(log_info);
	//Language *lan = new Language();
	//lan->init(&a);

	HSPlayer w;

	QFile file(getPath() + PLAYER_CSS);
	
	file.open(QFile::ReadOnly);
	a.setStyleSheet(file.readAll());
	
	w.show();

	return a.exec();
}
