#pragma once

#include <QMainWindow>
#include"Login_window.h"
#include"ui_Login_window.h"
#include<QMessageBox>
class Login_window : public QMainWindow
{
	Q_OBJECT

public:
	Login_window(QWidget *parent = nullptr);
	~Login_window();
private slots:
	void button();

private:
	Ui::Qt_ImageClass ui;
};
