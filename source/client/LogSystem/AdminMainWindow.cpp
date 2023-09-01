#pragma execution_character_set("utf-8")  
#include "AdminMainWindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(GetAllItemList()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(GetAllStationList()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(GetAllOrderList()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(AddItem()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(DelItem()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(AddStation()));
	connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(DelStation()));
	connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(UpdateOrder()));

    /*创建表结构*/
    itemlist_model = new QStandardItemModel(ui.tableView);//初始化
    stationlist_model = new QStandardItemModel(ui.tableView_2);//初始化
    orderlist_model = new QStandardItemModel(ui.tableView_3);//初始化

    /*设置项*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑


    /*设置物品列表列字段名*/
    itemlist_model->setRowCount(0);
    itemlist_model->setColumnCount(4);
    itemlist_model->setHeaderData(0, Qt::Horizontal, "物品id");
    itemlist_model->setHeaderData(1, Qt::Horizontal, "物品名");
    itemlist_model->setHeaderData(2, Qt::Horizontal, "物品价格");
    itemlist_model->setHeaderData(3, Qt::Horizontal, "物品备注");

    /*设置站点列表列字段名*/
    stationlist_model->setRowCount(0);
    stationlist_model->setColumnCount(4);
    stationlist_model->setHeaderData(0, Qt::Horizontal, "站点id");
    stationlist_model->setHeaderData(1, Qt::Horizontal, "站点名");
    stationlist_model->setHeaderData(2, Qt::Horizontal, "站点地址");
    stationlist_model->setHeaderData(3, Qt::Horizontal, "站点备注");

    /*设置订单列表列字段名*/
    orderlist_model->setRowCount(0);
    orderlist_model->setColumnCount(9);
    orderlist_model->setHeaderData(0, Qt::Horizontal, "订单号");
    orderlist_model->setHeaderData(1, Qt::Horizontal, "发货方电话");
    orderlist_model->setHeaderData(2, Qt::Horizontal, "收货方电话");
    orderlist_model->setHeaderData(3, Qt::Horizontal, "发货方地址");
    orderlist_model->setHeaderData(4, Qt::Horizontal, "收货方地址");
    orderlist_model->setHeaderData(5, Qt::Horizontal, "订单金额");
    orderlist_model->setHeaderData(6, Qt::Horizontal, "下单时间");
    orderlist_model->setHeaderData(7, Qt::Horizontal, "订单状态");
    orderlist_model->setHeaderData(8, Qt::Horizontal, "订单备注");



}

AdminMainWindow::~AdminMainWindow()
{
}

class AdminServiceClient {
public:
    AdminServiceClient(std::shared_ptr<Channel> channel)
        : stub_(AdminService::NewStub(channel)) {}

