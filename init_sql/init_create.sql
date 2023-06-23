drop database if exists Logistics_System;
create database Logistics_System;
use Logistics_System;

# 人员的表
# 分表建立意味着数据的隔离，普通用户信息与工作人员显然不能混用

#sender和receiver在应用层逻辑上隔离，在物理存储层共享
#普通用户，对应sender和receiver类，显然普通用户可以同时作为sender和receiver
#order相关id自增(int), user相关id(string)为phone or idcard
create table user_info(
    user_id varchar(20) not null primary key,
    user_password varchar(40) not null,
    user_name varchar(20) not null,
    user_address varchar(20) not null,
    user_phone varchar(20) not null,
    user_authority varchar(20) not null
);

#工作站点信息列表
create table station_info(
    station_id varchar(20) not null primary key,
    station_name varchar(40) not null,
    station_position varchar(100) not null,
    station_description varchar(400) not null
);

#站点工作人员，对应stationer类
create table stationer_info(
    stationer_id varchar(20) not null primary key,
    stationer_password varchar(40) not null,
    stationer_station_id varchar(20) not null,
    stationer_name varchar(20) not null,
    stationer_phone varchar(20) not null,
    stationer_authority varchar(20) not null,

    constraint `stationer_station_con` foreign key (`stationer_station_id`)
        references `station_info`(`station_id`)
);

#系统管理人员，对应admin类
create table admin_info(
    admin_id varchar(20) not null primary key,
    admin_password varchar(40) not null,
    admin_name varchar(20) not null,
    admin_phone varchar(20) not null,
    admin_authority varchar(20) not null
);

#订单表，是高频查询区域AUTO_INCREMENT
create table order_info(
    order_id integer not null primary key AUTO_INCREMENT,
    order_sender_id varchar(20) not null,
    order_receiver_id varchar(20) not null,
    order_start_address varchar(200) not null,
    order_end_address varchar(200) not null,
    order_money decimal(10,2) not null,
    order_time timestamp not null,
    order_status varchar(20) not null,
    order_description varchar(200) not null,

    constraint `order_sender_con` foreign key (`order_sender_id`)
        references `user_info`(`user_id`),
    constraint `order_receiver_con` foreign key (`order_receiver_id`)
        references `user_info`(`user_id`)
);

#货物信息表
create table item_info(
    item_id varchar(20) not null primary key,
    item_name varchar(20) not null,
    item_price decimal(10,2) not null,
    item_description varchar(200) not null
);

#订单货物信息列表，视情况可能分库/分表/加索引，
create table orderitemlist_info(
    orderitemlist_id integer not null primary key AUTO_INCREMENT,
    orderitemlist_order_id integer not null,
    orderitemlist_item_id varchar(20) not null,
    item_number integer not null,

    constraint `orderitemlist_order_con` foreign key (`orderitemlist_order_id`)
        references `order_info`(`order_id`),
    constraint `orderitemlist_item_con` foreign key (`orderitemlist_item_id`)
        references `item_info`(`item_id`)
);

#运输链路流转列表，description字段的构建在server端做逻辑上的字符串拼接
create table transport_info(
    transport_id integer not null primary key AUTO_INCREMENT,
    transport_order_id integer not null,
    transport_number integer not null, #链路上第几次，每流转一次状态+1
    transport_time timestamp not null,
    transport_description varchar(200) not null,

    constraint `transport_order_con` foreign key (`transport_order_id`)
        references `order_info`(`order_id`)
);


#存储某个station中的order列表，有对应的insert/delete操作
#入库/出库同时insert/delete该表和transport_info表
#user没有访问该表的权限
create table stationsave_info(
    stationsave_id integer not null primary key AUTO_INCREMENT,
    order_id integer not null,
    station_id varchar(20) not null, 
    input_time timestamp not null, #入库时间

    constraint `stationsave_order_con` foreign key (`order_id`)
        references `order_info`(`order_id`),
    constraint `stationsave_station_con` foreign key (`station_id`)
        references `station_info`(`station_id`)
);