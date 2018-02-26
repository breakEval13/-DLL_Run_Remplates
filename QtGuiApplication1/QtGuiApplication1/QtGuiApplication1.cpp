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
//����ͷ�ļ�  
typedef int(*Fun)(int, int); //���庯��ָ�룬�Ա����� 
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
//���ղ���ӡ value �仯�����ֵ
void QtGuiApplication1::RecvValue(double v)
{
	qDebug() << "RecvValue: " << fixed << v;
}
QtGuiApplication1::~QtGuiApplication1()
{
}
int QtGuiApplication1::LibLloader()
{
	QLibrary mylib("mydll.dll");   //�������õ���dll�ļ�  
	int result;
	if (mylib.load())              //�ж��Ƿ���ȷ����  
	{
		QMessageBox::information(NULL, "OK", "DLL load is OK!");
		Fun open = (Fun)mylib.resolve("add");    //Ԯ�� add() ����  
		if (open)                  //�Ƿ�ɹ������� add() ����  
		{
			QMessageBox::information(NULL, "OK", "Link to Function is OK!");
			result = open(5, 6);      //���ﺯ��ָ�����dll�е� add() ����  
			QMessageBox::information(NULL, "OK", result +"");
		}
		else
			QMessageBox::information(NULL, "NO", "Linke to Function is not OK!!!!");
	}
	else
		QMessageBox::information(NULL, "NO", "DLL is not loaded!");
	return 0;  //����ʧ�����˳�28
}  


void QtGuiApplication1::downloaderDll()
{
	m_downloadNetwork->execute(); //ui.lineEdit->text()
	downloadTime.start();
	m_nTime = 0;
}
// �������ش�С���ٶȡ�ʣ��ʱ��  
void QtGuiApplication1::onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
	QString text;
	// ��ʱ��  
	int nTime = downloadTime.elapsed();//���ش���һ�ε���start���õ�ʱ��  
									   // ������������ʱ��  
	nTime -= m_nTime;

	// �����ٶ�  
	double dBytesSpeed = (bytesReceived * 1000.0) / nTime;
	double dSpeed = dBytesSpeed;

	//ʣ��ʱ��  
	qint64 leftBytes = (bytesTotal - bytesReceived);
	double dLeftTime = (leftBytes * 1.0) / dBytesSpeed;

	text.append(" Speed:" + speed(dSpeed));
	text.append("\n Lave time:" + timeFormat(qCeil(dLeftTime)));
	text.append("\n File total Size:" + toolSize(bytesTotal));
	text.append("\n Download Size:" + toolSize(bytesReceived));

	ui.progressBar->setMaximum(bytesTotal);
	ui.progressBar->setValue(bytesReceived);
	ui.text->setText(text);
	// ��ȡ��һ�ε�ʱ��  
	m_nTime = nTime;
}
void QtGuiApplication1::onReplyFinished(int code, QString path)
{
	bool b = code == 200;
	// QMessageBox::information(this, "DownLoad", b ? "Success" : "Fail");
	(b ? emit LibLloader() : QMessageBox::information(this, "DownLoad", b ? "Success" : "Fail"));
	
	qDebug() << "Path:" << path;
}