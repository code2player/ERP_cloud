#pragma execution_character_set("utf-8")  
#include "StationerMainWindow.h"

StationerMainWindow::StationerMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    /*设定ui*/
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(InStation()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(OutStation()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(GetStationOrderList()));

    order_list_model = new QStandardItemModel(ui.tableView);//初始化

    /*设置项*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑


    /*设置sender订单列表列字段名*/
    order_list_model->setRowCount(0);
    order_list_model->setColumnCount(2);
    order_list_model->setHeaderData(0, Qt::Horizontal, "订单号");
    order_list_model->setHeaderData(1, Qt::Horizontal, "入库时间");



}

StationerMainWindow::~StationerMainWindow()
{
}

class StationerOrderClient {
public:
    StationerOrderClient(std::shared_ptr<Channel> channel)
        : stub_(StationerOrder::NewStub(channel)) {}

    bool GetStationerInfoRpc(const StationerId& request, StationerInfo& reply, std::string& return_message_) {
        ClientContext context;
        /*rpc通信*/
        Status status = stub_->GetStationerInfo(&context, request, &reply);

        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed, " + reply.return_message_();
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

    bool GetStationOrderListRpc(const StationId& request, SaveOrderList& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->GetStationOrderList(&context, request, &reply);
        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed, " + reply.return_message_();
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

    bool InStationRpc(const InStationRequest& request, BaseReply2& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->InStation(&context, request, &reply);

        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed, " + reply.return_message_();
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

    bool OutStationRpc(const OutStationRequest& request, BaseReply2& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->OutStation(&context, request, &reply);

        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed, " + reply.return_message_();
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

private:
    std::unique_ptr<StationerOrder::Stub> stub_;
};

void StationerMainWindow::GetStationerInfo()
{
    ui.lineEdit_3->setText(QString::fromStdString(userid_impl_.stationer_id_()));
    /*rpc通信*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetStationerInfoRpc(userid_impl_, stationer_info__impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "初始化用户信息错误", QString::fromStdString(return_message_));
    }

}


void StationerMainWindow::GetStationOrderList()
{
    /*初始化*/
    /*if (flagx == 0) {
        GetStationerInfo();
        flagx = 1;
    }*/
    

    stationid_impl_.set_station_id_(stationer_info__impl_.station_id_());
    /*rpc通信*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetStationOrderListRpc(stationid_impl_, save_order_list_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "获取当前仓库订单列表错误", QString::fromStdString(return_message_));
    }

    /*填充表格*/
    order_list_model->setRowCount(save_order_list_impl_.order_list_().size());
    for (int i = 0; i < save_order_list_impl_.order_list_().size(); i++) {
        order_list_model->setItem(i, 0, new QStandardItem(QString::fromStdString(save_order_list_impl_.order_list_(i).order_id_())));
        order_list_model->setItem(i, 1, new QStandardItem(QString::fromStdString(save_order_list_impl_.order_list_(i).input_time_())));
    }
    ui.tableView->setModel(order_list_model);
}

void StationerMainWindow::InStation()
{
    in_station_request_impl_.set_stationer_id_(stationer_info__impl_.stationer_id_());
    in_station_request_impl_.set_station_id_(stationer_info__impl_.station_id_());
    in_station_request_impl_.set_order_id_(ui.lineEdit->text().toStdString());

    /*rpc通信*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.InStationRpc(in_station_request_impl_, basereply_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "入库错误", QString::fromStdString(return_message_));
    }
    GetStationOrderList();
}

void StationerMainWindow::OutStation()
{
    out_station_request_impl_.set_stationer_id_(stationer_info__impl_.stationer_id_());
    out_station_request_impl_.set_station_id_(stationer_info__impl_.station_id_());
    out_station_request_impl_.set_order_id_(ui.lineEdit_2->text().toStdString());
    out_station_request_impl_.set_next_address_(ui.plainTextEdit->toPlainText().toStdString());

    /*rpc通信*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.OutStationRpc(out_station_request_impl_, basereply_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "出库错误", QString::fromStdString(return_message_));
    }
    GetStationOrderList();
}

