#pragma once

#include <QMainWindow>
#include "ui_Edge_Detection.h"
#include"home.h"
class Edge_Detection : public QMainWindow
{
	Q_OBJECT

public:
	Edge_Detection(QWidget *parent = nullptr);
	~Edge_Detection();
private slots:
	void load_image();
	void sobel_image();
	void canny_image();
	void prewitt_image();
	void laplace_image();
	void return_up();
	
private:
	Ui::Edge_DetectionClass ui;
	Mat image1,image2;
	Mat grayImg, gray2Img;
	Mat dst, dst1, dst2, dst3, dst4;
	QImage Qtemp, Qtemp2;
	


};
