#pragma once
#include <iostream>
#include <memory>
#include <string>



/*���ڶԺ궨��Ƚ���ͳһ�Ĺ���*/
const std::string identity_list[3] = {"user", "stationer", "admin"};

/*ͨ�ŵ�ַ���˿ں�*/
const std::string REGISTER_IP = "106.15.251.12";
const std::string REGISTER_PORT = "30001";

const std::string LOGIN_IP = REGISTER_IP;
const std::string LOGIN_PORT = "30002";

const std::string USERORDER_IP = REGISTER_IP;
const std::string USERORDER_PORT = "30003";

const std::string STATIONERORDER_IP = REGISTER_IP;
const std::string STATIONERORDER_PORT = "30004";

const std::string ADMINSERVER_IP = REGISTER_IP;
const std::string ADMINSERVER_PORT = "30005";

