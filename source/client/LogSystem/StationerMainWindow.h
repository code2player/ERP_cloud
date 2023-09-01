#pragma once

#include <QMainWindow>
#include "ui_StationerMainWindow.h"

/*标准库*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc及proto协议库*/
#include <grpcpp/grpcpp.h>
#include "../protocol/mystationer.grpc.pb.h"


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


using stationerspace::StationerOrder;
using stationerspace::StationId;
using stationerspace::SaveOrder;
using stationerspace::SaveOrderList;
using stationerspace::InStationRequest;
using stationerspace::OutStationRequest;
using stationerspace::StationerInfo;
using stationerspace::StationerId;
using stationerspace::BaseReply2;


class StationerMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	StationerMainWindow(QWidget *parent = Q_NULLPTR);
	~StationerMainWindow();

	//int flagx = 0;

	StationerId userid_impl_;
	StationId stationid_impl_;
	SaveOrderList save_order_list_impl_;
	StationerInfo stationer_info__impl_;
	InStationRequest in_station_request_impl_;
	OutStationRequest out_station_request_impl_;
	BaseReply2 basereply_impl_;

	/*qt主界面窗口*/
	QStandardItemModel* order_list_model;//主界面表结构


public slots:
	void GetStationerInfo();
	void InStation();//入库
	void OutStation();//出库
	void GetStationOrderList();//刷新当前函数列表
	

private:
	Ui::StationerMainWindow ui;
};
