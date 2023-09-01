#pragma execution_character_set("utf-8")  
#include "LoginWindow.h"

/*��׼��*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc��protoЭ���*/
#include <grpcpp/grpcpp.h>
#include "../protocol/mylogin.grpc.pb.h"


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

using loginspace::MyLogin;
using loginspace::UserLoginRequest;
using loginspace::UserLoginReply;


LoginWindow::LoginWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(login_to_server()));
}

LoginWindow::~LoginWindow()
{
}

class LoginClient {
public:
    LoginClient(std::shared_ptr<Channel> channel)
        : stub_(MyLogin::NewStub(channel)) {}

    bool StartLogin(const std::string& user_phone_, const std::string& user_password_, 
        const std::string& user_identity_, std::string& return_message_) {

        UserLoginRequest request;
        UserLoginReply reply;
        ClientContext context;

        /*���÷�������*/
        request.set_user_phone_(user_phone_);
        request.set_user_password_(user_password_);
        request.set_user_identity_(user_identity_);

        /*rpcͨ��*/
		Status status = stub_->UserLogin(&context, request, &reply);

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
    std::unique_ptr<MyLogin::Stub> stub_;
};

void LoginWindow::login_to_server()
{
    //accept();
    //return;
    /*�ϴ��û��������뵽�����������շ��������ر���*/
	LoginClient LoginClientImpl(grpc::CreateChannel(
		LOGIN_IP + ":" + LOGIN_PORT, grpc::InsecureChannelCredentials()));

	std::string phone = ui.lineEdit->text().toStdString();
	std::string password = ui.lineEdit_2->text().toStdString();
	std::string identity = identity_list[state_code];
	std::string return_message_;

	bool res = LoginClientImpl.StartLogin(phone, password, identity, return_message_);

    if (res == true)//��¼�ɹ�����ת
    {
        return_phone = phone;
        QMessageBox::information(nullptr, "��¼�ɹ�", QString::fromStdString(return_message_));
        accept();
    }
    else//��¼ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "����", QString::fromStdString(return_message_));
    }

}
