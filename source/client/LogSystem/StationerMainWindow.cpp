#pragma execution_character_set("utf-8")  
#include "StationerMainWindow.h"

StationerMainWindow::StationerMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    /*�趨ui*/
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(InStation()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(OutStation()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(GetStationOrderList()));

    order_list_model = new QStandardItemModel(ui.tableView);//��ʼ��

    /*������*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ñ��ĵ�ԪΪֻ�����ԣ������ܱ༭


    /*����sender�����б����ֶ���*/
    order_list_model->setRowCount(0);
    order_list_model->setColumnCount(2);
    order_list_model->setHeaderData(0, Qt::Horizontal, "������");
    order_list_model->setHeaderData(1, Qt::Horizontal, "���ʱ��");



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
        /*rpcͨ��*/
        Status status = stub_->GetStationerInfo(&context, request, &reply);

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

    bool GetStationOrderListRpc(const StationId& request, SaveOrderList& reply, std::string& return_message_) {
        ClientContext context;

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->GetStationOrderList(&context, request, &reply);
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

    bool InStationRpc(const InStationRequest& request, BaseReply2& reply, std::string& return_message_) {
        ClientContext context;

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->InStation(&context, request, &reply);

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

    bool OutStationRpc(const OutStationRequest& request, BaseReply2& reply, std::string& return_message_) {
        ClientContext context;

        /*���÷�������*/

        /*rpcͨ��*/
        Status status = stub_->OutStation(&context, request, &reply);

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
    std::unique_ptr<StationerOrder::Stub> stub_;
};

void StationerMainWindow::GetStationerInfo()
{
    ui.lineEdit_3->setText(QString::fromStdString(userid_impl_.stationer_id_()));
    /*rpcͨ��*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetStationerInfoRpc(userid_impl_, stationer_info__impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "��ʼ���û���Ϣ����", QString::fromStdString(return_message_));
    }

}


void StationerMainWindow::GetStationOrderList()
{
    /*��ʼ��*/
    /*if (flagx == 0) {
        GetStationerInfo();
        flagx = 1;
    }*/
    

    stationid_impl_.set_station_id_(stationer_info__impl_.station_id_());
    /*rpcͨ��*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.GetStationOrderListRpc(stationid_impl_, save_order_list_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "��ȡ��ǰ�ֿⶩ���б����", QString::fromStdString(return_message_));
    }

    /*�����*/
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

    /*rpcͨ��*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.InStationRpc(in_station_request_impl_, basereply_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "������", QString::fromStdString(return_message_));
    }
    GetStationOrderList();
}

void StationerMainWindow::OutStation()
{
    out_station_request_impl_.set_stationer_id_(stationer_info__impl_.stationer_id_());
    out_station_request_impl_.set_station_id_(stationer_info__impl_.station_id_());
    out_station_request_impl_.set_order_id_(ui.lineEdit_2->text().toStdString());
    out_station_request_impl_.set_next_address_(ui.plainTextEdit->toPlainText().toStdString());

    /*rpcͨ��*/
    StationerOrderClient LoginClientImpl(grpc::CreateChannel(
        STATIONERORDER_IP + ":" + STATIONERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.OutStationRpc(out_station_request_impl_, basereply_impl_, return_message_);

    if (res == true)//�ɹ�
    {
        //QMessageBox::information(nullptr, "�ļ��ɹ�", QString::fromStdString(return_message_));
    }
    else//ʧ�ܣ���ӡ��ʾ��Ϣ
    {
        QMessageBox::critical(nullptr, "�������", QString::fromStdString(return_message_));
    }
    GetStationOrderList();
}

