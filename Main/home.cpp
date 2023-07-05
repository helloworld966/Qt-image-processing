#include "home.h"
#include"Image_Processing.h"
#include"Image_Filter.h"
#include"Noise.h"
#include"Edge_Detection.h"
#include"Feature_Extraction.h"
#include"Feature_Matching.h"
home::home(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

home::~home()
{}


void home::Image_processing() //1. ͼ��Ԥ����
{
	Image_Processing* processing = new Image_Processing();
	this->close();
	processing->show();
}
void home::Image_filter() //2. ͼ���˲�
{
	Image_Filter* filter = new Image_Filter();
	this->close();
	filter->show();
}
void home::Edge_detection() //3.��Ե���
{
	Edge_Detection* detection = new Edge_Detection();
	this->close();
	detection->show();
}
void home::noise() //4. ��������
{
	Noise* noised = new Noise();
	this->close();
	noised->show();
}
void home::Feature_extraction() //5. ������ȡ
{
	Feature_Extraction* extraction = new Feature_Extraction();
	this->close();
	extraction->show();
}
void home::Feature_matching() //6. ����ƥ��
{
	Feature_Matching* matching = new Feature_Matching();
	this->close();
	matching->show();
}