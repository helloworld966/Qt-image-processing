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
	void load_image();//����ͼ��
	void Mean_filtering();//��ֵ�˲�
	void Median_filtering();//��ֵ�˲�
	void Gaussian_filtering();//��˹�˲�
	void Bilateral_filtering();//˫���˲�
	void corrosion();//��ʴ
	void expansion();//����
	void return_up();//������һ��

private:
	Ui::Image_FilterClass ui;
	Mat image1;
	Mat result;
	Mat output_image;
	Mat noiseImg;
	QLabel* label;

};
