#pragma once

#include <QMainWindow>
#include "ui_StationerMainWindow.h"

/*��׼��*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc��protoЭ���*/
#include <grpcpp/grpcpp.h>
#include "../protocol/mystationer.grpc.pb.h"


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

	/*qt�����洰��*/
	QStandardItemModel* order_list_model;//�������ṹ


public slots:
	void GetStationerInfo();
	void InStation();//���
	void OutStation();//����
	void GetStationOrderList();//ˢ�µ�ǰ�����б�
	

private:
	Ui::StationerMainWindow ui;
};
