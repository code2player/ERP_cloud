#pragma execution_character_set("utf-8")  
#include "UserMainWindow.h"

UserMainWindow::UserMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(CreateOrder()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(GetOrderList()));



    /*�����б��һϵ�в���*/
    sender_model = new QStandardItemModel(ui.tableView);//��ʼ��
    receiver_model = new QStandardItemModel(ui.tableView_2);//��ʼ��
    detail_model = new QStandardItemModel(ui.tableView_3);//��ʼ��
    transport_model = new QStandardItemModel(ui.tableView_4);//��ʼ��
    itemlist_model = new QStandardItemModel(ui.tableView_5);//��ʼ��


    /*������*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭
    ui.tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭

    /*������˫�����¼�*/
    connect(ui.tableView, &QTableView::clicked, this, &UserMainWindow::ClickedTable);
    connect(ui.tableView, &QTableView::doubleClicked, this, &UserMainWindow::DoubleClickedTable);
    connect(ui.tableView_2, &QTableView::clicked, this, &UserMainWindow::ClickedTable);
    connect(ui.tableView_2, &QTableView::doubleClicked, this, &UserMainWindow::DoubleClickedTable);

    /*����sender�����б����ֶ���*/
    sender_model->setRowCount(0);
    sender_model->setColumnCount(6);
    sender_model->setHeaderData(0, Qt::Horizontal, "������");
    sender_model->setHeaderData(1, Qt::Horizontal, "�������绰");
    sender_model->setHeaderData(2, Qt::Horizontal, "�ջ����绰");
    sender_model->setHeaderData(3, Qt::Horizontal, "�������");
    sender_model->setHeaderData(4, Qt::Horizontal, "�µ�ʱ��");
    sender_model->setHeaderData(5, Qt::Horizontal, "����״̬");

    
    /*����receiver�����б����ֶ���*/
    receiver_model->setRowCount(0);
    receiver_model->setColumnCount(6);
    receiver_model->setHeaderData(0, Qt::Horizontal, "������");
    receiver_model->setHeaderData(1, Qt::Horizontal, "�������绰");
    receiver_model->setHeaderData(2, Qt::Horizontal, "�ջ����绰");
    receiver_model->setHeaderData(3, Qt::Horizontal, "�������");
    receiver_model->setHeaderData(4, Qt::Horizontal, "�µ�ʱ��");
    receiver_model->setHeaderData(5, Qt::Horizontal, "����״̬");


    /*����detail���ֶ�����vertical��*/
    detail_model->setRowCount(9);
    detail_model->setColumnCount(1);
    detail_model->setHeaderData(0, Qt::Vertical, "������");
    detail_model->setHeaderData(1, Qt::Vertical, "�������绰");
    detail_model->setHeaderData(2, Qt::Vertical, "�ջ����绰");
    detail_model->setHeaderData(3, Qt::Vertical, "��������ַ");
    detail_model->setHeaderData(4, Qt::Vertical, "�ջ�����ַ");
    detail_model->setHeaderData(5, Qt::Vertical, "�������");
    detail_model->setHeaderData(6, Qt::Vertical, "�µ�ʱ��");
    detail_model->setHeaderData(7, Qt::Vertical, "����״̬");
    detail_model->setHeaderData(8, Qt::Vertical, "������ע");


    /*����transport�б����ֶ���*/
    transport_model->setRowCount(0);
    transport_model->setColumnCount(2);
    transport_model->setHeaderData(0, Qt::Horizontal, "ʱ��");
    transport_model->setHeaderData(1, Qt::Horizontal, "����");


    /*����item�б����ֶ���*/
    itemlist_model->setRowCount(0);
    itemlist_model->setColumnCount(4);
    itemlist_model->setHeaderData(0, Qt::Horizontal, "�����");
    itemlist_model->setHeaderData(1, Qt::Horizontal, "������");
    itemlist_model->setHeaderData(2, Qt::Horizontal, "���۽��");
    itemlist_model->setHeaderData(3, Qt::Horizontal, "����");



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

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->GetOrderList(&context, request, &reply);

        /*���ͨ�ţ�����*/
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

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->GetSpecificOrder(&context, request, &reply);
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

    bool UpdateOrderStateRpc(const UpdateOrderStateRequest& request, BaseReply& reply, std::string& return_message_) {
        ClientContext context;

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->UpdateOrderState(&context, request, &reply);

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
    std::unique_ptr<UserOrder::Stub> stub_;
};


void UserMainWindow::CreateOrder()
{
    /*����ͨ��ʵ��*/
    //userid_impl_.set_user_phone_("13512341234");
    UserCreateOrderWindow UserCreateOrderWindowImpl(userid_impl_.user_phone_());

    //UserCreateOrderWindowImpl.orderdetail_impl_.set_order_sender_id_(userid_impl_.user_phone_());

    //UserCreateOrderWindowImpl.user_phone_ = userid_impl_.user_phone_();

    /*����ô���*/
    UserCreateOrderWindowImpl.exec();

    GetOrderList();




}

void UserMainWindow::GetOrderList()
{
    /*rpcͨ��*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetOrderListRpc(userid_impl_, order_list_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "��ȡ�����б����", QString::fromStdString(return_message_));
    }

    


    /*������ʾ*/
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
    /*rpcͨ��*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.UpdateOrderStateRpc(update_state_impl, basereply_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "ȷ���ռ�����", QString::fromStdString(return_message_));
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
    /*������ʾ*/
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
    /*������ʾ*/
    transport_model->setRowCount(specific_order_impl_.transport_list_().size());

    for (int i = 0; i < specific_order_impl_.transport_list_().size(); i++) {
        transport_model->setItem(i, 0, new QStandardItem(QString::fromStdString(specific_order_impl_.transport_list_(i).transport_time_())));
        transport_model->setItem(i, 1, new QStandardItem(QString::fromStdString(specific_order_impl_.transport_list_(i).transport_description_())));
    }
    ui.tableView_4->setModel(transport_model);
    return;
}

//��������ʾĳ��������Ϣ��������ϸ��Ϣ�������б���ǰ�������
void UserMainWindow::ClickedTable(const QModelIndex& index)
{
    orderid_impl_.set_order_id_(index.model()->index(index.row(), 0).data().toString().toStdString());

    

    //index.model()

    /*rpc*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetSpecificOrderRpc(orderid_impl_, specific_order_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "��ȡ������Ϣ����", QString::fromStdString(return_message_));
    }

    

    /*show order detail*/
    ShowOrderDetail(index);



    /*show order item list */
    ShowOrderItemList();



    /*show transport_info*/
    ShowOrderTransportList();




}

/*˫����ȷ���ջ��������ݶ���*/
void UserMainWindow::DoubleClickedTable(const QModelIndex& index) {
    
    update_state_impl.set_order_id_(index.model()->index(index.row(), 0).data().toString().toStdString());
    update_state_impl.set_order_status_("ȷ���ջ�");

    bool res = UpdateOrderState();

}
