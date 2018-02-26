#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H  
#include "sdownloadnetwork.h"  
#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT
public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
    ~QtGuiApplication1();
public:
	Ui::QtGuiApplication1Class ui;

signals:
	public slots :
		//�ۺ��������� value �仯�ź�
	void RecvValue(double v);
	void ClickButton();
	int LibLloader();
	//downloader 
	void downloaderDll();
	void onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);//���ع���  
	void onReplyFinished(int code, QString path);//��ȡ��Ӧ����Ϣ,״̬��Ϊ200��ʾ����  
private:
	QTime downloadTime;
	SDownloadNetwork * m_downloadNetwork = 0;
	int m_nTime;

};
#endif // MAINWINDOW_H 