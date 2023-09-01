#pragma execution_character_set("utf-8")  
#include "LoginWindow.h"

/*标准库*/
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


/*grpc及proto协议库*/
#include <grpcpp/grpcpp.h>
#include "../protocol/mylogin.grpc.pb.h"


/*QT专用库*/
#include <QMainWindow>
#include <QMessageBox>   //弹窗功能的实现
#include <QTextBlock>
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

        /*设置发送内容*/
        request.set_user_phone_(user_phone_);
        request.set_user_password_(user_password_);
        request.set_user_identity_(user_identity_);

        /*rpc通信*/
		Status status = stub_->UserLogin(&context, request, &reply);

        /*完成通信，返回*/
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
    /*上传用户名和密码到服务器，接收服务器返回报文*/
	LoginClient LoginClientImpl(grpc::CreateChannel(
		LOGIN_IP + ":" + LOGIN_PORT, grpc::InsecureChannelCredentials()));

	std::string phone = ui.lineEdit->text().toStdString();
	std::string password = ui.lineEdit_2->text().toStdString();
	std::string identity = identity_list[state_code];
	std::string return_message_;

	bool res = LoginClientImpl.StartLogin(phone, password, identity, return_message_);

    if (res == true)//登录成功，跳转
    {
        return_phone = phone;
        QMessageBox::information(nullptr, "登录成功", QString::fromStdString(return_message_));
        accept();
    }
    else//登录失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "错误", QString::fromStdString(return_message_));
    }

}
