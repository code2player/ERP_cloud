// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: myregister.proto
#ifndef GRPC_myregister_2eproto__INCLUDED
#define GRPC_myregister_2eproto__INCLUDED

#include "myregister.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace registerspace {

class MyRegister final {
 public:
  static constexpr char const* service_full_name() {
    return "registerspace.MyRegister";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::registerspace::UserRegisterReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>> AsyncUserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>>(AsyncUserRegisterRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>> PrepareAsyncUserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>>(PrepareAsyncUserRegisterRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>* AsyncUserRegisterRaw(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::registerspace::UserRegisterReply>* PrepareAsyncUserRegisterRaw(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::registerspace::UserRegisterReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>> AsyncUserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>>(AsyncUserRegisterRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>> PrepareAsyncUserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>>(PrepareAsyncUserRegisterRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response, std::function<void(::grpc::Status)>) override;
      void UserRegister(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>* AsyncUserRegisterRaw(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::registerspace::UserRegisterReply>* PrepareAsyncUserRegisterRaw(::grpc::ClientContext* context, const ::registerspace::UserRegisterRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_UserRegister_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status UserRegister(::grpc::ServerContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_UserRegister() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestUserRegister(::grpc::ServerContext* context, ::registerspace::UserRegisterRequest* request, ::grpc::ServerAsyncResponseWriter< ::registerspace::UserRegisterReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_UserRegister<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_UserRegister() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::registerspace::UserRegisterRequest, ::registerspace::UserRegisterReply>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::registerspace::UserRegisterRequest* request, ::registerspace::UserRegisterReply* response) { return this->UserRegister(context, request, response); }));}
    void SetMessageAllocatorFor_UserRegister(
        ::grpc::MessageAllocator< ::registerspace::UserRegisterRequest, ::registerspace::UserRegisterReply>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::registerspace::UserRegisterRequest, ::registerspace::UserRegisterReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* UserRegister(
      ::grpc::CallbackServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_UserRegister<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_UserRegister() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_UserRegister() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestUserRegister(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_UserRegister() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->UserRegister(context, request, response); }));
    }
    ~WithRawCallbackMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* UserRegister(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_UserRegister : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_UserRegister() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::registerspace::UserRegisterRequest, ::registerspace::UserRegisterReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::registerspace::UserRegisterRequest, ::registerspace::UserRegisterReply>* streamer) {
                       return this->StreamedUserRegister(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_UserRegister() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status UserRegister(::grpc::ServerContext* /*context*/, const ::registerspace::UserRegisterRequest* /*request*/, ::registerspace::UserRegisterReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedUserRegister(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::registerspace::UserRegisterRequest,::registerspace::UserRegisterReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_UserRegister<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_UserRegister<Service > StreamedService;
};

}  // namespace registerspace


#endif  // GRPC_myregister_2eproto__INCLUDED
