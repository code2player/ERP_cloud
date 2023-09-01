#pragma once

#include <QMainWindow>
#include "ui_UserMainWindow.h"
#include "UserCreateOrderWindow.h"


/*标准库*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc及proto协议库*/
#include <grpcpp/grpcpp.h>
#include "../protocol/myuser.grpc.pb.h"


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

using userspace::UserOrder;
using userspace::UserId;
using userspace::OrderItem;
using userspace::OrderList;
using userspace::OrderDetail;
using userspace::UpdateOrderStateRequest;
using userspace::BaseReply;

using userspace::OrderId;
using userspace::OrderTransport;
using userspace::SpecificOrder;

/*普通用户、工作人员、管理员等公用*/
class UserBase {
public:
	std::string user_phone_;//作为查询id
	std::string user_identity_;//用户身份

};

class User : public UserBase
{

};


class UserMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	UserMainWindow(QWidget *parent = Q_NULLPTR);
	~UserMainWindow();

	/*grpc通信*/
	User user_impl_;
	UserId userid_impl_;
	OrderList order_list_impl_;

	OrderId orderid_impl_;
	SpecificOrder specific_order_impl_;

	UpdateOrderStateRequest update_state_impl;
	BaseReply basereply_impl_;


	/*qt主界面窗口*/
	QStandardItemModel* sender_model;//主界面表结构
	QStandardItemModel* receiver_model;//

	QStandardItemModel* detail_model;//
	QStandardItemModel* transport_model;//
	QStandardItemModel* itemlist_model;//


	QModelIndex now_index;//当前选中的表项（如果有的话）


	/*内部函数*/
	void ShowOrderDetail(const QModelIndex& index);
	void ShowOrderItemList();
	void ShowOrderTransportList();

public slots:
	/*用例*/
	void CreateOrder();//寄件
	void GetOrderList();//刷新订单列表
	bool UpdateOrderState();//更新订单状态(主要是收件)



	/*系统工具*/
	void ClickedTable(const QModelIndex& index);//单击文件列表项
	void DoubleClickedTable(const QModelIndex& index);//双击文件列表项


private:
	Ui::UserMainWindow ui;
};
