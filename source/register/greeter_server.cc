#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>
#include "../include/mysql_common.h"

#include "glog/logging.h" // glog 头文件
#include "glog/raw_logging.h"

#include <grpcpp/grpcpp.h>
#ifdef BAZEL_BUILD
#include "examples/protos/myregister.grpc.pb.h"
#else
#include "myregister.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using registerspace::MyRegister;
using registerspace::UserRegisterReply;
using registerspace::UserRegisterRequest;



// Logic and data behind the server's behavior.
class MyRegisterServiceImpl final : public MyRegister::Service, public MysqlTools
{
  bool CheckPasswordLegal(std::string password, std::string &ret_message)
  {
    // length 6-15
    if (password.size() < 6 || password.size() > 15)
    {
      ret_message = "密码长度需要为6-15个字符";
      return false;
    }

    std::set<std::string> char_set;

    for(auto iter : password){
      if(iter>='a'&&iter<='z'){
        char_set.insert("small");
      }
      else if(iter>='A'&&iter<='Z'){
        char_set.insert("big");
      }
      else if(iter>='0'&&iter<='9'){
        char_set.insert("number");
      }
      else{
        char_set.insert("other");
      }
    }

    if(char_set.size()<3){
      ret_message = "密码需要由大写字母、小写字母、数字、特殊符号中的任意三个以上组成";
      //LOG(ERROR) << ret_message;
      return false;
    }
    return true;
  }

  Status UserRegister(ServerContext *context, const UserRegisterRequest *request,
                      UserRegisterReply *reply) override
  {
    std::string ret_message;
    if(CheckPasswordLegal(request->user_password_(), ret_message) == true){
      LOG(INFO) << "密码合法性检测成功, user phone:"<<request->user_phone_();
    }
    else{
      LOG(INFO) << "密码合法性检测失败, user phone:"<<request->user_phone_();
      LOG(INFO) << ret_message;
      reply->set_return_message_("register error, 密码合法性检测失败, " + ret_message);
      return Status::OK;
    }
    
    std::vector<std::string> info;
    std::string table_name;

    if (request->user_identity_() == "user")
    {
      info.resize(6, "");
      info[0] = request->user_phone_();
      info[1] = request->user_password_();
      info[2] = request->user_name_();
      info[4] = request->user_phone_();
      info[5] = "1";
      table_name = "user_info";
    }
    else if (request->user_identity_() == "stationer")
    {
      info.resize(6, "");
      info[0] = request->user_phone_();
      info[1] = request->user_password_();
      info[2] = request->staff_station_();
      info[3] = request->user_name_();
      info[4] = request->user_phone_();
      info[5] = "5";
      table_name = "stationer_info";
    }
    else if (request->user_identity_() == "admin")
    {
      info.resize(5, "");
      info[0] = request->user_phone_();
      info[1] = request->user_password_();
      info[2] = request->user_name_();
      info[3] = request->user_phone_();
      info[4] = "10";
      table_name = "admin_info";
    }
    else
    {
      // error
    }

    reply->set_return_message_("register success");

    if (InsertMysql(table_name, info) < 0)
    {
      reply->set_return_message_("register error");
    }
    std::cout << "get user: " << request->user_name_() << std::endl;
    return Status::OK;
  }
};

  void RunServer()
  {
    std::string server_address("0.0.0.0:50051");
    MyRegisterServiceImpl service;
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
