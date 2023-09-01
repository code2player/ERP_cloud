#pragma once

#include <QDialog>
#include "ui_RegisterWindow.h"

class RegisterWindow : public QDialog
{
	Q_OBJECT

public:
	int state_code;
	RegisterWindow(QWidget *parent = Q_NULLPTR);
	~RegisterWindow();

public slots:
	void register_to_server();

private:
	Ui::RegisterWindow ui;
};
