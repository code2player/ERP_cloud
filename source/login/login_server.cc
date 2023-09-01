#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "../include/mysql_common.h"
#include "../include/define_common.h"

#include "glog/logging.h" // glog 头文件
#include "glog/raw_logging.h"

#include <grpcpp/grpcpp.h>
#ifdef BAZEL_BUILD
#include "examples/protos/mylogin.grpc.pb.h"
#else
#include "mylogin.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using loginspace::MyLogin;
using loginspace::UserLoginRequest;
using loginspace::UserLoginReply;

// Logic and data behind the server's behavior.
class MyLoginServiceImpl final : public MyLogin::Service, public MysqlTools
{
private:
    Status UserLogin(ServerContext *context, const UserLoginRequest *request,
                        UserLoginReply *reply) override
    {
        /*检查登录身份合法性*/
        if (request->user_identity_() != "user" && 
            request->user_identity_() != "stationer" && 
            request->user_identity_() != "admin"  )
        {
            // error
            LOG(ERROR) << "user identity wrong, undefined identity " + request->user_identity_();
            reply->set_return_result_(false);
            reply->set_return_message_("login error, user identity wrong, undefined identity " + request->user_identity_());
            return Status::OK;
        }

        /*密码加密*/

        std::vector<std::vector<std::string>> info(2, std::vector<std::string>(3, ""));
        info[0] = {"string", request->user_identity_()+"_phone", request->user_phone_()};
        info[1] = {"string", request->user_identity_()+"_password", request->user_password_()};
        std::string table_name = request->user_identity_() + "_info";

        if (QueryMysqlExist(table_name, info) <= 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("login error");
            LOG(INFO) << "user login failed, phone:" << request->user_phone_();
        }
        else
        {
            reply->set_return_result_(true);
            reply->set_return_message_("login success");
            LOG(INFO) << "user login successed, phone:" << request->user_phone_();
        }
        return Status::OK;
    }
};

void RunServer()
{
    std::string server_address(LOGIN_SERVER);
    MyLoginServiceImpl service;
    service.MysqlStart();

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on " << server_address;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char **argv)
{
    FLAGS_log_dir = ".";                // 设置log目录  没有指定则输出到控制台
    FLAGS_logtostderr = false;          // 输出到控制台
    google::InitGoogleLogging(argv[0]); // 初始化

    RunServer();

    return 0;
}
