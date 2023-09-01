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

#include "myuser.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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

std::vector <std::string> OrderStatus = {"运送中", "待收货", "已收件", "异常", "退单", "订单取消"};

// Logic and data behind the server's behavior.
class MyUserOrderServiceImpl final : public UserOrder::Service, public MysqlTools
{
private:
    int FillSenderList(const UserId *request, OrderList *reply)
    {
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> info(1, std::vector<std::string>(3, ""));
        std::vector<std::vector<std::string>> query_result;
        info[0] = {"string", "order_sender_id", request->user_phone_()};
        int order_list_num = QueryMysql(table_name, info, query_result);
        if (order_list_num < 0)
        {
            reply->set_return_result_(false);
            LOG(INFO) << "user sender order query failed, phone:" << request->user_phone_();
            return -1;
        }

        /*需要注意此处处理了两层repeated嵌套，具体数据格式查询proto文件*/
        for (int i = 0; i < order_list_num; i++)
        {
            OrderDetail *order_sender_list_;
            order_sender_list_ = reply->add_order_sender_list_();
            order_sender_list_->set_order_id_(query_result[i][0]);
            order_sender_list_->set_order_sender_id_(query_result[i][1]);
            order_sender_list_->set_order_receiver_id_(query_result[i][2]);
            order_sender_list_->set_order_start_address_(query_result[i][3]);
            order_sender_list_->set_order_end_address_(query_result[i][4]);
            order_sender_list_->set_order_money_(query_result[i][5]);
            order_sender_list_->set_order_time_(query_result[i][6]);
            order_sender_list_->set_order_status_(query_result[i][7]);
            order_sender_list_->set_order_description_(query_result[i][8]);

            /*处理第二层嵌套，再次循环*/
            /*std::string table_name_2 = "item_info JOIN orderitemlist_info ON (item_info.item_id = orderitemlist_info.orderitemlist_item_id)";
            std::vector<std::vector<std::string>> info_2(1, std::vector<std::string>(3, ""));
            std::vector<std::string> query_col_name = {"item_id", "item_name", "item_price", "item_description", "item_number"};
            std::vector<std::vector<std::string>> query_result_2;
            info_2[0] = {"string", "orderitemlist_order_id", order_sender_list_->order_id_()};
            int order_list_num_2 = QueryMysql(table_name_2, info_2, query_col_name, query_result_2);
            if (order_list_num_2 < 0)
            {
                reply->set_return_result_(false);
                LOG(INFO) << "user sender order query failed, phone:" << request->user_phone_();
                return -1;
            }

            for (int j = 0; j < order_list_num_2; j++)
            {
                OrderItem *item_info_;
                item_info_ = order_sender_list_->add_item_info_();
                item_info_->set_item_id_(query_result_2[j][0]);
                item_info_->set_item_name_(query_result_2[j][1]);
                item_info_->set_item_price_(query_result_2[j][2]);
                item_info_->set_item_description_(query_result_2[j][3]);
                item_info_->set_item_number_(atoi(query_result_2[j][4].c_str()));
            }*/
        }
        reply->set_return_result_(true);
        LOG(INFO) << "user sender order query success, phone:" << request->user_phone_();
        return 1;
    }

