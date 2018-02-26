
#ifndef TOOLFUCTION_H  
#define TOOLFUCTION_H  
#include <QString>  
// 字节转KB、MB、GB  
QString toolSize(qint64 bytes)
{
	QString strUnit;
	double dSize = bytes * 1.0;
	if (dSize <= 0)
	{
		dSize = 0.0;
	}
	else if (dSize < 1024)
	{
		strUnit = "Bytes";
	}
	else if (dSize < 1024 * 1024)
	{
		dSize /= 1024;
		strUnit = "KB";
	}
	else if (dSize < 1024 * 1024 * 1024)
	{
		dSize /= (1024 * 1024);
		strUnit = "MB";
	}
	else
	{
		dSize /= (1024 * 1024 * 1024);
		strUnit = "GB";
	}

	return QString("%1 %2").arg(QString::number(dSize, 'f', 2)).arg(strUnit);
}

// 速度转KB/S、MB/S、GB/S  
QString speed(double speed)
{
	QString strUnit;
	if (speed <= 0)
	{
		speed = 0;
		strUnit = "Bytes/S";
	}
	else if (speed < 1024)
	{
		strUnit = "Bytes/S";
	}
	else if (speed < 1024 * 1024)
	{
		speed /= 1024;
		strUnit = "KB/S";
	}
	else if (speed < 1024 * 1024 * 1024)
	{
		speed /= (1024 * 1024);
		strUnit = "MB/S";
	}
	else
	{
		speed /= (1024 * 1024 * 1024);
		strUnit = "GB/S";
	}

	QString strSpeed = QString::number(speed, 'f', 2);
	return QString("%1 %2").arg(strSpeed).arg(strUnit);
}

// 秒转*d *h *m *s  
QString timeFormat(int seconds)
{
	QString strValue;
	QString strSpacing(" ");
	if (seconds <= 0)
	{
		strValue = QString("%1s").arg(0);
	}
	else if (seconds < 60)
	{
		strValue = QString("%1s").arg(seconds);
	}
	else if (seconds < 60 * 60)
	{
		int nMinute = seconds / 60;
		int nSecond = seconds - nMinute * 60;

		strValue = QString("%1m").arg(nMinute);

		if (nSecond > 0)
			strValue += strSpacing + QString("%1s").arg(nSecond);
	}
	else if (seconds < 60 * 60 * 24)
	{
		int nHour = seconds / (60 * 60);
		int nMinute = (seconds - nHour * 60 * 60) / 60;
		int nSecond = seconds - nHour * 60 * 60 - nMinute * 60;

		strValue = QString("%1h").arg(nHour);

		if (nMinute > 0)
			strValue += strSpacing + QString("%1m").arg(nMinute);

		if (nSecond > 0)
			strValue += strSpacing + QString("%1s").arg(nSecond);
	}
	else
	{
		int nDay = seconds / (60 * 60 * 24);
		int nHour = (seconds - nDay * 60 * 60 * 24) / (60 * 60);
		int nMinute = (seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60) / 60;
		int nSecond = seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60 - nMinute * 60;

		strValue = QString("%1d").arg(nDay);

		if (nHour > 0)
			strValue += strSpacing + QString("%1h").arg(nHour);

		if (nMinute > 0)
			strValue += strSpacing + QString("%1m").arg(nMinute);

		if (nSecond > 0)
			strValue += strSpacing + QString("%1s").arg(nSecond);
	}

	return strValue;
}

#endif // TOOLFUCTION_H  