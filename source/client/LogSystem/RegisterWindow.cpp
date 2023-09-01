#pragma execution_character_set("utf-8")  
#include "RegisterWindow.h"

/*��׼��*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc��protoЭ���*/
#include <grpcpp/grpcpp.h>
#include "../protocol/myregister.grpc.pb.h"


/*QTר�ÿ�*/
#include <QMainWindow>
#include <QMessageBox>   //�������ܵ�ʵ��
#include <QTextBlock>
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

using registerspace::MyRegister;
using registerspace::UserRegisterReply;
using registerspace::UserRegisterRequest;

RegisterWindow::RegisterWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(register_to_server()));
}

RegisterWindow::~RegisterWindow()
{
}


class RegisterClient {
public:
    RegisterClient(std::shared_ptr<Channel> channel)
        : stub_(MyRegister::NewStub(channel)) {}

    bool StartRegister(const std::string& user_phone_, const std::string& user_password_, const std::string& user_name_,
        const std::string& user_secertkey_, const std::string& staff_station_,
        const std::string& user_identity_, std::string& return_message_) {

        UserRegisterRequest request;
        UserRegisterReply reply;
        ClientContext context;

		/*���÷�������*/
		request.set_user_phone_(user_phone_);
		request.set_user_password_(user_password_);
		request.set_user_name_(user_name_);
		request.set_user_secertkey_(user_secertkey_);
		request.set_staff_station_(staff_station_);
		request.set_user_identity_(user_identity_);

        /*rpcͨ��*/
        Status status = stub_->UserRegister(&context, request, &reply);

        /*���ͨ�ţ�����*/
        if (status.ok()) {
            return_message_ = reply.return_message_();
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

private:
    std::unique_ptr<MyRegister::Stub> stub_;
};


void RegisterWindow::register_to_server()
{
    /*�ϴ��û��������뵽�����������շ��������ر���*/
    RegisterClient RegisterClientImpl(grpc::CreateChannel(
        REGISTER_IP + ":" + REGISTER_PORT, grpc::InsecureChannelCredentials()));

	std::string phone =     ui.lineEdit->text().toStdString();
	std::string password =  ui.lineEdit_2->text().toStdString();
	std::string name =      ui.lineEdit_3->text().toStdString();
	std::string secertkey = ui.lineEdit_4->text().toStdString();
	std::string station =   ui.lineEdit_5->text().toStdString();
	std::string identity =  identity_list[state_code];
	std::string return_message_;

	bool res = RegisterClientImpl.StartRegister(phone, password, name, secertkey, station, identity, return_message_);

	if (res == true)//�ɹ�����ת
	{
        QMessageBox::information(nullptr, "ע��ɹ�", QString::fromStdString(return_message_));
        accept();
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "����", QString::fromStdString(return_message_));
    }

}
