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
	void load_image1();//����ͼ��
	void Gradient(); //�ݶ���
	void Grayscale_histogram();//�Ҷ�ֱ��ͼ
	void Grayscale();//�Ҷ�ͼ
	void image_Filp_up();//���·�ת
	void image_Filp_left();//���ҷ�ת
	void image_rotate_45();//45��ͼ����ת
	void image_rotate_90();//90��ͼ����ת
	void image_rotate_180();//180��ͼ����ת
	void image_rotate_270();//270��ͼ����ת
	void affine_transformation();//����任
	void Gaussian_smoothing();//��˹ƽ��
	void image_histogram();//ͼ��ֱ��ͼ
	void Histogram_equalization();//ֱ��ͼ���⻯
	void return_image(); //���ص���һ��
private:
	Ui::Image_ProcessingClass ui;
	Mat image1;
	Mat image2;
	Mat histogram;
	QLabel* label;
	QLabel* label2;
	
};
