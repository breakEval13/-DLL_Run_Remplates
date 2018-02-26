#ifndef SDOWNLOADNETWORK_H  
#define SDOWNLOADNETWORK_H  
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>  
#include <QtNetwork/QNetworkReply>  

class SDownloadNetwork : public QNetworkAccessManager
{
	Q_OBJECT

public:
	explicit SDownloadNetwork(QObject *parent = 0);
	~SDownloadNetwork();
	void execute();
	public slots:
	void replyFinished(QNetworkReply *reply);
	void onAuthenticationRequest(QNetworkReply *reply, QAuthenticator *authenticator);
	void onNoAuthenticationRequest(QNetworkReply *reply);
	void readyRead();
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);//下载过程  
	void sigReplyFinished(int code, QString filePath);//获取响应的信息,状态码为200表示正常  
private:
	QNetworkReply * m_pReply = 0;
	QUrl m_url;
	QString m_strFileName;
	QString m_filePath;
};

#endif // SDOWNLOADNETWORK_H  