    int FillReceiverList(const UserId *request, OrderList *reply)
    {
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> info(1, std::vector<std::string>(3, ""));
        std::vector<std::vector<std::string>> query_result;
        info[0] = {"string", "order_receiver_id", request->user_phone_()};
        int order_list_num = QueryMysql(table_name, info, query_result);
        if (order_list_num < 0)
        {
            reply->set_return_result_(false);
            LOG(INFO) << "user receiver order query failed, phone:" << request->user_phone_();
            return -1;
        }

        /*需要注意此处处理了两层repeated嵌套，具体数据格式查询proto文件*/
        for (int i = 0; i < order_list_num; i++)
        {
            OrderDetail *order_receiver_list_;
            order_receiver_list_ = reply->add_order_receiver_list_();
            order_receiver_list_->set_order_id_(query_result[i][0]);
            order_receiver_list_->set_order_sender_id_(query_result[i][1]);
            order_receiver_list_->set_order_receiver_id_(query_result[i][2]);
            order_receiver_list_->set_order_start_address_(query_result[i][3]);
            order_receiver_list_->set_order_end_address_(query_result[i][4]);
            order_receiver_list_->set_order_money_(query_result[i][5]);
            order_receiver_list_->set_order_time_(query_result[i][6]);
            order_receiver_list_->set_order_status_(query_result[i][7]);
            order_receiver_list_->set_order_description_(query_result[i][8]);

            /*处理第二层嵌套，再次循环*/
            /*std::string table_name_2 = "item_info JOIN orderitemlist_info ON (item_info.item_id = orderitemlist_info.orderitemlist_item_id)";
            std::vector<std::vector<std::string>> info_2(1, std::vector<std::string>(3, ""));
            std::vector<std::string> query_col_name = {"item_id", "item_name", "item_price", "item_description", "item_number"};
            std::vector<std::vector<std::string>> query_result_2;
            info_2[0] = {"string", "orderitemlist_order_id", order_receiver_list_->order_id_()};
            int order_list_num_2 = QueryMysql(table_name_2, info_2, query_col_name, query_result_2);
            if (order_list_num_2 < 0)
            {
                reply->set_return_result_(false);
                LOG(INFO) << "user receiver order query failed, phone:" << request->user_phone_();
                return -1;
            }

            for (int j = 0; j < order_list_num_2; j++)
            {
                OrderItem *item_info_;
                item_info_ = order_receiver_list_->add_item_info_();
                item_info_->set_item_id_(query_result_2[j][0]);
                item_info_->set_item_name_(query_result_2[j][1]);
                item_info_->set_item_price_(query_result_2[j][2]);
                item_info_->set_item_description_(query_result_2[j][3]);
                item_info_->set_item_number_(atoi(query_result_2[j][4].c_str()));
            }*/
        }
        reply->set_return_result_(true);
        LOG(INFO) << "user receiver order query success, phone:" << request->user_phone_();
        return 1;
    }
    Status GetOrderList(ServerContext *context, const UserId *request,
                        OrderList *reply) override
    {
        int SenderResult = FillSenderList(request, reply);
        if (SenderResult < 0)
            return Status::OK;
        int ReceiverResult = FillReceiverList(request, reply);
        return Status::OK;
    }
    Status CreateOrder(ServerContext *context, const OrderDetail *request,
                        BaseReply *reply) override
    {
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> info(9, std::vector<std::string>(3, ""));
        info[0] = {"null", "", "null"};//id自增
        info[1] = {"string", "", request->order_sender_id_()};
        info[2] = {"string", "", request->order_receiver_id_()};
        info[3] = {"string", "", request->order_start_address_()};
        info[4] = {"string", "", request->order_end_address_()};
        info[5] = {"string", "", request->order_money_()};//计算后字符串传输，否则可能出现跨平台精度丢失
        info[6] = {"null", "", "CURRENT_TIMESTAMP"};//timestamp自动计算
        info[7] = {"string", "", "运送中"};
        info[8] = {"string", "", request->order_description_()};

        if (InsertMysql(table_name, info) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("order create failed");
            LOG(INFO) << "order insert failed, phone:" << request->order_sender_id_();
            return Status::OK;
        }

        /*获取自增order_id*/
        std::string new_order_id;
        if(QueryMaxIdMysql("order_info", "order_id", new_order_id) < 0){
            reply->set_return_result_(false);
            reply->set_return_message_("order create failed");
            LOG(INFO) << "order get maxid failed, phone:" << request->order_sender_id_();
            return Status::OK;
        }

        /*填充orderitemlist_info*/
        std::string table_name_2 = "orderitemlist_info";
        std::vector<std::vector<std::string>> info_2(4, std::vector<std::string>(3, ""));
        info_2[0] = {"null", "", "null"};
        info_2[1] = {"int", "", new_order_id};
        for (int i = 0; i < request->item_info__size(); i++)
        {
            info_2[2] = {"string", "", request->item_info_(i).item_id_()};
            info_2[3] = {"int", "", std::to_string(request->item_info_(i).item_number_())};
            
            if (InsertMysql(table_name_2, info_2) < 0)
            {
                reply->set_return_result_(false);
                reply->set_return_message_("order create failed");
                LOG(INFO) << "orderitemlist insert failed, phone:" << request->order_sender_id_();
                return Status::OK;
            }
        }

        reply->set_return_result_(true);
        reply->set_return_message_("order create successed");
        LOG(INFO) << "orderitemlist insert successed, phone:" << request->order_sender_id_();
        return Status::OK;
    }
    Status UpdateOrderState(ServerContext *context, const UpdateOrderStateRequest *request,
                            BaseReply *reply) override
    {
        std::string table_name = "order_info";
        std::vector<std::vector<std::string>> info_set(1, std::vector<std::string>(3, ""));
        std::vector<std::vector<std::string>> info_where(1, std::vector<std::string>(3, ""));
        info_set[0] = {"string", "order_status", request->order_status_()};
        info_where[0] = {"int", "order_id", request->order_id_()};

        if (UpdateMysql(table_name, info_set, info_where) < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("order status update failed");
            LOG(INFO) << "order status update failed, order_id:" << request->order_id_();
        }
        else
        {
            reply->set_return_result_(true);
            reply->set_return_message_("order status update successed");
            LOG(INFO) << "order status update successed, order_id:" << request->order_id_();
        }

        return Status::OK;
    }

