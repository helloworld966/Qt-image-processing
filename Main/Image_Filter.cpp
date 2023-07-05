#include "Image_Filter.h"
#include"home.h"
Image_Filter::Image_Filter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Image_Filter::~Image_Filter()
{}


void Image_Filter::load_image() //加载图像
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
        tr("选择图像"),
        "",
        tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage* imgtest = new QImage;
        if (!(imgtest->load(filename)))                        //加载图像
        {
            QMessageBox::information(this,
                tr("打开图像失败"),
                tr("打开图像失败!"));
            delete imgtest;
            return;
        }
        string str = filename.toStdString();                  // 将filename转变为string类型；
        image1 = imread(str);
        cvtColor(image1, image1, CV_BGR2RGB);
        cv::resize(image1, image1, Size(300, 200));
        QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);


        ui.label->setPixmap(QPixmap::fromImage(img1));
        img1 = img1.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui.label->setScaledContents(true);
        ui.label->resize(img1.size());
        ui.label->show();
	}
}

void Image_Filter::Mean_filtering() //均值滤波
{

	//调用均值滤波函数blur()进行滤波
	blur(image1, result, Size(9, 9)); // 3x3卷积核
	QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Median_filtering() //中值滤波
{
    medianBlur(image1, result, 9);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Gaussian_filtering() //高斯滤波
{
    GaussianBlur(image1, result, Size(5, 5), 0, 0);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Bilateral_filtering()//双边滤波
{
    //bilateralFilter(image1, result, 9, 9, 9);
    bilateralFilter(image1, result, 9, 200, 200);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::corrosion() //腐蚀
{
    result = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(image1, output_image, result);
    QImage img1 = QImage((const unsigned char*)(output_image.data), output_image.cols, output_image.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}



void Image_Filter::expansion() //膨胀
{
    result = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(image1, output_image, result);
    QImage img1 = QImage((const unsigned char*)(output_image.data), output_image.cols, output_image.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::return_up() //返回上一级
{
	home* home_menu = new home();
	this->close();
	home_menu->show();
}