#include "SDownloadNetwork.h"  
#include <QDateTime>  
#include <QFileInfo>  
#include <QSsl>   
#include <QSslConfiguration>   
#include <QSslSocket>   

SDownloadNetwork::SDownloadNetwork(QObject *parent) : QNetworkAccessManager(parent)
{
	// 获取当前的时间戳，设置下载的临时文件名称  
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("yyyy-MM-dd-hh-mm-ss-zzz");
	m_strFileName = QString("E:/%0.tmp").arg(date);

	connect(this, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
}

SDownloadNetwork::~SDownloadNetwork()
{
	// 终止下载  
	if (m_pReply != NULL)
	{
		m_pReply->abort();
		m_pReply->deleteLater();
	}
}

// 设置URL及消息头，开始请求  
void SDownloadNetwork::execute()
{
	QString path = "http://download.skycn.com/hao123-soft-online-bcs/soft/Q/QvodSetupPlus5_5.20.234-hao123.exe";
	m_url = QUrl(path);

	QSslConfiguration config;
	// config tls 0 1 2 for http downloader to files
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	QNetworkRequest request;
	request.setUrl(m_url);
	request.setSslConfiguration(config);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/zip");

	/*connect(this, SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
		this, SLOT(onAuthenticationRequest(QNetworkReply *, QAuthenticator *)));
*/
	connect(this, SIGNAL(authenticationRequired(QNetworkReply *)),
		this, SLOT(onNoAuthenticationRequest(QNetworkReply *)));


	m_pReply = get(request);
	connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
	connect(m_pReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

#include <QDir>  
void SDownloadNetwork::replyFinished(QNetworkReply *reply)
{
	// 获取响应的信息，状态码为200表示正常  
	QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	// 无错误返回  
	if (reply->error() == QNetworkReply::NoError) {
		// 重命名临时文件  
		QFileInfo fileInfo(m_strFileName);
		QFileInfo newFileInfo = fileInfo.absolutePath() + m_url.fileName();
		QDir dir;
		if (dir.exists(fileInfo.absolutePath()))
		{
			if (newFileInfo.exists())
				newFileInfo.dir().remove(newFileInfo.fileName());
			QFile::rename(m_strFileName, newFileInfo.absoluteFilePath());
		}
	}
	else {
		QString strError = reply->errorString();
		qDebug() << "Error:" << strError;
	}

	emit sigReplyFinished(statusCode.toInt(), m_filePath);
}

// 用户认证  
void SDownloadNetwork::onAuthenticationRequest(QNetworkReply *reply, QAuthenticator *authenticator)
{
#ifdef User  
	QByteArray password;
	password.append("123456");
	password = QByteArray::fromBase64(password);
	QString strPassword(password);
	authenticator->setUser("wang");
	authenticator->setPassword(strPassword);
#endif  
}

void SDownloadNetwork::onNoAuthenticationRequest(QNetworkReply *reply)
{
}

//http://zmatsh.b0.upaiyun.com/PUBG_FUCK.zip
// 本地写文件  
void SDownloadNetwork::readyRead()
{
	QFileInfo fileInfo(m_strFileName);
	QFileInfo newFileInfo = fileInfo.absolutePath() + m_url.fileName();
	m_filePath = newFileInfo.absoluteFilePath();

	// 写文件-形式为追加  
	QFile file(m_strFileName);
	if (file.open(QIODevice::Append)) {
		file.write(m_pReply->readAll());
	}
	file.close();
}
