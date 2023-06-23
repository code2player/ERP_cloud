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

#include "myadmin.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using adminspace::AdminService;
using adminspace::AdminId;
using adminspace::ItemInfo;
using adminspace::AllItemList;
using adminspace::OrderInfo;
using adminspace::AllOrderList;
using adminspace::StationInfo;
using adminspace::AllStationList;
using adminspace::BaseReply3;


// Logic and data behind the server's behavior.
class MyAdminOrderServiceImpl final : public AdminService::Service, public MysqlTools
{
private:
    Status GetAllItemList(ServerContext *context, const AdminId *request,
                          AllItemList *reply) override
    {
        std::string table_name = "item_info";
        std::vector<std::vector<std::string>> query_result;

        int list_num = QueryMysql(table_name, query_result);
        if (list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("GetAllItemList query failed");
            LOG(INFO) << "GetAllItemList query failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }

        for (int i = 0; i < list_num; i++)
        {
            ItemInfo *item_info_;
            item_info_ = reply->add_item_info_();
            item_info_->set_item_id_(query_result[i][0]);
            item_info_->set_item_name_(query_result[i][1]);
            item_info_->set_item_price_(query_result[i][2]);
            item_info_->set_item_description_(query_result[i][3]);
        }
        reply->set_return_result_(true);
        reply->set_return_message_("GetAllItemList query succeed");
        LOG(INFO) << "GetAllItemList query succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status GetAllStationList(ServerContext *context, const AdminId *request,
                             AllStationList *reply) override
    {
        /*填充order_list_*/
        std::string table_name = "station_info";
        std::vector<std::vector<std::string>> query_result;

        int list_num = QueryMysql(table_name, query_result);
        if (list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("GetAllStationList query failed");
            LOG(INFO) << "GetAllStationList query failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }

        for (int i = 0; i < list_num; i++)
        {
            StationInfo *station_info_;
            station_info_ = reply->add_station_info_();
            station_info_->set_station_id_(query_result[i][0]);
            station_info_->set_station_name_(query_result[i][1]);
            station_info_->set_station_position_(query_result[i][2]);
            station_info_->set_station_description_(query_result[i][3]);
        }
        reply->set_return_result_(true);
        reply->set_return_message_("GetAllStationList query succeed");
        LOG(INFO) << "GetAllStationList query succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status GetAllOrderList(ServerContext *context, const AdminId *request,
                           AllOrderList *reply) override
    {
        /*填充order_list_*/
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> query_result;

        int list_num = QueryMysql(table_name, query_result);
        if (list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("GetAllOrderList query failed");
            LOG(INFO) << "GetAllOrderList query failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }

        for (int i = 0; i < list_num; i++)
        {
            OrderInfo *order_info_;
            order_info_ = reply->add_order_info_();
            order_info_->set_order_id_(query_result[i][0]);
            order_info_->set_order_sender_id_(query_result[i][1]);
            order_info_->set_order_receiver_id_(query_result[i][2]);
            order_info_->set_order_start_address_(query_result[i][3]);
            order_info_->set_order_end_address_(query_result[i][4]);
            order_info_->set_order_money_(query_result[i][5]);
            order_info_->set_order_time_(query_result[i][6]);
            order_info_->set_order_status_(query_result[i][7]);
            order_info_->set_order_description_(query_result[i][8]);
        }
        reply->set_return_result_(true);
        reply->set_return_message_("GetAllOrderList query succeed");
        LOG(INFO) << "GetAllOrderList query succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }

    Status AddItem(ServerContext *context, const ItemInfo *request,
                   BaseReply3 *reply) override
    {
        std::vector<std::vector<std::string>> info(4, std::vector<std::string>(3, ""));
        info[0] = {"string", "", request->item_id_()};
        info[1] = {"string", "", request->item_name_()};
        info[2] = {"string", "", request->item_price_()};
        info[3] = {"string", "", request->item_description_()};

        if (InsertMysql("item_info", info) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("AddItem failed");
            LOG(INFO) << "AddItem failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }
        reply->set_return_result_(true);
        reply->set_return_message_("AddItem succeed");
        LOG(INFO) << "AddItem succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status DelItem(ServerContext *context, const ItemInfo *request,
                   BaseReply3 *reply) override
    {
        std::vector<std::vector<std::string>> delete_condition(1, std::vector<std::string>(3, ""));
        delete_condition[0] = {"string", "item_id", request->item_id_()};

        if (DeleteMysql("item_info", delete_condition) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("DelItem failed");
            LOG(INFO) << "DelItem failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }
        reply->set_return_result_(true);
        reply->set_return_message_("DelItem succeed");
        LOG(INFO) << "DelItem succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status AddStation(ServerContext *context, const StationInfo *request,
                      BaseReply3 *reply) override
    {
        std::vector<std::vector<std::string>> info(4, std::vector<std::string>(3, ""));
        info[0] = {"string", "", request->station_id_()};
        info[1] = {"string", "", request->station_name_()};
        info[2] = {"string", "", request->station_position_()};
        info[3] = {"string", "", request->station_description_()};

        if (InsertMysql("station_info", info) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("AddStation failed");
            LOG(INFO) << "AddStation failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }
        reply->set_return_result_(true);
        reply->set_return_message_("AddStation succeed");
        LOG(INFO) << "AddStation succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status DelStation(ServerContext *context, const StationInfo *request,
                      BaseReply3 *reply) override
    {
        std::vector<std::vector<std::string>> delete_condition(1, std::vector<std::string>(3, ""));
        delete_condition[0] = {"string", "station_id", request->station_id_()};

        if (DeleteMysql("station_info", delete_condition) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("DelStation failed");
            LOG(INFO) << "DelStation failed, admin_id_:" << request->admin_id_();
            return Status::OK;
        }
        reply->set_return_result_(true);
        reply->set_return_message_("DelStation succeed");
        LOG(INFO) << "DelStation succeed, admin_id_:" << request->admin_id_();
        return Status::OK;
    }
    Status UpdateOrder(ServerContext *context, const OrderInfo *request,
                       BaseReply3 *reply) override
    {
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> info_set(4, std::vector<std::string>(3, ""));
        std::vector<std::vector<std::string>> info_where(1, std::vector<std::string>(3, ""));
        info_set[0] = {"string", "order_start_address", request->order_start_address_()};
        info_set[1] = {"string", "order_end_address", request->order_end_address_()};
        info_set[2] = {"string", "order_status", request->order_status_()};
        info_set[3] = {"string", "order_description", request->order_description_()};
        info_where[0] = {"int", "order_id", request->order_id_()};

        if (UpdateMysql(table_name, info_set, info_where) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("UpdateOrder failed");
            LOG(INFO) << "UpdateOrder failed, order_id:" << request->order_id_();
        }
        else
        {
            reply->set_return_result_(true);
            reply->set_return_message_("UpdateOrder successed");
            LOG(INFO) << "UpdateOrder successed, order_id:" << request->order_id_();
        }
        return Status::OK;
    }
};

void RunServer()
{
    std::string server_address(ADMIN_ORDER_SERVER);
    MyAdminOrderServiceImpl service;
    service.MysqlStart();

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG(INFO) << "Admin Server listening on " << server_address;

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
