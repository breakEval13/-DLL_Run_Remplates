#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "login.h"
#include "ui_login.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w;
	//主界面
	QObject::connect(w.ui.pushButton, &QPushButton::clicked, &w, &QtGuiApplication1::ClickButton);
	QObject::connect(w.ui.run_dll, SIGNAL(clicked()), &w, SLOT(downloaderDll()));
	/*QObject::connect(SIGNAL(onReplyFinished()),SLOT(LibLloader()));*/
	login log; //登陆界面
	QObject::connect(log.ui->logined, SIGNAL(clicked()), &log, SLOT(on_logined_clicked()));
	QObject::connect(log.ui->closed, SIGNAL(clicked()), &log, SLOT(on_closed_clicked()));

	if (log.exec() == QDialog::Accepted)
	{
		w.show();
		return a.exec();
	}
	else return 0;
}

