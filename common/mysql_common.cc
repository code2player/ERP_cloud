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
#include "../include/mysql_common.h"

int MysqlTools::MysqlStart()
{
    /* 初始化 mysql 变量，失败返回NULL */
    if ((mysql = mysql_init(NULL)) == NULL)
    {
        LOG(ERROR) << "mysql_init failed";
        return -1;
    }

    LOG(INFO) << "mysql_init successed";

    /* 连接数据库，失败返回NULL
       1、mysqld没运行
       2、没有指定名称的数据库存在 */
    /*if (mysql_real_connect(mysql, "xpfmysql.rwlb.rds.aliyuncs.com", "root_ecs", "Aa111111", "Logistics_System", 0, NULL, 0) == NULL)
    {
        LOG(ERROR) << "mysql_real_connect failed(" << mysql_error(mysql) << ")";
        return -1;
    }*/

    if (mysql_real_connect(mysql, "localhost", "root", "root123", "Logistics_System", 0, NULL, 0) == NULL)
    {
        LOG(ERROR) << "mysql_real_connect failed(" << mysql_error(mysql) << ")";
        return -1;
    }

    LOG(INFO) << "mysql_real_connect to localhost, database Logistics_System, user root successed";
    return 1;
}

int MysqlTools::InsertMysql(const std::string table_name, const std::vector<std::string> &info)
{
    std::string inst = "INSERT INTO ";
    inst += table_name;
    inst += " VALUES (";

    // INSERT INTO `skill_info` VALUES('1', '能天使', 5, '倾泻子弹，造成中量伤害', '110%倍率的三连击');

    for (int i = 0; i < info.size(); i++)
    {
        if (i != 0)
            inst += ", ";
        inst += "\'";
        inst += info[i];
        inst += "\'";
    }
    inst += ");";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_insert failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    //LOG(INFO) << "mysql_insert success";
    return 1;
}

int MysqlTools::InsertMysql(const std::string table_name, const std::vector<std::vector<std::string>> &info)
{
    std::string inst = "INSERT INTO ";
    inst += table_name;
    inst += " VALUES (";

    // INSERT INTO `skill_info` VALUES('1', '能天使', 5, '倾泻子弹，造成中量伤害', '110%倍率的三连击');

    for (int i = 0; i < info.size(); i++)
    {
        if (i != 0)
            inst += ", ";

        if (info[i][0] == "string")
        {
            inst += "\'";
            inst += info[i][2];
            inst += "\'";
        }
        else{
            inst += info[i][2];
        }
    }
    inst += ");";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_insert failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    //LOG(INFO) << "mysql_insert success";
    return 1;
}

int MysqlTools::DeleteMysql(const std::string table_name, const std::vector<std::vector<std::string>> &delete_condition)
{
    std::string inst = "delete from ";
    inst += table_name;
    inst += " where ";

    for (int i = 0; i < delete_condition.size(); i++)
    {
        if (i != 0)
            inst += "and ";
        
        inst += delete_condition[i][1];
        inst += " = ";

        if (delete_condition[i][0] == "string")
        {
            inst += "\'";
            inst += delete_condition[i][2];
            inst += "\'";
        }
        else{
            inst += delete_condition[i][2];
        }
    }
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_delete failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    //LOG(INFO) << "mysql_delete success";
    return 1;
}

int MysqlTools::QueryMysql(const std::string table_name, std::vector<std::vector<std::string>> &query_result)
{
    query_result.clear();
    std::string inst = "select * from ";
    inst += table_name;
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_query failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
   注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        LOG(ERROR) << "mysql_store_result failed";
        return -1;
    }

    /* 当前查询到的记录的数量 */
    int return_row_num = (int)mysql_num_rows(result);
    //LOG(INFO) << "mysql_query success";

    /* 循环读取所有满足条件的记录 */
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        std::vector<std::string> temp_row(mysql_num_fields(result), "");
        for (int i = 0; i < temp_row.size(); i++)
        {
            temp_row[i] = row[i];
        }
        query_result.push_back(temp_row);
    }

    mysql_free_result(result);//注意：由于server为长连接，且result始终持有，必须使用free，否则出现内存泄漏！！！
    return return_row_num;
}

int MysqlTools::QueryMysqlExist(const std::string table_name, const std::vector<std::vector<std::string>> &info)
{
    std::string inst = "select * from ";
    inst += table_name;
    inst += " where ";

    for (int i = 0; i < info.size(); i++)
    {
        if (i != 0)
            inst += "and ";
        
        inst += info[i][1];
        inst += " = ";

        if (info[i][0] == "string")
        {
            inst += "\'";
            inst += info[i][2];
            inst += "\'";
        }
        else{
            inst += info[i][2];
        }
    }
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_query failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
   注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        LOG(ERROR) << "mysql_store_result failed";
        return -1;
    }

    /* 当前查询到的记录的数量 */

    int query_sum = (int)mysql_num_rows(result);
    //LOG(INFO) << "mysql_query success";
    mysql_free_result(result);//注意：由于server为长连接，且result始终持有，必须使用free，否则出现内存泄漏！！！

    return query_sum;
}

