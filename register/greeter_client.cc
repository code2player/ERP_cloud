/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/myregister.grpc.pb.h"
#else
#include "myregister.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using registerspace::MyRegister;
using registerspace::AdminRegisterCtoS;
using registerspace::AdminRegisterStoC;
using registerspace::StaffRegisterCtoS;
using registerspace::StaffRegisterStoC;
using registerspace::UserRegisterCtoS;
using registerspace::UserRegisterStoC;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(MyRegister::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string UserRegister() {
    // Data we are sending to the server.
    UserRegisterCtoS request;
    request.set_user_phone_("13511112222");
    request.set_user_password_("Aa111111");
    request.set_user_name_("中文名测试");

    // Container for the data we expect from the server.
    UserRegisterStoC reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->UserRegister(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.return_message_();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<MyRegister::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  if(argc != 2){
    std::cout<<"argc error"<<std::endl;
    return -1;
  }

  std::string target_addr = argv[1];

  GreeterClient greeter(grpc::CreateChannel(
      target_addr, grpc::InsecureChannelCredentials()));

  std::string reply = greeter.UserRegister();
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
