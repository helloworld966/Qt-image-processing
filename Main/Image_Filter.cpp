#include "Image_Filter.h"
#include"home.h"
Image_Filter::Image_Filter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Image_Filter::~Image_Filter()
{}


void Image_Filter::load_image() //����ͼ��
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
        tr("ѡ��ͼ��"),
        "",
        tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage* imgtest = new QImage;
        if (!(imgtest->load(filename)))                        //����ͼ��
        {
            QMessageBox::information(this,
                tr("��ͼ��ʧ��"),
                tr("��ͼ��ʧ��!"));
            delete imgtest;
            return;
        }
        string str = filename.toStdString();                  // ��filenameת��Ϊstring���ͣ�
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

void Image_Filter::Mean_filtering() //��ֵ�˲�
{

	//���þ�ֵ�˲�����blur()�����˲�
	blur(image1, result, Size(9, 9)); // 3x3�����
	QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Median_filtering() //��ֵ�˲�
{
    medianBlur(image1, result, 9);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Gaussian_filtering() //��˹�˲�
{
    GaussianBlur(image1, result, Size(5, 5), 0, 0);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::Bilateral_filtering()//˫���˲�
{
    //bilateralFilter(image1, result, 9, 9, 9);
    bilateralFilter(image1, result, 9, 200, 200);
    QImage img1 = QImage((const unsigned char*)(result.data), result.cols, result.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::corrosion() //��ʴ
{
    result = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(image1, output_image, result);
    QImage img1 = QImage((const unsigned char*)(output_image.data), output_image.cols, output_image.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}



void Image_Filter::expansion() //����
{
    result = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(image1, output_image, result);
    QImage img1 = QImage((const unsigned char*)(output_image.data), output_image.cols, output_image.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Filter::return_up() //������һ��
{
	home* home_menu = new home();
	this->close();
	home_menu->show();
}