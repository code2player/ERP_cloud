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

#include "mystationer.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using stationerspace::StationerOrder;
using stationerspace::StationId;
using stationerspace::SaveOrder;
using stationerspace::SaveOrderList;
using stationerspace::InStationRequest;
using stationerspace::BaseReply2;
using stationerspace::OutStationRequest;
using stationerspace::StationerInfo;
using stationerspace::StationerId;

// Logic and data behind the server's behavior.
class MyStationerOrderServiceImpl final : public StationerOrder::Service, public MysqlTools
{
private:
    Status GetStationOrderList(ServerContext *context, const StationId *request,
                        SaveOrderList *reply) override
    {
        /*填充order_list_*/
        std::string table_name = "stationsave_info";
        std::vector<std::vector<std::string>> query_condition(1, std::vector<std::string>(3, ""));
        std::vector<std::string> query_col_name = {"order_id", "input_time"};
        std::vector<std::vector<std::string>> query_result;
        query_condition[0] = {"string", "station_id", request->station_id_()};

        int order_list_num = QueryMysql(table_name, query_condition, query_col_name, query_result);
        if (order_list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("stationsave_info list query failed");
            LOG(INFO) << "stationsave_info query failed, station id:" << request->station_id_();
            return Status::OK;
        }

        for (int j = 0; j < order_list_num; j++)
        {
            SaveOrder *order_list_;
            order_list_ = reply->add_order_list_();
            order_list_->set_order_id_(query_result[j][0]);
            order_list_->set_input_time_(query_result[j][1]);
        }

        reply->set_return_result_(true);
        reply->set_return_message_("get SaveOrderList query succeed");
        LOG(INFO) << "user SaveOrderList query success, station id:" << request->station_id_();
        return Status::OK;
    }

    Status GetStationerInfo(ServerContext *context, const StationerId *request,
                        StationerInfo *reply) override
    {
        std::string table_name = "stationer_info";
        std::vector<std::vector<std::string>> query_condition(1, std::vector<std::string>(3, ""));
        std::vector<std::string> query_col_name = {"stationer_id", "stationer_station_id", "stationer_name"};
        std::vector<std::vector<std::string>> query_result;
        query_condition[0] = {"string", "stationer_id", request->stationer_id_()};

        int order_list_num = QueryMysql(table_name, query_condition, query_col_name, query_result);
        if (order_list_num <= 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("stationer_info query failed");
            LOG(INFO) << "stationer_info query failed, stationer id:" << request->stationer_id_();
            return Status::OK;
        }

        reply->set_return_result_(true);
        reply->set_return_message_("stationer_info query succeed");
        reply->set_stationer_id_(query_result[0][0]);
        reply->set_station_id_(query_result[0][1]);
        reply->set_stationer_name(query_result[0][2]);
        LOG(INFO) << "stationer_info query succeed, stationer id:" << request->stationer_id_();
        return Status::OK;
    }

    //获取对应station_name
    std::string get_station_name(std::string station_id)
    {
        std::string table_name = "station_info";
        std::vector<std::vector<std::string>> query_condition(1, std::vector<std::string>(3, ""));
        std::vector<std::string> query_col_name = {"station_name"};
        std::vector<std::vector<std::string>> query_result;
        query_condition[0] = {"string", "station_id", station_id};

        int order_list_num = QueryMysql(table_name, query_condition, query_col_name, query_result);
        if (order_list_num <= 0)
        {
            LOG(INFO) << "station_info query failed, station id:" << station_id;
            return "";
        }

        LOG(INFO) << "station_info query success, station name:" << query_result[0][0];
        return query_result[0][0];
    }

