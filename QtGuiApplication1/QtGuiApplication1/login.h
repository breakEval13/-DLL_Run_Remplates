#pragma once

#include <QDialog>
#include "ui_login.h"

class login : public QDialog
{
	Q_OBJECT

public:
    explicit login(QWidget *parent = Q_NULLPTR);
	~login();

	void changeEvent(QEvent * e);
signals:
public slots :
	void on_closed_clicked();
	void on_logined_clicked();

public:
	Ui::login *ui;
};