    bool GetAllItemListRpc(const AdminId& request, AllItemList& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->GetAllItemList(&context, request, &reply);

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

    bool GetAllStationListRpc(const AdminId& request, AllStationList& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->GetAllStationList(&context, request, &reply);
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

    bool GetAllOrderListRpc(const AdminId& request, AllOrderList& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->GetAllOrderList(&context, request, &reply);

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

    bool AddItemRpc(const ItemInfo& request, BaseReply3& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->AddItem(&context, request, &reply);

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

    bool DelItemRpc(const ItemInfo& request, BaseReply3& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->DelItem(&context, request, &reply);

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

    bool AddStationRpc(const StationInfo& request, BaseReply3& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->AddStation(&context, request, &reply);

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

    bool DelStationRpc(const StationInfo& request, BaseReply3& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->DelStation(&context, request, &reply);

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

    bool UpdateOrderRpc(const OrderInfo& request, BaseReply3& reply, std::string& return_message_) {
        ClientContext context;

        /*rpc通信*/
        Status status = stub_->UpdateOrder(&context, request, &reply);

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
    std::unique_ptr<AdminService::Stub> stub_;
};


void AdminMainWindow::GetAllItemList()
{
    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllItemListRpc(admin_id_impl_, item_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "获取item列表错误", QString::fromStdString(return_message_));
    }

    /*界面显示*/
    itemlist_model->setRowCount(item_list_impl_.item_info_().size());
    for (int i = 0; i < item_list_impl_.item_info_().size(); i++) {
        itemlist_model->setItem(i, 0, new QStandardItem(QString::fromStdString(item_list_impl_.item_info_(i).item_id_())));
        itemlist_model->setItem(i, 1, new QStandardItem(QString::fromStdString(item_list_impl_.item_info_(i).item_name_())));
        itemlist_model->setItem(i, 2, new QStandardItem(QString::fromStdString(item_list_impl_.item_info_(i).item_price_())));
        itemlist_model->setItem(i, 3, new QStandardItem(QString::fromStdString(item_list_impl_.item_info_(i).item_description_())));
    }
    ui.tableView->setModel(itemlist_model);
}

void AdminMainWindow::GetAllStationList()
{
    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllStationListRpc(admin_id_impl_, station_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "获取Station列表错误", QString::fromStdString(return_message_));
    }

    /*界面显示*/
    stationlist_model->setRowCount(station_list_impl_.station_info_().size());
    for (int i = 0; i < station_list_impl_.station_info_().size(); i++) {
        stationlist_model->setItem(i, 0, new QStandardItem(QString::fromStdString(station_list_impl_.station_info_(i).station_id_())));
        stationlist_model->setItem(i, 1, new QStandardItem(QString::fromStdString(station_list_impl_.station_info_(i).station_name_())));
        stationlist_model->setItem(i, 2, new QStandardItem(QString::fromStdString(station_list_impl_.station_info_(i).station_position_())));
        stationlist_model->setItem(i, 3, new QStandardItem(QString::fromStdString(station_list_impl_.station_info_(i).station_description_())));
    }
    ui.tableView_2->setModel(stationlist_model);
}

void AdminMainWindow::GetAllOrderList()
{
    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllOrderListRpc(admin_id_impl_, order_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "获取Order列表错误", QString::fromStdString(return_message_));
    }

    /*界面显示*/
    stationlist_model->setRowCount(order_list_impl_.order_info_().size());
    for (int i = 0; i < order_list_impl_.order_info_().size(); i++) {
        orderlist_model->setItem(i, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_id_())));
        orderlist_model->setItem(i, 1, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_sender_id_())));
        orderlist_model->setItem(i, 2, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_receiver_id_())));
        orderlist_model->setItem(i, 3, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_start_address_())));
        orderlist_model->setItem(i, 4, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_end_address_())));
        orderlist_model->setItem(i, 5, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_money_())));
        orderlist_model->setItem(i, 6, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_time_())));
        orderlist_model->setItem(i, 7, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_status_())));
        orderlist_model->setItem(i, 8, new QStandardItem(QString::fromStdString(order_list_impl_.order_info_(i).order_description_())));
    }
    ui.tableView_3->setModel(orderlist_model);
}

void AdminMainWindow::AddItem()
{
    /*clear*/
    item_info_impl_.Clear();

    /*数据填充*/
    item_info_impl_.set_item_id_(ui.lineEdit->text().toStdString());
    item_info_impl_.set_item_name_(ui.lineEdit_2->text().toStdString());
    item_info_impl_.set_item_price_(ui.lineEdit_3->text().toStdString());
    item_info_impl_.set_item_description_(ui.plainTextEdit->toPlainText().toStdString());

    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddItemRpc(item_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "AddItem错误", QString::fromStdString(return_message_));
    }
    GetAllItemList();
}

void AdminMainWindow::DelItem()
{
    /*clear*/
    item_info_impl_.Clear();

    /*数据填充*/
    item_info_impl_.set_item_id_(ui.lineEdit->text().toStdString());

    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.DelItemRpc(item_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "DelItem错误", QString::fromStdString(return_message_));
    }
    GetAllItemList();
}

void AdminMainWindow::AddStation()
{
    /*clear*/
    station_info_impl_.Clear();

    /*数据填充*/
    station_info_impl_.set_station_id_(ui.lineEdit_4->text().toStdString());
    station_info_impl_.set_station_name_(ui.lineEdit_5->text().toStdString());
    station_info_impl_.set_station_position_(ui.lineEdit_6->text().toStdString());
    station_info_impl_.set_station_description_(ui.plainTextEdit_2->toPlainText().toStdString());

    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddStationRpc(station_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "AddStation错误", QString::fromStdString(return_message_));
    }
    GetAllStationList();
}

void AdminMainWindow::DelStation()
{
    /*clear*/
    station_info_impl_.Clear();

    /*数据填充*/
    station_info_impl_.set_station_id_(ui.lineEdit_4->text().toStdString());

    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddStationRpc(station_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "DelStation错误", QString::fromStdString(return_message_));
    }
    GetAllStationList();
}

void AdminMainWindow::UpdateOrder()
{
    /*clear*/
    order_info_impl_.Clear();

    /*数据填充*/
    order_info_impl_.set_order_id_(ui.lineEdit_8->text().toStdString());
    order_info_impl_.set_order_status_(ui.lineEdit_9->text().toStdString());
    order_info_impl_.set_order_start_address_(ui.plainTextEdit_3->toPlainText().toStdString());
    order_info_impl_.set_order_end_address_(ui.plainTextEdit_4->toPlainText().toStdString());
    order_info_impl_.set_order_description_(ui.plainTextEdit_5->toPlainText().toStdString());

    /*rpc通信*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.UpdateOrderRpc(order_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "UpdateOrder错误", QString::fromStdString(return_message_));
    }
    GetAllOrderList();
}



