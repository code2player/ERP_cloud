#pragma once

/*通信地址及端口号*/
const std::string REGISTER_IP = "192.168.80.134";
const std::string REGISTER_PORT = "50051";

const std::string LOGIN_IP = "192.168.80.134";
const std::string LOGIN_PORT = "50052";

const std::string USERORDER_IP = "192.168.80.134";
const std::string USERORDER_PORT = "50053";

const std::string STATIONERORDER_IP = "192.168.80.134";
const std::string STATIONERORDER_PORT = "50054";

const std::string ADMINSERVER_IP = "192.168.80.134";
const std::string ADMINSERVER_PORT = "50055";

/*构建测试数据数量级*/
const int base_num = 100;

const int user_num = base_num * 10;
const int station_num = base_num * 10;
const int stationer_num = base_num * 10;
const int admin_num = base_num * 10;
const int order_num = base_num * 100;
const int item_num = base_num * 1;
const int orderitemlist_num = base_num * 1000;
const int transport_num = base_num * 1000;
const int stationsave_num = base_num * 10;