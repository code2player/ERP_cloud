#pragma once

#include <QDialog>
#include "ui_LoginWindow.h"

class LoginWindow : public QDialog
{
	Q_OBJECT

public:
	std::string return_phone;
	int state_code;
	LoginWindow(QWidget *parent = Q_NULLPTR);
	~LoginWindow();

public slots:
	void login_to_server();
private:
	Ui::LoginWindow ui;
};
