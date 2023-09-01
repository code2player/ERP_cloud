#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogSystem.h"

class LogSystem : public QMainWindow
{
	Q_OBJECT

public:
	LogSystem(QWidget *parent = Q_NULLPTR);

public slots:
	//void recv_loginwindow();//初始化，从loginwindow中接收数据

private:
	Ui::LogSystemClass ui;
};