    Status GetSpecificOrder(ServerContext *context, const OrderId *request,
                            SpecificOrder *reply) override
    {
        /*填充transport_list_*/
        std::string table_name = "transport_info";
        std::vector<std::vector<std::string>> query_condition(1, std::vector<std::string>(3, ""));
        std::vector<std::string> query_col_name = {"transport_time", "transport_description"};
        std::vector<std::vector<std::string>> query_result;
        query_condition[0] = {"string", "transport_order_id", request->order_id_()};

        int order_list_num = QueryMysql(table_name, query_condition, query_col_name, query_result);
        if (order_list_num < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("transport list query failed");
            LOG(INFO) << "transport_info query failed, order id:" << request->order_id_();
            return Status::OK;
        }

        for (int j = 0; j < order_list_num; j++)
        {
            OrderTransport *transport_list_;
            transport_list_ = reply->add_transport_list_();
            transport_list_->set_transport_time_(query_result[j][0]);
            transport_list_->set_transport_description_(query_result[j][1]);
        }

        /*填充item_list_*/
        std::string table_name_2 = "item_info JOIN orderitemlist_info ON (item_info.item_id = orderitemlist_info.orderitemlist_item_id)";
        std::vector<std::vector<std::string>> query_condition_2(1, std::vector<std::string>(3, ""));
        std::vector<std::string> query_col_name_2 = {"item_id", "item_name", "item_price", "item_description", "item_number"};
        std::vector<std::vector<std::string>> query_result_2;
        query_condition_2[0] = {"string", "orderitemlist_order_id", request->order_id_()};
        int order_list_num_2 = QueryMysql(table_name_2, query_condition_2, query_col_name_2, query_result_2);

        if (order_list_num_2 < 0)
        {
            reply->set_return_result_(false);
            reply->set_return_message_("item list query failed");
            LOG(INFO) << "user sender order query failed, order id:" << request->order_id_();
            return Status::OK;
        }

        for (int j = 0; j < order_list_num_2; j++)
        {
            OrderItem *item_list_;
            item_list_ = reply->add_item_list_();
            item_list_->set_item_id_(query_result_2[j][0]);
            item_list_->set_item_name_(query_result_2[j][1]);
            item_list_->set_item_price_(query_result_2[j][2]);
            item_list_->set_item_description_(query_result_2[j][3]);
            item_list_->set_item_number_(atoi(query_result_2[j][4].c_str()));
        }

        reply->set_return_result_(true);
        reply->set_return_message_("get SpecificOrder query succeed");
        LOG(INFO) << "user specific order query success, order id:" << request->order_id_();
        return Status::OK;
    }
};

void RunServer()
{
    std::string server_address(USER_ORDER_SERVER);
    MyUserOrderServiceImpl service;
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
