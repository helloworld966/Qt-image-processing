#pragma once

#include <QMainWindow>
#include "ui_Image_Processing.h"
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include"home.h"
class Image_Processing : public QMainWindow
{
	Q_OBJECT

public:
	Image_Processing(QWidget *parent = nullptr);
	~Image_Processing();
	int isGray = 0;
	Mat grayImg, grayImg2;
private slots:
	void load_image1();//加载图像
	void Gradient(); //梯度锐化
	void Grayscale_histogram();//灰度直方图
	void Grayscale();//灰度图
	void image_Filp_up();//上下翻转
	void image_Filp_left();//左右翻转
	void image_rotate_45();//45°图像旋转
	void image_rotate_90();//90°图像旋转
	void image_rotate_180();//180°图像旋转
	void image_rotate_270();//270°图像旋转
	void affine_transformation();//仿射变换
	void Gaussian_smoothing();//高斯平滑
	void image_histogram();//图像直方图
	void Histogram_equalization();//直方图均衡化
	void return_image(); //返回到上一级
private:
	Ui::Image_ProcessingClass ui;
	Mat image1;
	Mat image2;
	Mat histogram;
	QLabel* label;
	QLabel* label2;
	
};
