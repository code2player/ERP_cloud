#pragma execution_character_set("utf-8")  
#include "LogSystem.h"
#include <QtWidgets/QApplication>


#include "StartPage.h"
#include "RegisterWindow.h"
#include "LoginWindow.h"
#include "UserMainWindow.h"
#include "StationerMainWindow.h"
#include "AdminMainWindow.h"


#include <QCoreApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{

	QTextCodec* codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
	QTextCodec::setCodecForLocale(codec);

	QApplication a(argc, argv);
	//LogSystem w;
	int identity = -1;
	std::string return_phone;

	while (1) {
		SysStartPage StartPageImpl;
		StartPageImpl.state_code = 0;

		if (StartPageImpl.exec() == QDialog::Accepted) {	// 如果符合登录条件，login执行后，必返回QDialog::Accepted
			if (StartPageImpl.state_code >= 1 && StartPageImpl.state_code <= 3) { // register
				RegisterWindow ChildImpl;
				ChildImpl.state_code = StartPageImpl.state_code - 1;
				ChildImpl.exec();
			}
			else { // login
				LoginWindow ChildImpl;
				ChildImpl.state_code = StartPageImpl.state_code - 4;
				//ChildImpl.return_phone = "11133334444";
				if (ChildImpl.exec() == QDialog::Accepted) {
					return_phone = ChildImpl.return_phone;
					identity = StartPageImpl.state_code - 4;
					break;
				}
			}
		}
		else
		{
			return -1;
		}
	}

	if (identity == 0)
	{
		UserMainWindow UserMainWindowImpl;
		UserMainWindowImpl.userid_impl_.set_user_phone_(return_phone);
		UserMainWindowImpl.show();
		return a.exec();//必须放在内部
	}
	else if (identity == 1) {
		

		StationerMainWindow StationerMainWindowImpl;
		StationerMainWindowImpl.userid_impl_.set_stationer_id_(return_phone);
		StationerMainWindowImpl.GetStationerInfo();
		StationerMainWindowImpl.show();
		return a.exec();//必须放在内部
	}
	else if (identity == 2) {
		AdminMainWindow AdminMainWindowImpl;
		AdminMainWindowImpl.admin_id_impl_.set_admin_id_(return_phone);
		AdminMainWindowImpl.show();
		return a.exec();//必须放在内部
	}
	/*else {
		return -1;
	}*/


	//return -1;

	//w.show();
	return a.exec();
}
