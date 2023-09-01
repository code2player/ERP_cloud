#pragma execution_character_set("utf-8")  
#include "UserMainWindow.h"

UserMainWindow::UserMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(CreateOrder()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(GetOrderList()));



    /*订单列表的一系列操作*/
    sender_model = new QStandardItemModel(ui.tableView);//初始化
    receiver_model = new QStandardItemModel(ui.tableView_2);//初始化
    detail_model = new QStandardItemModel(ui.tableView_3);//初始化
    transport_model = new QStandardItemModel(ui.tableView_4);//初始化
    itemlist_model = new QStandardItemModel(ui.tableView_5);//初始化


    /*设置项*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑
    ui.tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑

    /*单击、双击等事件*/
    connect(ui.tableView, &QTableView::clicked, this, &UserMainWindow::ClickedTable);
    connect(ui.tableView, &QTableView::doubleClicked, this, &UserMainWindow::DoubleClickedTable);
    connect(ui.tableView_2, &QTableView::clicked, this, &UserMainWindow::ClickedTable);
    connect(ui.tableView_2, &QTableView::doubleClicked, this, &UserMainWindow::DoubleClickedTable);

    /*设置sender订单列表列字段名*/
    sender_model->setRowCount(0);
    sender_model->setColumnCount(6);
    sender_model->setHeaderData(0, Qt::Horizontal, "订单号");
    sender_model->setHeaderData(1, Qt::Horizontal, "发货方电话");
    sender_model->setHeaderData(2, Qt::Horizontal, "收货方电话");
    sender_model->setHeaderData(3, Qt::Horizontal, "订单金额");
    sender_model->setHeaderData(4, Qt::Horizontal, "下单时间");
    sender_model->setHeaderData(5, Qt::Horizontal, "订单状态");

    
    /*设置receiver订单列表列字段名*/
    receiver_model->setRowCount(0);
    receiver_model->setColumnCount(6);
    receiver_model->setHeaderData(0, Qt::Horizontal, "订单号");
    receiver_model->setHeaderData(1, Qt::Horizontal, "发货方电话");
    receiver_model->setHeaderData(2, Qt::Horizontal, "收货方电话");
    receiver_model->setHeaderData(3, Qt::Horizontal, "订单金额");
    receiver_model->setHeaderData(4, Qt::Horizontal, "下单时间");
    receiver_model->setHeaderData(5, Qt::Horizontal, "订单状态");


    /*设置detail行字段名（vertical）*/
    detail_model->setRowCount(9);
    detail_model->setColumnCount(1);
    detail_model->setHeaderData(0, Qt::Vertical, "订单号");
    detail_model->setHeaderData(1, Qt::Vertical, "发货方电话");
    detail_model->setHeaderData(2, Qt::Vertical, "收货方电话");
    detail_model->setHeaderData(3, Qt::Vertical, "发货方地址");
    detail_model->setHeaderData(4, Qt::Vertical, "收货方地址");
    detail_model->setHeaderData(5, Qt::Vertical, "订单金额");
    detail_model->setHeaderData(6, Qt::Vertical, "下单时间");
    detail_model->setHeaderData(7, Qt::Vertical, "订单状态");
    detail_model->setHeaderData(8, Qt::Vertical, "订单备注");


    /*设置transport列表列字段名*/
    transport_model->setRowCount(0);
    transport_model->setColumnCount(2);
    transport_model->setHeaderData(0, Qt::Horizontal, "时间");
    transport_model->setHeaderData(1, Qt::Horizontal, "描述");


    /*设置item列表列字段名*/
    itemlist_model->setRowCount(0);
    itemlist_model->setColumnCount(4);
    itemlist_model->setHeaderData(0, Qt::Horizontal, "货物号");
    itemlist_model->setHeaderData(1, Qt::Horizontal, "货物名");
    itemlist_model->setHeaderData(2, Qt::Horizontal, "单价金额");
    itemlist_model->setHeaderData(3, Qt::Horizontal, "数量");



}

UserMainWindow::~UserMainWindow()
{
}

class UserOrderClient {
public:
    UserOrderClient(std::shared_ptr<Channel> channel)
        : stub_(UserOrder::NewStub(channel)) {}

