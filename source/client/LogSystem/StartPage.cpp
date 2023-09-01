#include "StartPage.h"

SysStartPage::SysStartPage(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


    connect(ui.pushButton,   SIGNAL(clicked()), this, SLOT(register_user()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(register_stationer()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(register_admin()));
    connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(login_user()));
    connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(login_stationer()));
    connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(login_admin()));
}

SysStartPage::~SysStartPage()
{
}


void SysStartPage::register_user() {
    state_code = 1;
    accept();
}
void SysStartPage::register_stationer() {
    state_code = 2;
    accept();
}
void SysStartPage::register_admin() {
    state_code = 3;
    accept();
}
void SysStartPage::login_user() {
    state_code = 4;
    accept();
}
void SysStartPage::login_stationer() {
    state_code = 5;
    accept();
}
void SysStartPage::login_admin() {
    state_code = 6;
    accept();
}


