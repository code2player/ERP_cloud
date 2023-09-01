#pragma once

#include <QMainWindow>
#include "ui_AdminMainWindow.h"

/*��׼��*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc��protoЭ���*/
#include <grpcpp/grpcpp.h>
#include "../protocol/myadmin.grpc.pb.h"


/*QTר�ÿ�*/
#include <QMainWindow>
#include <QMessageBox>   //�������ܵ�ʵ��
#include <QTextBlock>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QDebug>
#include "QDir"
#include "QFileDialog"
#include "QTextStream"
#include "QFile"


/*�Զ����*/
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

	/*grpcͨ��*/
	AdminId admin_id_impl_;
	ItemInfo item_info_impl_;
	AllItemList item_list_impl_;
	OrderInfo order_info_impl_;
	AllOrderList order_list_impl_;
	StationInfo station_info_impl_;
	AllStationList station_list_impl_;
	BaseReply3 basereply_impl_;


	/*qt�����洰��*/
	QStandardItemModel* itemlist_model;
	QStandardItemModel* stationlist_model;
	QStandardItemModel* orderlist_model;



public slots:
	/*ʵ����ť*/
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
