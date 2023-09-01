#pragma execution_character_set("utf-8")  
#include "UserCreateOrderWindow.h"

UserCreateOrderWindow::UserCreateOrderWindow(const std::string passed_user_phone_, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(CreateOrder()));

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(AddItem()));

    ui.lineEdit->setText(QString::fromStdString(passed_user_phone_));
    
    /*订单列表的一系列操作*/
    itemlist_model = new QStandardItemModel(ui.tableView);//初始化

    /*设置项*/
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时为整行选中
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑

    /*单击、双击等事件*/
    connect(ui.tableView, &QTableView::doubleClicked, this, &UserCreateOrderWindow::DoubleClickedTable);

    /*设置订单列表列字段名*/
    itemlist_model->setRowCount(0);
    itemlist_model->setColumnCount(4);
    itemlist_model->setHeaderData(0, Qt::Horizontal, "货物号");
    itemlist_model->setHeaderData(1, Qt::Horizontal, "货物名");
    itemlist_model->setHeaderData(2, Qt::Horizontal, "单价金额");
    itemlist_model->setHeaderData(3, Qt::Horizontal, "数量");
}

UserCreateOrderWindow::~UserCreateOrderWindow()
{
}

/*
QStandardItem:点：零维
QList:线：一维
QStandardItemModel:面：二维
*/


/*同时增加model和orderdetail两个*/
void UserCreateOrderWindow::AddItem()
{


    orderdetail_impl_.set_order_end_address_(ui.plainTextEdit_2->toPlainText().toStdString());

    QList<QStandardItem*>    aItemList; //容器类
    //QStandardItem* aItem;

    aItemList << (new QStandardItem(ui.lineEdit_3->text()));   //创建Item并添加到容器
    aItemList << (new QStandardItem(ui.lineEdit_4->text()));
    aItemList << (new QStandardItem(ui.lineEdit_5->text()));
    aItemList << (new QStandardItem(QString::number(ui.spinBox->value())));
    

    itemlist_model->insertRow(itemlist_model->rowCount(), aItemList);


    ui.tableView->setModel(itemlist_model);
}

/*同时删除model和orderdetail两个*/
void UserCreateOrderWindow::DelItem(const QModelIndex& index)
{
    itemlist_model->removeRow(index.row());
    ui.tableView->setModel(itemlist_model);
}

/*双击，连接到删除*/
void UserCreateOrderWindow::DoubleClickedTable(const QModelIndex& index)
{
    DelItem(index);
}

class UserOrderClient {
public:
    UserOrderClient(std::shared_ptr<Channel> channel)
        : stub_(UserOrder::NewStub(channel)) {}

    bool CreateOrderRpc(const OrderDetail& request, BaseReply& reply, std::string& return_message_) {
        ClientContext context;

        /*设置发送内容*/

        /*rpc通信*/
        Status status = stub_->CreateOrder(&context, request, &reply);

        /*完成通信，返回*/
        if (status.ok()) {
            return_message_ = "RPC successed, "+ reply.return_message_();
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

void UserCreateOrderWindow::CreateOrder()
{
    /*clear*/
    orderdetail_impl_.Clear();

    /*数据填充*/
    orderdetail_impl_.set_order_sender_id_(ui.lineEdit->text().toStdString());

    orderdetail_impl_.set_order_receiver_id_(ui.lineEdit_2->text().toStdString());

    orderdetail_impl_.set_order_start_address_(ui.plainTextEdit->toPlainText().toStdString());

    orderdetail_impl_.set_order_end_address_(ui.plainTextEdit_2->toPlainText().toStdString());

    orderdetail_impl_.set_order_description_(ui.plainTextEdit_3->toPlainText().toStdString());

    double sum_money = 0;

    for (int i = 0; i < itemlist_model->rowCount(); i++) {
        OrderItem* temp_item_info_;
        temp_item_info_ = orderdetail_impl_.add_item_info_();
        temp_item_info_->set_item_id_(itemlist_model->item(i, 0)->text().toStdString());
        temp_item_info_->set_item_name_(itemlist_model->item(i, 1)->text().toStdString());
        temp_item_info_->set_item_price_(itemlist_model->item(i, 2)->text().toStdString());
        temp_item_info_->set_item_number_(itemlist_model->item(i, 3)->text().toInt());

        sum_money += itemlist_model->item(i, 2)->text().toDouble() * itemlist_model->item(i, 3)->text().toInt();
    }

    orderdetail_impl_.set_order_money_(std::to_string(sum_money));

    

    /*rpc通信*/
    UserOrderClient LoginClientImpl(grpc::CreateChannel(
        USERORDER_IP + ":" + USERORDER_PORT, grpc::InsecureChannelCredentials()));

    std::string return_message_;

    bool res = LoginClientImpl.CreateOrderRpc(orderdetail_impl_, basereply_impl_, return_message_);

    if (res == true)//成功
    {
        QMessageBox::information(nullptr, "寄件成功", QString::fromStdString(return_message_));
        accept();
    }
    else//失败，打印提示信息
	{
        QMessageBox::critical(nullptr, "错误", QString::fromStdString(return_message_));
	}
}
