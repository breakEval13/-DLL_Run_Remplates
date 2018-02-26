#include "login.h"
#include <QMessageBox>
#include <QDebug>
login::login(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::login)
{
	ui->setupUi(this);
}

login::~login()
{
	delete ui;
}

void login::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void login::on_logined_clicked()
{
	if (this->ui->txtpwd->text().trimmed() == tr("admin") &&
		this->ui->txtname->text().trimmed() == tr("admin"))
	{
		accept();
	}
	else
	{
		QMessageBox::warning(this, tr("warning"), tr("username or password is error!"), QMessageBox::Yes);
		this->ui->txtname->clear();
		this->ui->txtpwd->clear();
		this->ui->txtname->setFocus();
	}
}

void login::on_closed_clicked()
{
	this->close();
}