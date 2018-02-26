#include "QtGuiApplication1.h"
#include <QDebug>
#include <QApplication>  
#include <QLibrary>  
#include <QDebug>  
#include <QMessageBox>  
#include "toolfuction.h"
#include <QDebug>
#include <qmath.h>  
#include <QMainWindow>
#include "QtGuiApplication1.h"
//引入头文件  
typedef int(*Fun)(int, int); //定义函数指针，以备调用 
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{	
	ui.setupUi(this);  
	m_downloadNetwork = new SDownloadNetwork(this);
	connect(m_downloadNetwork, SIGNAL(downloadProgress(qint64, qint64)),
		this, SLOT(onDownloadProcess(qint64, qint64)), Qt::QueuedConnection);
	connect(m_downloadNetwork, SIGNAL(sigReplyFinished(int, QString)),
		this, SLOT(onReplyFinished(int, QString)), Qt::QueuedConnection);
}
void QtGuiApplication1::ClickButton()
{
	//what you want to do
	//QMessageBox::information(this, "My Tittle", "Hello World!");
	ui.pushButton->setText("status");

}
//接收并打印 value 变化后的新值
void QtGuiApplication1::RecvValue(double v)
{
	qDebug() << "RecvValue: " << fixed << v;
}
QtGuiApplication1::~QtGuiApplication1()
{
}
int QtGuiApplication1::LibLloader()
{
	QLibrary mylib("mydll.dll");   //声明所用到的dll文件  
	int result;
	if (mylib.load())              //判断是否正确加载  
	{
		QMessageBox::information(NULL, "OK", "DLL load is OK!");
		Fun open = (Fun)mylib.resolve("add");    //援引 add() 函数  
		if (open)                  //是否成功连接上 add() 函数  
		{
			QMessageBox::information(NULL, "OK", "Link to Function is OK!");
			result = open(5, 6);      //这里函数指针调用dll中的 add() 函数  
			QMessageBox::information(NULL, "OK", result +"");
		}
		else
			QMessageBox::information(NULL, "NO", "Linke to Function is not OK!!!!");
	}
	else
		QMessageBox::information(NULL, "NO", "DLL is not loaded!");
	return 0;  //加载失败则退出28
}  


void QtGuiApplication1::downloaderDll()
{
	m_downloadNetwork->execute(); //ui.lineEdit->text()
	downloadTime.start();
	m_nTime = 0;
}
// 计算下载大小、速度、剩余时间  
void QtGuiApplication1::onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
	QString text;
	// 总时间  
	int nTime = downloadTime.elapsed();//返回从上一次调用start所用的时间  
									   // 本次下载所用时间  
	nTime -= m_nTime;

	// 下载速度  
	double dBytesSpeed = (bytesReceived * 1000.0) / nTime;
	double dSpeed = dBytesSpeed;

	//剩余时间  
	qint64 leftBytes = (bytesTotal - bytesReceived);
	double dLeftTime = (leftBytes * 1.0) / dBytesSpeed;

	text.append(" Speed:" + speed(dSpeed));
	text.append("\n Lave time:" + timeFormat(qCeil(dLeftTime)));
	text.append("\n File total Size:" + toolSize(bytesTotal));
	text.append("\n Download Size:" + toolSize(bytesReceived));

	ui.progressBar->setMaximum(bytesTotal);
	ui.progressBar->setValue(bytesReceived);
	ui.text->setText(text);
	// 获取上一次的时间  
	m_nTime = nTime;
}
void QtGuiApplication1::onReplyFinished(int code, QString path)
{
	bool b = code == 200;
	// QMessageBox::information(this, "DownLoad", b ? "Success" : "Fail");
	(b ? emit LibLloader() : QMessageBox::information(this, "DownLoad", b ? "Success" : "Fail"));
	
	qDebug() << "Path:" << path;
}