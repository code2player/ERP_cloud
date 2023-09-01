#pragma once

#include <QDialog>
#include "ui_StartPage.h"

class SysStartPage : public QDialog
{
	Q_OBJECT

public:
	int state_code;
	SysStartPage(QWidget *parent = Q_NULLPTR);
	~SysStartPage();

public slots:
	void register_user();
	void register_stationer();
	void register_admin();
	void login_user();
	void login_stationer();
	void login_admin();


private:
	Ui::StartPage ui;
};