    Status InStation(ServerContext *context, const InStationRequest *request,
                     BaseReply2 *reply) override
    {
        /*入库操作*/
        /*入库前先检测是否存在*/
        std::string table_name = "stationsave_info";
        std::vector<std::vector<std::string>> query_condition(2, std::vector<std::string>(3, ""));
        std::vector<std::vector<std::string>> query_result;
        query_condition[0] = {"string", "station_id", request->station_id_()};
        query_condition[1] = {"int", "order_id", request->order_id_()};

        int order_list_num = QueryMysql(table_name, query_condition, query_result);
        if (order_list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("stationsave_info list query failed");
            LOG(INFO) << "stationsave_info query failed, stationer id:" << request->stationer_id_();
            return Status::OK;
        }
        else if (order_list_num > 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("该订单已入库");
            LOG(INFO) << "order has existed, stationer id:" << request->stationer_id_();
            return Status::OK;
        }
        else
        {
            ;
        }

        /*表中不存在，insert*/
        std::vector<std::vector<std::string>> info_2(4, std::vector<std::string>(3, ""));
        info_2[0] = {"null", "", "null"}; // id自增
        info_2[1] = {"int", "", request->order_id_()};
        info_2[2] = {"string", "", request->station_id_()};
        info_2[3] = {"null", "", "CURRENT_TIMESTAMP"}; // timestamp自动计算

        if (InsertMysql("stationsave_info", info_2) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("stationsave info create failed");
            LOG(INFO) << "stationsave info insert failed, phone:" << request->stationer_id_();
            return Status::OK;
        }

        LOG(INFO) << "stationsave info insert success, phone:" << request->stationer_id_();
        //return Status::OK;

        /*自动拼接消息，生成格式如下：*/
        /*order_id 入库 station_name, 处理人: stationer_id*/
        std::string transport_description = request->order_id_() + " 入库 " + get_station_name(request->station_id_()) +
                                            ", 处理人联系方式: " + request->stationer_id_();
        std::vector<std::vector<std::string>> info_3(5, std::vector<std::string>(3, ""));
        info_3[0] = {"null", "", "null"}; // id自增
        info_3[1] = {"int", "", request->order_id_()};
        info_3[2] = {"int", "", "1"};
        info_3[3] = {"null", "", "CURRENT_TIMESTAMP"}; // timestamp自动计算
        info_3[4] = {"string", "", transport_description};

        if (InsertMysql("transport_info", info_3) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("transport record create failed");
            LOG(INFO) << "transport record insert failed, phone:" << request->stationer_id_();
            return Status::OK;
        }

        reply->set_return_result_(true);
        reply->set_return_message_("order into station succeed");
        LOG(INFO) << "order into station succeed, stationer id:" << request->stationer_id_();
        return Status::OK;
    }

    Status OutStation(ServerContext *context, const OutStationRequest *request,
                            BaseReply2 *reply) override
    {
        /*delete stationsave_info table*/
        std::vector<std::vector<std::string>> delete_condition(2, std::vector<std::string>(3, ""));
        delete_condition[0] = {"string", "station_id", request->station_id_()};
        delete_condition[1] = {"int", "order_id", request->order_id_()};

        if (DeleteMysql("stationsave_info", delete_condition) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("stationsave info delete failed");
            LOG(INFO) << "stationsave info delete failed, phone:" << request->stationer_id_();
            return Status::OK;
        }
        LOG(INFO) << "stationsave info delete success, phone:" << request->stationer_id_();

        /*insert transport_info*/
        /*自动拼接消息，生成格式如下：*/
        /*order_id 出库 station_name, 前往 next_address, 处理人: stationer_id*/
        std::string transport_description = request->order_id_() + " 出库 " + get_station_name(request->station_id_()) +
                                            "前往 " + request->next_address_() + ", 处理人联系方式: " + request->stationer_id_();
        std::vector<std::vector<std::string>> info_3(5, std::vector<std::string>(3, ""));
        info_3[0] = {"null", "", "null"}; // id自增
        info_3[1] = {"int", "", request->order_id_()};
        info_3[2] = {"int", "", "1"};
        info_3[3] = {"null", "", "CURRENT_TIMESTAMP"}; // timestamp自动计算
        info_3[4] = {"string", "", transport_description};

        if (InsertMysql("transport_info", info_3) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("transport record create failed");
            LOG(INFO) << "transport record insert failed, phone:" << request->stationer_id_();
            return Status::OK;
        }

        reply->set_return_result_(true);
        reply->set_return_message_("order into station succeed");
        LOG(INFO) << "order into station succeed, stationer id:" << request->stationer_id_();
        return Status::OK;
    }
};

void RunServer()
{
    std::string server_address(STATIONER_ORDER_SERVER);
    MyStationerOrderServiceImpl service;
    service.MysqlStart();

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG(INFO) << "User Order Server listening on " << server_address;

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
