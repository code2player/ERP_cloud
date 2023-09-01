#pragma once

#include <QMainWindow>
#include "ui_UserMainWindow.h"
#include "UserCreateOrderWindow.h"


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

using userspace::OrderId;
using userspace::OrderTransport;
using userspace::SpecificOrder;

/*��ͨ�û���������Ա������Ա�ȹ���*/
class UserBase {
public:
	std::string user_phone_;//��Ϊ��ѯid
	std::string user_identity_;//�û����

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

	/*grpcͨ��*/
	User user_impl_;
	UserId userid_impl_;
	OrderList order_list_impl_;

	OrderId orderid_impl_;
	SpecificOrder specific_order_impl_;

	UpdateOrderStateRequest update_state_impl;
	BaseReply basereply_impl_;


	/*qt�����洰��*/
	QStandardItemModel* sender_model;//�������ṹ
	QStandardItemModel* receiver_model;//

	QStandardItemModel* detail_model;//
	QStandardItemModel* transport_model;//
	QStandardItemModel* itemlist_model;//


	QModelIndex now_index;//��ǰѡ�еı������еĻ���


	/*�ڲ�����*/
	void ShowOrderDetail(const QModelIndex& index);
	void ShowOrderItemList();
	void ShowOrderTransportList();

public slots:
	/*����*/
	void CreateOrder();//�ļ�
	void GetOrderList();//ˢ�¶����б�
	bool UpdateOrderState();//���¶���״̬(��Ҫ���ռ�)



	/*ϵͳ����*/
	void ClickedTable(const QModelIndex& index);//�����ļ��б���
	void DoubleClickedTable(const QModelIndex& index);//˫���ļ��б���


private:
	Ui::UserMainWindow ui;
};