int MysqlTools::QueryMysql(const std::string table_name,
                           const std::vector<std::vector<std::string>> &info,
                           const std::vector<std::string> &info2,
                           std::vector<std::vector<std::string>> &query_result)
{
    query_result.clear();
    std::string inst = "select ";

    for (int i = 0; i < info2.size(); i++)
    {
        if (i != 0)
            inst += ",";
        inst += info2[i];
    }

    inst += " from ";
    inst += table_name;
    inst += " where ";

    for (int i = 0; i < info.size(); i++)
    {
        if (i != 0)
            inst += "and ";
        
        inst += info[i][1];
        inst += " = ";

        if (info[i][0] == "string")
        {
            inst += "\'";
            inst += info[i][2];
            inst += "\'";
        }
        else{
            inst += info[i][2];
        }
    }
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_query failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
   注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        LOG(ERROR) << "mysql_store_result failed";
        return -1;
    }

    /* 当前查询到的记录的数量 */
    int return_row_num = (int)mysql_num_rows(result);
    //LOG(INFO) << "mysql_query success";

    /* 循环读取所有满足条件的记录 */
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        std::vector<std::string> temp_row(info2.size(), "");
        for (int i = 0; i < temp_row.size(); i++)
        {
            temp_row[i] = row[i];
        }
        query_result.push_back(temp_row);
    }

    mysql_free_result(result);//注意：由于server为长连接，且result始终持有，必须使用free，否则出现内存泄漏！！！
    return return_row_num;
}

int MysqlTools::QueryMysql(const std::string table_name,
                           const std::vector<std::vector<std::string>> &info,
                           std::vector<std::vector<std::string>> &query_result)
{
    query_result.clear();
    std::string inst = "select * from ";
    inst += table_name;
    inst += " where ";

    for (int i = 0; i < info.size(); i++)
    {
        if (i != 0)
            inst += "and ";
        
        inst += info[i][1];
        inst += " = ";

        if (info[i][0] == "string")
        {
            inst += "\'";
            inst += info[i][2];
            inst += "\'";
        }
        else{
            inst += info[i][2];
        }
    }
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_query failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
   注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        LOG(ERROR) << "mysql_store_result failed";
        return -1;
    }

    /* 当前查询到的记录的数量 */
    int return_row_num = (int)mysql_num_rows(result);
    //LOG(INFO) << "mysql_query success";

    /* 循环读取所有满足条件的记录 */
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        std::vector<std::string> temp_row(mysql_num_fields(result), "");
        for (int i = 0; i < temp_row.size(); i++)
        {
            temp_row[i] = row[i];
        }
        query_result.push_back(temp_row);
    }

    mysql_free_result(result);//注意：由于server为长连接，且result始终持有，必须使用free，否则出现内存泄漏！！！
    return return_row_num;
}

int MysqlTools::UpdateMysql(const std::string table_name,
                            const std::vector<std::vector<std::string>> &info_set,
                            const std::vector<std::vector<std::string>> &info_where)
{
    std::string inst = "update ";
    inst += table_name;
    inst += " set ";
    /*info_set[0]类型, [1]字段名, [2]更新后内容 */
    /*info_where[0]类型, [1]字段名, [2]条件 */

    for (int i = 0; i < info_set.size(); i++)
    {
        if (i != 0)
            inst += ", ";

        inst += info_set[i][1];
        inst += " = ";

        if (info_set[i][0] == "string")
        {
            inst += "\'";
            inst += info_set[i][2];
            inst += "\'";
        }
        else
        {
            inst += info_set[i][2];
        }
    }
    inst += " where ";

    for (int i = 0; i < info_where.size(); i++)
    {
        if (i != 0)
            inst += ", ";

        inst += info_where[i][1];
        inst += " = ";

        if (info_where[i][0] == "string")
        {
            inst += "\'";
            inst += info_where[i][2];
            inst += "\'";
        }
        else
        {
            inst += info_where[i][2];
        }
    }
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_update failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    //LOG(INFO) << "mysql_update success";
    return 1;
}

int MysqlTools::QueryMaxIdMysql(const std::string table_name, const std::string col_name, std::string &max_id)
{
    std::string inst = "select max(";
    inst += col_name;
    inst += ") from ";
    inst += table_name;
    inst += ";";

    if (mysql_query(mysql, inst.c_str()))
    {
        LOG(ERROR) << "mysql_query failed(" << mysql_error(mysql) << ")";
        LOG(ERROR) << "inst:" << inst ;
        return -1;
    }

    /* 将查询结果存储起来，出现错误则返回NULL
   注意：查询结果为NULL，不会返回NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        LOG(ERROR) << "mysql_store_result failed";
        return -1;
    }

    /* 当前查询到的记录的数量 */
    int return_row_num = (int)mysql_num_rows(result);
    if(return_row_num != 1){
        LOG(ERROR) << "mysql_maxid_result failed";
        return -1;
    }
    
    //LOG(INFO) << "mysql_query success";
    row = mysql_fetch_row(result);
    max_id = row[0];
    mysql_free_result(result);//注意：由于server为长连接，且result始终持有，必须使用free，否则出现内存泄漏！！！
    return 1;
}