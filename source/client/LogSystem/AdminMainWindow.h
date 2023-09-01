#pragma once

#include <QMainWindow>
#include "ui_AdminMainWindow.h"

/*标准库*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc及proto协议库*/
#include <grpcpp/grpcpp.h>
#include "../protocol/myadmin.grpc.pb.h"


/*QT专用库*/
#include <QMainWindow>
#include <QMessageBox>   //弹窗功能的实现
#include <QTextBlock>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QDebug>
#include "QDir"
#include "QFileDialog"
#include "QTextStream"
#include "QFile"


/*自定义库*/
#include "SystemDefine.h"


/*namespace*/
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using adminspace::AdminService;
using adminspace::AdminId;
using adminspace::ItemInfo;
using adminspace::AllItemList;
using adminspace::OrderInfo;
using adminspace::AllOrderList;
using adminspace::StationInfo;
using adminspace::AllStationList;
using adminspace::BaseReply3;



class AdminMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	AdminMainWindow(QWidget *parent = Q_NULLPTR);
	~AdminMainWindow();

	std::string return_message_;

	/*grpc通信*/
	AdminId admin_id_impl_;
	ItemInfo item_info_impl_;
	AllItemList item_list_impl_;
	OrderInfo order_info_impl_;
	AllOrderList order_list_impl_;
	StationInfo station_info_impl_;
	AllStationList station_list_impl_;
	BaseReply3 basereply_impl_;


	/*qt主界面窗口*/
	QStandardItemModel* itemlist_model;
	QStandardItemModel* stationlist_model;
	QStandardItemModel* orderlist_model;



public slots:
	/*实例按钮*/
	void GetAllItemList();
	void GetAllStationList();
	void GetAllOrderList();

	void AddItem();
	void DelItem();
	void AddStation();
	void DelStation();
	void UpdateOrder();

private:
	Ui::AdminMainWindow ui;
};
