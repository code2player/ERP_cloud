// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mystationer.proto

#include "mystationer.pb.h"
#include "mystationer.grpc.pb.h"

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
namespace stationerspace {

static const char* StationerOrder_method_names[] = {
  "/stationerspace.StationerOrder/GetStationOrderList",
  "/stationerspace.StationerOrder/GetStationerInfo",
  "/stationerspace.StationerOrder/InStation",
  "/stationerspace.StationerOrder/OutStation",
};

std::unique_ptr< StationerOrder::Stub> StationerOrder::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< StationerOrder::Stub> stub(new StationerOrder::Stub(channel, options));
  return stub;
}

StationerOrder::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetStationOrderList_(StationerOrder_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetStationerInfo_(StationerOrder_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_InStation_(StationerOrder_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_OutStation_(StationerOrder_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status StationerOrder::Stub::GetStationOrderList(::grpc::ClientContext* context, const ::stationerspace::StationId& request, ::stationerspace::SaveOrderList* response) {
  return ::grpc::internal::BlockingUnaryCall< ::stationerspace::StationId, ::stationerspace::SaveOrderList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetStationOrderList_, context, request, response);
}

void StationerOrder::Stub::async::GetStationOrderList(::grpc::ClientContext* context, const ::stationerspace::StationId* request, ::stationerspace::SaveOrderList* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::stationerspace::StationId, ::stationerspace::SaveOrderList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetStationOrderList_, context, request, response, std::move(f));
}

void StationerOrder::Stub::async::GetStationOrderList(::grpc::ClientContext* context, const ::stationerspace::StationId* request, ::stationerspace::SaveOrderList* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetStationOrderList_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::SaveOrderList>* StationerOrder::Stub::PrepareAsyncGetStationOrderListRaw(::grpc::ClientContext* context, const ::stationerspace::StationId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::stationerspace::SaveOrderList, ::stationerspace::StationId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetStationOrderList_, context, request);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::SaveOrderList>* StationerOrder::Stub::AsyncGetStationOrderListRaw(::grpc::ClientContext* context, const ::stationerspace::StationId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetStationOrderListRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status StationerOrder::Stub::GetStationerInfo(::grpc::ClientContext* context, const ::stationerspace::StationerId& request, ::stationerspace::StationerInfo* response) {
  return ::grpc::internal::BlockingUnaryCall< ::stationerspace::StationerId, ::stationerspace::StationerInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetStationerInfo_, context, request, response);
}

void StationerOrder::Stub::async::GetStationerInfo(::grpc::ClientContext* context, const ::stationerspace::StationerId* request, ::stationerspace::StationerInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::stationerspace::StationerId, ::stationerspace::StationerInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetStationerInfo_, context, request, response, std::move(f));
}

void StationerOrder::Stub::async::GetStationerInfo(::grpc::ClientContext* context, const ::stationerspace::StationerId* request, ::stationerspace::StationerInfo* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetStationerInfo_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::StationerInfo>* StationerOrder::Stub::PrepareAsyncGetStationerInfoRaw(::grpc::ClientContext* context, const ::stationerspace::StationerId& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::stationerspace::StationerInfo, ::stationerspace::StationerId, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetStationerInfo_, context, request);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::StationerInfo>* StationerOrder::Stub::AsyncGetStationerInfoRaw(::grpc::ClientContext* context, const ::stationerspace::StationerId& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetStationerInfoRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status StationerOrder::Stub::InStation(::grpc::ClientContext* context, const ::stationerspace::InStationRequest& request, ::stationerspace::BaseReply2* response) {
  return ::grpc::internal::BlockingUnaryCall< ::stationerspace::InStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_InStation_, context, request, response);
}

void StationerOrder::Stub::async::InStation(::grpc::ClientContext* context, const ::stationerspace::InStationRequest* request, ::stationerspace::BaseReply2* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::stationerspace::InStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_InStation_, context, request, response, std::move(f));
}

void StationerOrder::Stub::async::InStation(::grpc::ClientContext* context, const ::stationerspace::InStationRequest* request, ::stationerspace::BaseReply2* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_InStation_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::BaseReply2>* StationerOrder::Stub::PrepareAsyncInStationRaw(::grpc::ClientContext* context, const ::stationerspace::InStationRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::stationerspace::BaseReply2, ::stationerspace::InStationRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_InStation_, context, request);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::BaseReply2>* StationerOrder::Stub::AsyncInStationRaw(::grpc::ClientContext* context, const ::stationerspace::InStationRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncInStationRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status StationerOrder::Stub::OutStation(::grpc::ClientContext* context, const ::stationerspace::OutStationRequest& request, ::stationerspace::BaseReply2* response) {
  return ::grpc::internal::BlockingUnaryCall< ::stationerspace::OutStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_OutStation_, context, request, response);
}

void StationerOrder::Stub::async::OutStation(::grpc::ClientContext* context, const ::stationerspace::OutStationRequest* request, ::stationerspace::BaseReply2* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::stationerspace::OutStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_OutStation_, context, request, response, std::move(f));
}

void StationerOrder::Stub::async::OutStation(::grpc::ClientContext* context, const ::stationerspace::OutStationRequest* request, ::stationerspace::BaseReply2* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_OutStation_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::BaseReply2>* StationerOrder::Stub::PrepareAsyncOutStationRaw(::grpc::ClientContext* context, const ::stationerspace::OutStationRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::stationerspace::BaseReply2, ::stationerspace::OutStationRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_OutStation_, context, request);
}

::grpc::ClientAsyncResponseReader< ::stationerspace::BaseReply2>* StationerOrder::Stub::AsyncOutStationRaw(::grpc::ClientContext* context, const ::stationerspace::OutStationRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncOutStationRaw(context, request, cq);
  result->StartCall();
  return result;
}

StationerOrder::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StationerOrder_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StationerOrder::Service, ::stationerspace::StationId, ::stationerspace::SaveOrderList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StationerOrder::Service* service,
             ::grpc::ServerContext* ctx,
             const ::stationerspace::StationId* req,
             ::stationerspace::SaveOrderList* resp) {
               return service->GetStationOrderList(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StationerOrder_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StationerOrder::Service, ::stationerspace::StationerId, ::stationerspace::StationerInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StationerOrder::Service* service,
             ::grpc::ServerContext* ctx,
             const ::stationerspace::StationerId* req,
             ::stationerspace::StationerInfo* resp) {
               return service->GetStationerInfo(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StationerOrder_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StationerOrder::Service, ::stationerspace::InStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StationerOrder::Service* service,
             ::grpc::ServerContext* ctx,
             const ::stationerspace::InStationRequest* req,
             ::stationerspace::BaseReply2* resp) {
               return service->InStation(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      StationerOrder_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< StationerOrder::Service, ::stationerspace::OutStationRequest, ::stationerspace::BaseReply2, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](StationerOrder::Service* service,
             ::grpc::ServerContext* ctx,
             const ::stationerspace::OutStationRequest* req,
             ::stationerspace::BaseReply2* resp) {
               return service->OutStation(ctx, req, resp);
             }, this)));
}

StationerOrder::Service::~Service() {
}

::grpc::Status StationerOrder::Service::GetStationOrderList(::grpc::ServerContext* context, const ::stationerspace::StationId* request, ::stationerspace::SaveOrderList* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status StationerOrder::Service::GetStationerInfo(::grpc::ServerContext* context, const ::stationerspace::StationerId* request, ::stationerspace::StationerInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status StationerOrder::Service::InStation(::grpc::ServerContext* context, const ::stationerspace::InStationRequest* request, ::stationerspace::BaseReply2* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status StationerOrder::Service::OutStation(::grpc::ServerContext* context, const ::stationerspace::OutStationRequest* request, ::stationerspace::BaseReply2* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace stationerspace

