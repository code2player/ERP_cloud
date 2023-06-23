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

class MysqlTools {
public:
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;

    int MysqlStart();


    int InsertMysql(const std::string table_name, const std::vector<std::string> &info);
    int InsertMysql(const std::string table_name, const std::vector<std::vector<std::string>> &info);

    int DeleteMysql(const std::string table_name, const std::vector<std::vector<std::string>> &delete_condition);

    int QueryMysql(const std::string table_name, std::vector<std::vector<std::string>> &query_result);

    int QueryMysqlExist(const std::string table_name, const std::vector<std::vector<std::string>> &info);

    /*table_name, query_condition, query_col_name, query_result*/
    int QueryMysql(const std::string table_name,
                   const std::vector<std::vector<std::string>> &info,
                   const std::vector<std::string> &info2,
                   std::vector<std::vector<std::string>> &query_result); // query_result返回info2中查询字段对应
    int QueryMysql(const std::string table_name,
                   const std::vector<std::vector<std::string>> &info,
                   std::vector<std::vector<std::string>> &query_result); // query_result返回info2中查询字段对应

    int UpdateMysql(const std::string table_name,
                    const std::vector<std::vector<std::string>> &info_set,
                    const std::vector<std::vector<std::string>> &info_where);

    int QueryMaxIdMysql(const std::string table_name, const std::string col_name, std::string &max_id);
};
