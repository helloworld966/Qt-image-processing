#pragma once

#include <QMainWindow>
#include "ui_Image_Filter.h"
#include"home.h"
using namespace std;
using namespace cv;
class Image_Filter : public QMainWindow
{
	Q_OBJECT

public:
	Image_Filter(QWidget *parent = nullptr);
	~Image_Filter();
private slots:
	void load_image();//加载图像
	void Mean_filtering();//均值滤波
	void Median_filtering();//中值滤波
	void Gaussian_filtering();//高斯滤波
	void Bilateral_filtering();//双边滤波
	void corrosion();//腐蚀
	void expansion();//膨胀
	void return_up();//返回上一级

private:
	Ui::Image_FilterClass ui;
	Mat image1;
	Mat result;
	Mat output_image;
	Mat noiseImg;
	QLabel* label;

};
