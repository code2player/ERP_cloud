#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unordered_map>
#include <fcntl.h>
#include "glog/logging.h" // glog 头文件
#include "glog/raw_logging.h"

#include <mysql/mysql.h>


const std::string REGISTER_SERVER = "0.0.0.0:50051";
const std::string LOGIN_SERVER = "0.0.0.0:50052";
const std::string USER_ORDER_SERVER = "0.0.0.0:50053";
const std::string STATIONER_ORDER_SERVER = "0.0.0.0:50054";
const std::string ADMIN_ORDER_SERVER = "0.0.0.0:50055";

