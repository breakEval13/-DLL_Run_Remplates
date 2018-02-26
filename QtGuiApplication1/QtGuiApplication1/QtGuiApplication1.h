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
		//槽函数，接收 value 变化信号
	void RecvValue(double v);
	void ClickButton();
	int LibLloader();
	//downloader 
	void downloaderDll();
	void onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);//下载过程  
	void onReplyFinished(int code, QString path);//获取响应的信息,状态码为200表示正常  
private:
	QTime downloadTime;
	SDownloadNetwork * m_downloadNetwork = 0;
	int m_nTime;

};
#endif // MAINWINDOW_H 