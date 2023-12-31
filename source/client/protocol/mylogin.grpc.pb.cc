// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mylogin.proto

#include "mylogin.pb.h"
#include "mylogin.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace loginspace {

static const char* MyLogin_method_names[] = {
  "/loginspace.MyLogin/UserLogin",
};

std::unique_ptr< MyLogin::Stub> MyLogin::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MyLogin::Stub> stub(new MyLogin::Stub(channel, options));
  return stub;
}

MyLogin::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_UserLogin_(MyLogin_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MyLogin::Stub::UserLogin(::grpc::ClientContext* context, const ::loginspace::UserLoginRequest& request, ::loginspace::UserLoginReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::loginspace::UserLoginRequest, ::loginspace::UserLoginReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UserLogin_, context, request, response);
}

void MyLogin::Stub::async::UserLogin(::grpc::ClientContext* context, const ::loginspace::UserLoginRequest* request, ::loginspace::UserLoginReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::loginspace::UserLoginRequest, ::loginspace::UserLoginReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UserLogin_, context, request, response, std::move(f));
}

void MyLogin::Stub::async::UserLogin(::grpc::ClientContext* context, const ::loginspace::UserLoginRequest* request, ::loginspace::UserLoginReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UserLogin_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::loginspace::UserLoginReply>* MyLogin::Stub::PrepareAsyncUserLoginRaw(::grpc::ClientContext* context, const ::loginspace::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::loginspace::UserLoginReply, ::loginspace::UserLoginRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UserLogin_, context, request);
}

::grpc::ClientAsyncResponseReader< ::loginspace::UserLoginReply>* MyLogin::Stub::AsyncUserLoginRaw(::grpc::ClientContext* context, const ::loginspace::UserLoginRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUserLoginRaw(context, request, cq);
  result->StartCall();
  return result;
}

MyLogin::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MyLogin_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MyLogin::Service, ::loginspace::UserLoginRequest, ::loginspace::UserLoginReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MyLogin::Service* service,
             ::grpc::ServerContext* ctx,
             const ::loginspace::UserLoginRequest* req,
             ::loginspace::UserLoginReply* resp) {
               return service->UserLogin(ctx, req, resp);
             }, this)));
}

MyLogin::Service::~Service() {
}

::grpc::Status MyLogin::Service::UserLogin(::grpc::ServerContext* context, const ::loginspace::UserLoginRequest* request, ::loginspace::UserLoginReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace loginspace

