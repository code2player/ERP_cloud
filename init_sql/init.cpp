#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fcntl.h>
#include <fstream>
#include "../include/test_common.h"
using namespace std;

/*负责生成需要使用的sql文件*/
/*运行该sql文件，自动填充系统数据库，便于进行性能测试*/

void insert_func(ofstream &out, string table_name, vector<string> &info_list)
{
    string str = "INSERT INTO `";
    str += table_name;
    str += "` VALUES(";
    for (int i = 0; i < info_list.size(); i++)
    {
        if (i != 0)
        {
            str += ", ";
        }
        str += info_list[i];
    }
    str += ");";
    out << str << endl;

    //INSERT INTO `user_info` VALUES(null, 1, '1', 1);
}

int main()
{
    /*首先删除数据库、表，重新建立*/
    /*删除已有完成，先建立表结构*/
    /*单独写sql，不在这里做*/
    /*表结构建立完成，逐次填充测试数据，注意依赖关系*/
    /*打开文件*/
    ofstream out("init_insert.sql", ios::out);
    if(out.is_open() == 0)
    {
        cout<<"open failed"<<endl;
    }

    out<<"use Logistics_System;"<<endl;

    /*user*/
    vector<string> info_list(6, "");
    for (int i = 0; i < user_num; i++)
    {
        info_list = {"'" + to_string(13500000000 + i) + "'",
                     "'Aa111111'",
                     "'user" + to_string(i) + "'",
                     "''",
                     "'" + to_string(13500000000 + i) + "'",
                     "'1'"};
        insert_func(out, "user_info", info_list);
    }

    /*station*/
    info_list.clear();
    info_list.resize(4, "");
    for (int i = 0; i < station_num; i++)
    {
        info_list = {"'" + to_string(i) + "'",
                     "'station" + to_string(i) + "'",
                     "'position" + to_string(i) + "'",
                     "'description" + to_string(i) + "'"};
        insert_func(out, "station_info", info_list);
    }

    /*stationer*/
    info_list.clear();
    info_list.resize(6, "");
    for (int i = 0; i < stationer_num; i++)
    {
        info_list = {"'" + to_string(16600000000 + i) + "'",
                     "'Aa111111'",
                     "'" + to_string(i%station_num) + "'",
                     "'stationer" + to_string(i) + "'",
                     "'" + to_string(16600000000 + i) + "'",
                     "'5'"};
        insert_func(out, "stationer_info", info_list);
    }

    /*admin*/
    info_list.clear();
    info_list.resize(5, "");
    for (int i = 0; i < admin_num; i++)
    {
        info_list = {"'" + to_string(18600000000 + i) + "'",
                     "'Aa111111'",
                     "'stationer" + to_string(i) + "'",
                     "'" + to_string(18600000000 + i) + "'",
                     "'10'"};
        insert_func(out, "admin_info", info_list);
    }

    /*order*/
    info_list.clear();
    info_list.resize(9, "");
    for (int i = 0; i < order_num; i++)
    {
        info_list = {"null",
                     "'" + to_string(13500000000 + i % user_num) + "'",
                     "'" + to_string(13500000000 + (i + 1) % user_num) + "'",
                     "'addr1_" + to_string(13500000000 + i % user_num) + "'",
                     "'addr2_" + to_string(13500000000 + (i + 1) % user_num) + "'",
                     "100.00",
                     "CURRENT_TIMESTAMP",
                     "'运送中'",
                     "'description" + to_string(i) + "'"};
        insert_func(out, "order_info", info_list);
    }

    /*item*/
    info_list.clear();
    info_list.resize(4, "");
    for (int i = 0; i < item_num; i++)
    {
        info_list = {"'" + to_string(i) + "'",
                     "'item" + to_string(i) + "'",
                     to_string(i),
                     "'item description" + to_string(i) + "'"};
        insert_func(out, "item_info", info_list);
    }

    /*orderitemlist*/
    info_list.clear();
    info_list.resize(4, "");
    for (int i = 0; i < orderitemlist_num; i++)
    {
        info_list = {"null",
                     to_string(i % order_num + 1),
                     "'" + to_string(i % item_num) + "'",
                     to_string(i % 10 + 1)};
        insert_func(out, "orderitemlist_info", info_list);
    }

    /*transport*/
    info_list.clear();
    info_list.resize(5, "");
    for (int i = 0; i < transport_num; i++)
    {
        info_list = {"null",
                     to_string(i % order_num + 1),
                     "1",
                     "CURRENT_TIMESTAMP",
                     "'transport description" + to_string(i) + "'"};
        insert_func(out, "transport_info", info_list);
    }

    /*stationsave*/
    info_list.clear();
    info_list.resize(5, "");
    for (int i = 0; i < stationsave_num; i++)
    {
        info_list = {"null",
                     to_string(i % order_num + 1),
                     "'" + to_string(i % station_num) + "'",
                     "CURRENT_TIMESTAMP"};
        insert_func(out, "stationsave_info", info_list);
    }

    cout<<"init file generate succeed."<<endl;

    out.close();
    return 0;

}



