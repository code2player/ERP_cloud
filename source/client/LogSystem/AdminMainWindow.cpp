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

    /*������ṹ*/
    itemlist_model = new QStandardItemModel(ui.tableView);//��ʼ��
    stationlist_model = new QStandardItemModel(ui.tableView_2);//��ʼ��
    orderlist_model = new QStandardItemModel(ui.tableView_3);//��ʼ��

    /*������*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭


    /*������Ʒ�б����ֶ���*/
    itemlist_model->setRowCount(0);
    itemlist_model->setColumnCount(4);
    itemlist_model->setHeaderData(0, Qt::Horizontal, "��Ʒid");
    itemlist_model->setHeaderData(1, Qt::Horizontal, "��Ʒ��");
    itemlist_model->setHeaderData(2, Qt::Horizontal, "��Ʒ�۸�");
    itemlist_model->setHeaderData(3, Qt::Horizontal, "��Ʒ��ע");

    /*����վ���б����ֶ���*/
    stationlist_model->setRowCount(0);
    stationlist_model->setColumnCount(4);
    stationlist_model->setHeaderData(0, Qt::Horizontal, "վ��id");
    stationlist_model->setHeaderData(1, Qt::Horizontal, "վ����");
    stationlist_model->setHeaderData(2, Qt::Horizontal, "վ���ַ");
    stationlist_model->setHeaderData(3, Qt::Horizontal, "վ�㱸ע");

    /*���ö����б����ֶ���*/
    orderlist_model->setRowCount(0);
    orderlist_model->setColumnCount(9);
    orderlist_model->setHeaderData(0, Qt::Horizontal, "������");
    orderlist_model->setHeaderData(1, Qt::Horizontal, "�������绰");
    orderlist_model->setHeaderData(2, Qt::Horizontal, "�ջ����绰");
    orderlist_model->setHeaderData(3, Qt::Horizontal, "��������ַ");
    orderlist_model->setHeaderData(4, Qt::Horizontal, "�ջ�����ַ");
    orderlist_model->setHeaderData(5, Qt::Horizontal, "�������");
    orderlist_model->setHeaderData(6, Qt::Horizontal, "�µ�ʱ��");
    orderlist_model->setHeaderData(7, Qt::Horizontal, "����״̬");
    orderlist_model->setHeaderData(8, Qt::Horizontal, "������ע");



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

        /*rpcͨ��*/
        Status status = stub_->GetAllItemList(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->GetAllStationList(&context, request, &reply);
        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->GetAllOrderList(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->AddItem(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->DelItem(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->AddStation(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->DelStation(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*rpcͨ��*/
        Status status = stub_->UpdateOrder(&context, request, &reply);

        /*���ͨ�ţ�����*/
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
    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllItemListRpc(admin_id_impl_, item_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "��ȡitem�б����", QString::fromStdString(return_message_));
    }

    /*������ʾ*/
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
    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllStationListRpc(admin_id_impl_, station_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "��ȡStation�б����", QString::fromStdString(return_message_));
    }

    /*������ʾ*/
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
    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.GetAllOrderListRpc(admin_id_impl_, order_list_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "��ȡOrder�б����", QString::fromStdString(return_message_));
    }

    /*������ʾ*/
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

    /*�������*/
    item_info_impl_.set_item_id_(ui.lineEdit->text().toStdString());
    item_info_impl_.set_item_name_(ui.lineEdit_2->text().toStdString());
    item_info_impl_.set_item_price_(ui.lineEdit_3->text().toStdString());
    item_info_impl_.set_item_description_(ui.plainTextEdit->toPlainText().toStdString());

    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddItemRpc(item_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "AddItem����", QString::fromStdString(return_message_));
    }
    GetAllItemList();
}

void AdminMainWindow::DelItem()
{
    /*clear*/
    item_info_impl_.Clear();

    /*�������*/
    item_info_impl_.set_item_id_(ui.lineEdit->text().toStdString());

    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.DelItemRpc(item_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "DelItem����", QString::fromStdString(return_message_));
    }
    GetAllItemList();
}

void AdminMainWindow::AddStation()
{
    /*clear*/
    station_info_impl_.Clear();

    /*�������*/
    station_info_impl_.set_station_id_(ui.lineEdit_4->text().toStdString());
    station_info_impl_.set_station_name_(ui.lineEdit_5->text().toStdString());
    station_info_impl_.set_station_position_(ui.lineEdit_6->text().toStdString());
    station_info_impl_.set_station_description_(ui.plainTextEdit_2->toPlainText().toStdString());

    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddStationRpc(station_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "AddStation����", QString::fromStdString(return_message_));
    }
    GetAllStationList();
}

void AdminMainWindow::DelStation()
{
    /*clear*/
    station_info_impl_.Clear();

    /*�������*/
    station_info_impl_.set_station_id_(ui.lineEdit_4->text().toStdString());

    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.AddStationRpc(station_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "DelStation����", QString::fromStdString(return_message_));
    }
    GetAllStationList();
}

void AdminMainWindow::UpdateOrder()
{
    /*clear*/
    order_info_impl_.Clear();

    /*�������*/
    order_info_impl_.set_order_id_(ui.lineEdit_8->text().toStdString());
    order_info_impl_.set_order_status_(ui.lineEdit_9->text().toStdString());
    order_info_impl_.set_order_start_address_(ui.plainTextEdit_3->toPlainText().toStdString());
    order_info_impl_.set_order_end_address_(ui.plainTextEdit_4->toPlainText().toStdString());
    order_info_impl_.set_order_description_(ui.plainTextEdit_5->toPlainText().toStdString());

    /*rpcͨ��*/
    AdminServiceClient ServiceClientImpl(grpc::CreateChannel(
        ADMINSERVER_IP + ":" + ADMINSERVER_PORT, grpc::InsecureChannelCredentials()));
    if (!ServiceClientImpl.UpdateOrderRpc(order_info_impl_, basereply_impl_, return_message_))
    {
        QMessageBox::critical(nullptr, "UpdateOrder����", QString::fromStdString(return_message_));
    }
    GetAllOrderList();
}



