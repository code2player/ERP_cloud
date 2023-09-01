#pragma once

#include <QDialog>
#include "ui_UserCreateOrderWindow.h"

/*��׼��*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc��protoЭ���*/
#include <grpcpp/grpcpp.h>
#include "../protocol/myuser.grpc.pb.h"


/*QTר�ÿ�*/
#include <QMainWindow>
#include <QMessageBox>   //�������ܵ�ʵ��
#include <QTextBlock>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QDebug>
#include <QSpinBox>
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

using userspace::UserOrder;
using userspace::UserId;
using userspace::OrderItem;
using userspace::OrderList;
using userspace::OrderDetail;
using userspace::UpdateOrderStateRequest;
using userspace::BaseReply;

class UserCreateOrderWindow : public QDialog
{
	Q_OBJECT

public:
	UserCreateOrderWindow(const std::string passed_user_phone_, QWidget *parent = Q_NULLPTR);
	~UserCreateOrderWindow();

	std::string user_phone_;
	OrderDetail orderdetail_impl_;
	BaseReply basereply_impl_;

	QStandardItemModel* itemlist_model;//�������ṹ

public slots:
	void AddItem();
	void DelItem(const QModelIndex& index);
	void CreateOrder();//�ļ�





	void DoubleClickedTable(const QModelIndex& index);

	

private:
	Ui::UserCreateOrderWindow ui;
};