    bool GetOrderListRpc(const UserId& request, OrderList& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->GetOrderList(&context, request, &reply);

        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed";
            return reply.return_result_();
        }
        else {
            return_message_ = to_string(status.error_code()) + ": " + status.error_message() + ", RPC failed";
            return false;
        }
    }

    bool GetSpecificOrderRpc(const OrderId& request, SpecificOrder& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->GetSpecificOrder(&context, request, &reply);
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

    bool UpdateOrderStateRpc(const UpdateOrderStateRequest& request, BaseReply& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->UpdateOrderState(&context, request, &reply);

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
    std::unique_ptr<UserOrder::Stub> stub_;
};


void UserMainWindow::CreateOrder()
{
    /*创建通信实例*/
    //userid_impl_.set_user_phone_("13512341234");
    UserCreateOrderWindow UserCreateOrderWindowImpl(userid_impl_.user_phone_());

    //UserCreateOrderWindowImpl.orderdetail_impl_.set_order_sender_id_(userid_impl_.user_phone_());

    //UserCreateOrderWindowImpl.user_phone_ = userid_impl_.user_phone_();

    /*进入该窗口*/
    UserCreateOrderWindowImpl.exec();

    GetOrderList();




}

void UserMainWindow::GetOrderList()
{
    /*rpc通信*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetOrderListRpc(userid_impl_, order_list_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "获取订单列表错误", QString::fromStdString(return_message_));
    }

    


    /*界面显示*/
    sender_model->setRowCount(order_list_impl_.order_sender_list_().size());
    for (int i = 0; i < order_list_impl_.order_sender_list_().size(); i++) {
        sender_model->setItem(i, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_id_())));
        sender_model->setItem(i, 1, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_sender_id_())));
        sender_model->setItem(i, 2, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_receiver_id_())));
        sender_model->setItem(i, 3, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_money_())));
        sender_model->setItem(i, 4, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_time_())));
        sender_model->setItem(i, 5, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_status_())));
    }
    

    /*QString::number(order_list_impl_.order_sender_list_().size());

    ui.textBrowser->setText(QString::number(order_list_impl_.order_sender_list_().size()));



    
    return;*/
    

    receiver_model->setRowCount(order_list_impl_.order_receiver_list_().size());
    for (int i = 0; i < order_list_impl_.order_receiver_list_().size(); i++) {
        receiver_model->setItem(i, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_id_())));
        receiver_model->setItem(i, 1, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_sender_id_())));
        receiver_model->setItem(i, 2, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_receiver_id_())));
        receiver_model->setItem(i, 3, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_money_())));
        receiver_model->setItem(i, 4, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_time_())));
        receiver_model->setItem(i, 5, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_status_())));
    }

    

    ui.tableView->setModel(sender_model);
    ui.tableView_2->setModel(receiver_model);

    return;
}

bool UserMainWindow::UpdateOrderState()
{
    /*rpc通信*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.UpdateOrderStateRpc(update_state_impl, basereply_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "确认收件错误", QString::fromStdString(return_message_));
    }
    GetOrderList();
    return res;
}

void UserMainWindow::ShowOrderDetail(const QModelIndex& index)
{
    if (index.model() == sender_model)
    {
        int i = index.row();
        detail_model->setItem(0, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_id_())));
        detail_model->setItem(1, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_sender_id_())));
        detail_model->setItem(2, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_receiver_id_())));
        detail_model->setItem(3, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_start_address_())));
        detail_model->setItem(4, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_end_address_())));
        detail_model->setItem(5, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_money_())));
        detail_model->setItem(6, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_time_())));
        detail_model->setItem(7, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_status_())));
        detail_model->setItem(8, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_sender_list_(i).order_description_())));
    }
    else
    {
        int i = index.row();
        detail_model->setItem(0, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_id_())));
        detail_model->setItem(1, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_sender_id_())));
        detail_model->setItem(2, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_receiver_id_())));
        detail_model->setItem(3, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_start_address_())));
        detail_model->setItem(4, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_end_address_())));
        detail_model->setItem(5, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_money_())));
        detail_model->setItem(6, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_time_())));
        detail_model->setItem(7, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_status_())));
        detail_model->setItem(8, 0, new QStandardItem(QString::fromStdString(order_list_impl_.order_receiver_list_(i).order_description_())));
    }
    ui.tableView_3->setModel(detail_model);

    return;
}

void UserMainWindow::ShowOrderItemList()
{
    /*界面显示*/
    itemlist_model->setRowCount(specific_order_impl_.item_list_().size());

    for (int i = 0; i < specific_order_impl_.item_list_().size(); i++) {
        itemlist_model->setItem(i, 0, new QStandardItem(QString::fromStdString(specific_order_impl_.item_list_(i).item_id_())));
        itemlist_model->setItem(i, 1, new QStandardItem(QString::fromStdString(specific_order_impl_.item_list_(i).item_name_())));
        itemlist_model->setItem(i, 2, new QStandardItem(QString::fromStdString(specific_order_impl_.item_list_(i).item_price_())));
        itemlist_model->setItem(i, 3, new QStandardItem(QString::number(specific_order_impl_.item_list_(i).item_number_())));
    }
    ui.tableView_5->setModel(itemlist_model);
    return;
}

void UserMainWindow::ShowOrderTransportList()
{
    /*界面显示*/
    transport_model->setRowCount(specific_order_impl_.transport_list_().size());

    for (int i = 0; i < specific_order_impl_.transport_list_().size(); i++) {
        transport_model->setItem(i, 0, new QStandardItem(QString::fromStdString(specific_order_impl_.transport_list_(i).transport_time_())));
        transport_model->setItem(i, 1, new QStandardItem(QString::fromStdString(specific_order_impl_.transport_list_(i).transport_description_())));
    }
    ui.tableView_4->setModel(transport_model);
    return;
}

//单击：显示某个订单信息，包括详细信息，货物列表，当前物流情况
void UserMainWindow::ClickedTable(const QModelIndex& index)
{
    orderid_impl_.set_order_id_(index.model()->index(index.row(), 0).data().toString().toStdString());

    

    //index.model()

    /*rpc*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetSpecificOrderRpc(orderid_impl_, specific_order_impl_, return_message_);

    if (res == true)//成功
    {
        //QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
    }
    else//失败，打印提示信息
    {
        QMessageBox::critical(nullptr, "获取订单信息错误", QString::fromStdString(return_message_));
    }

    

    /*show order detail*/
    ShowOrderDetail(index);



    /*show order item list */
    ShowOrderItemList();



    /*show transport_info*/
    ShowOrderTransportList();




}

/*双击：确认收货订单（暂定）*/
void UserMainWindow::DoubleClickedTable(const QModelIndex& index) {
    
    update_state_impl.set_order_id_(index.model()->index(index.row(), 0).data().toString().toStdString());
    update_state_impl.set_order_status_("确认收货");

    bool res = UpdateOrderState();

}
