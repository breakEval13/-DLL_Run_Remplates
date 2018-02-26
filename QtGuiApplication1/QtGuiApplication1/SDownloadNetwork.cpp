#include "SDownloadNetwork.h"  
#include <QDateTime>  
#include <QFileInfo>  
#include <QSsl>   
#include <QSslConfiguration>   
#include <QSslSocket>   

SDownloadNetwork::SDownloadNetwork(QObject *parent) : QNetworkAccessManager(parent)
{
	// ��ȡ��ǰ��ʱ������������ص���ʱ�ļ�����  
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("yyyy-MM-dd-hh-mm-ss-zzz");
	m_strFileName = QString("E:/%0.tmp").arg(date);

	connect(this, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
}

SDownloadNetwork::~SDownloadNetwork()
{
	// ��ֹ����  
	if (m_pReply != NULL)
	{
		m_pReply->abort();
		m_pReply->deleteLater();
	}
}

// ����URL����Ϣͷ����ʼ����  
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
	// ��ȡ��Ӧ����Ϣ��״̬��Ϊ200��ʾ����  
	QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	// �޴��󷵻�  
	if (reply->error() == QNetworkReply::NoError) {
		// ��������ʱ�ļ�  
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

// �û���֤  
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
// ����д�ļ�  
void SDownloadNetwork::readyRead()
{
	QFileInfo fileInfo(m_strFileName);
	QFileInfo newFileInfo = fileInfo.absolutePath() + m_url.fileName();
	m_filePath = newFileInfo.absoluteFilePath();

	// д�ļ�-��ʽΪ׷��  
	QFile file(m_strFileName);
	if (file.open(QIODevice::Append)) {
		file.write(m_pReply->readAll());
	}
	file.close();
}
