#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogSystem.h"

class LogSystem : public QMainWindow
{
	Q_OBJECT

public:
	LogSystem(QWidget *parent = Q_NULLPTR);

public slots:
	//void recv_loginwindow();//��ʼ������loginwindow�н�������

private:
	Ui::LogSystemClass ui;
};
