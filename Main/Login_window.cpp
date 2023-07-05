#include "Login_window.h"
#include<qmovie.h>
#include"home.h"
Login_window::Login_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Login_window::~Login_window()
{}

void Login_window::button()
{
    if (ui.username->text() == "admin" && ui.password->text() == "123456") {
        home* home1 = new home();
        this->close();
        home1->show();
    }
    else {
        QMessageBox::warning(this, tr("µÇÂ¼Ê§°Ü"), tr("ÓÃ»§Ãû»òÃÜÂëÊäÈë´íÎó£¡"), QMessageBox::Ok);
        ui.username->clear();
        ui.password->clear();
        ui.username->setFocus();
    }
    
	
}
