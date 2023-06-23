#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "myuser.grpc.pb.h"
#include "mystationer.grpc.pb.h"
#include "myadmin.grpc.pb.h"
#include "mylogin.grpc.pb.h"
#include "myregister.grpc.pb.h"
#include "../include/test_common.h"

#define USER_TEST true
#define STATIONER_TEST true



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

using namespace std;

/*把所有server的命名空间都整过来*/
/*分项目测试，然后使用benchmark参数(state)控制测试规模*/
/*仅对有重要意义的查询、创建等做性能测试，如login、register等性能要求不高的功能不进行额外的性能测试*/

class UserOrderClient {
public:
    UserOrderClient(std::shared_ptr<Channel> channel)
        : stub_(UserOrder::NewStub(channel)) {}

    bool GetOrderListRpc(UserId &request, OrderList &reply)
    {
        ClientContext context;
        Status status = stub_->GetOrderList(&context, request, &reply);
        return status.ok();
    }

    bool GetSpecificOrderRpc(OrderId &request, SpecificOrder &reply)
    {
        ClientContext context;
        Status status = stub_->GetSpecificOrder(&context, request, &reply);
        return status.ok();
    }

    bool CreateOrderRpc(const OrderDetail &request, BaseReply &reply)
    {
        ClientContext context;
        Status status = stub_->CreateOrder(&context, request, &reply);
        return status.ok();
    }

private:
    std::unique_ptr<UserOrder::Stub> stub_;
};

void GetOrderList(benchmark::State& state)
{
    UserId userid_impl_;
    OrderList order_list_impl_;
    //userid_impl_.set_user_phone_("13500000000");
    int length = state.range(0);

    /*rpc通信*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    /*start test*/
    for (auto _ : state)
    {
        for (int i = 1; i <= length; ++i)
        {
            state.PauseTiming();
            userid_impl_.set_user_phone_(to_string(13500000000 + i % user_num));
            state.ResumeTiming();
            bool res = LoginClientImpl.GetOrderListRpc(userid_impl_, order_list_impl_);
            state.PauseTiming();
            order_list_impl_.Clear();
            state.ResumeTiming();
        }
    }
}

void GetSpecificOrder(benchmark::State& state)
{
    OrderId orderid_impl_;
    SpecificOrder specific_order_impl_;
    int length = state.range(0);

    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    /*start test*/
    for (auto _ : state)
    {
        for (int i = 1; i <= length; ++i)
        {
            state.PauseTiming();
            orderid_impl_.set_order_id_(to_string(1 + i % order_num));
            state.ResumeTiming();

            bool res = LoginClientImpl.GetSpecificOrderRpc(orderid_impl_, specific_order_impl_);
            state.PauseTiming();
            specific_order_impl_.Clear();
            state.ResumeTiming();
        }
    }
}

void CreateOrder(benchmark::State& state)
{
    OrderDetail request_impl_;
    BaseReply reply_impl_;
    int length = state.range(0);

    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    /*start test*/
    for (auto _ : state)
    {
        for (int i = 1; i <= length; ++i)
        {
            state.PauseTiming();
            request_impl_.set_order_sender_id_(to_string(13500000000 + i % user_num));
            request_impl_.set_order_receiver_id_(to_string(13500000000 + (i + 1) % user_num));
            request_impl_.set_order_start_address_("addr1_" + to_string(13500000000 + i % user_num));
            request_impl_.set_order_end_address_("addr2_" + to_string(13500000000 + (i + 1) % user_num));
            request_impl_.set_order_money_("100.00");
            request_impl_.set_order_description_("description" + to_string(i));
            state.ResumeTiming();
            bool res = LoginClientImpl.CreateOrderRpc(request_impl_, reply_impl_);
            state.PauseTiming();
            reply_impl_.Clear();
            state.ResumeTiming();
        }
    }
}


#if USER_TEST
BENCHMARK(GetOrderList)->RangeMultiplier(10)->Range(10, 10000);
BENCHMARK(GetSpecificOrder)->RangeMultiplier(10)->Range(10, 10000);
BENCHMARK(CreateOrder)->RangeMultiplier(10)->Range(10, 10000);
#endif



/*stationer*/
using stationerspace::StationerOrder;
using stationerspace::StationId;
using stationerspace::SaveOrder;
using stationerspace::SaveOrderList;
using stationerspace::InStationRequest;
using stationerspace::OutStationRequest;
using stationerspace::StationerInfo;
using stationerspace::StationerId;
using stationerspace::BaseReply2;

class StationerOrderClient {
public:
    StationerOrderClient(std::shared_ptr<Channel> channel)
        : stub_(StationerOrder::NewStub(channel)) {}

    bool GetStationerInfoRpc(const StationerId& request, StationerInfo& reply) {
        ClientContext context;
        Status status = stub_->GetStationerInfo(&context, request, &reply);
        return status.ok();
    }

    bool GetStationOrderListRpc(const StationId& request, SaveOrderList& reply) {
        ClientContext context;
        Status status = stub_->GetStationOrderList(&context, request, &reply);
        return status.ok();
    }

private:
    std::unique_ptr<StationerOrder::Stub> stub_;
};

void GetStationerInfo(benchmark::State& state)
{
    StationerId request_impl_;
    StationerInfo reply_impl_;
    int length = state.range(0);

    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    /*start test*/
    for (auto _ : state)
    {
        for (int i = 1; i <= length; ++i)
        {
            state.PauseTiming();
            request_impl_.set_stationer_id_(to_string(16600000000 + i % stationer_num));
            state.ResumeTiming();
            bool res = LoginClientImpl.GetStationerInfoRpc(request_impl_, reply_impl_);
            state.PauseTiming();
            reply_impl_.Clear();
            state.ResumeTiming();
        }
    }
}

void GetStationOrderList(benchmark::State& state)
{
    StationId request_impl_;
    SaveOrderList reply_impl_;
    int length = state.range(0);

    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    /*start test*/
    for (auto _ : state)
    {
        for (int i = 1; i <= length; ++i)
        {
            state.PauseTiming();
            request_impl_.set_station_id_(to_string(i % station_num));
            state.ResumeTiming();
            bool res = LoginClientImpl.GetStationOrderListRpc(request_impl_, reply_impl_);
            state.PauseTiming();
            reply_impl_.Clear();
            state.ResumeTiming();
        }
    }
}


#if STATIONER_TEST
BENCHMARK(GetStationerInfo)->RangeMultiplier(10)->Range(10, 10000);
BENCHMARK(GetStationOrderList)->RangeMultiplier(10)->Range(10, 10000);
#endif









BENCHMARK_MAIN();
