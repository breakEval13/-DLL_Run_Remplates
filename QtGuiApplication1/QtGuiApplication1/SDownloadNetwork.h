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
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);//���ع���  
	void sigReplyFinished(int code, QString filePath);//��ȡ��Ӧ����Ϣ,״̬��Ϊ200��ʾ����  
private:
	QNetworkReply * m_pReply = 0;
	QUrl m_url;
	QString m_strFileName;
	QString m_filePath;
};

#endif // SDOWNLOADNETWORK_H  