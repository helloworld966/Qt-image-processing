#include "Edge_Detection.h"
#include"home.h"
Edge_Detection::Edge_Detection(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Edge_Detection::~Edge_Detection()
{}




void Edge_Detection::load_image()//加载图像
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
        QImage img = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);


        ui.label->setPixmap(QPixmap::fromImage(img));
        img = img.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui.label->setScaledContents(true);
        ui.label->resize(img.size());
        ui.label->show();
    }
}

void Edge_Detection::sobel_image()//sobel算子
{
    Mat matx;
    Mat maty;
    Mat matxy;
    QImage Qtemp, Qtemp2;
    //x方向梯度
    Sobel(image1, matx, CV_8U, 1, 0, 3);
    //y方向梯度
    Sobel(image1, maty, CV_8U, 0, 1, 3);
    //合并梯度
    addWeighted(matx, 0.8, maty, 0.8, 0, matxy);
    Qtemp2 = QImage((const unsigned char*)(matxy.data), matxy.cols, matxy.rows, matxy.step, QImage::Format_RGB888);
    
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
    
}
void Edge_Detection::canny_image()//canny算子
{
    image2 = image1.clone();
    cvtColor(image1, grayImg, COLOR_BGR2GRAY);
    Mat output, edge;

    blur(grayImg, grayImg, Size(3, 3));
    Canny(grayImg, edge, 150, 100, 3);

    output.create(image2.size(), image2.type());
    output = Scalar::all(0);
    image2.copyTo(output, edge);

    Qtemp = QImage((const uchar*)(output.data), output.cols, output.rows, output.cols * output.channels(), QImage::Format_Indexed8);
    ui.label_3->setPixmap(QPixmap::fromImage(Qtemp));
    Qtemp = Qtemp.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_3->setScaledContents(true);
    ui.label_3->resize(Qtemp.size());
    ui.label_3->show();

    Qtemp2 = QImage((const uchar*)(edge.data), edge.cols, edge.rows, edge.cols * edge.channels(), QImage::Format_Indexed8);
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
}
void Edge_Detection::prewitt_image()//prewitt算子
{
    Mat gradimg, gray2Img, f_x, f_y;
    
    gray2Img.create(grayImg.rows, grayImg.cols, CV_8UC1);
    gradimg.create(grayImg.rows, grayImg.cols, CV_8UC1);
    f_x.create(grayImg.rows, grayImg.cols, CV_8UC1);
    f_y.create(grayImg.rows, grayImg.cols, CV_8UC1);
    for (int i = 1; i < image1.rows - 1; i++)
    {
        for (int j = 1; j < image1.cols - 1; j++)
        {
            f_x.at<uchar>(i, j) = saturate_cast<uchar>(fabs(grayImg.at<uchar>(i + 1, j - 1) + grayImg.at<uchar>(i + 1, j) + grayImg.at<uchar>(i + 1, j + 1)
                - grayImg.at<uchar>(i - 1, j - 1) - grayImg.at<uchar>(i - 1, j) - grayImg.at<uchar>(i - 1, j + 1)));
            f_y.at<uchar>(i, j) = saturate_cast<uchar>(fabs(grayImg.at<uchar>(i - 1, j + 1) + grayImg.at<uchar>(i, j + 1) + grayImg.at<uchar>(i + 1, j + 1)
                - grayImg.at<uchar>(i - 1, j - 1) - grayImg.at<uchar>(i, j - 1) - grayImg.at<uchar>(i + 1, j - 1)));
            gradimg.at<uchar>(i, j) = max(f_x.at<uchar>(i, j), f_y.at<uchar>(i, j));
            gray2Img.at<uchar>(i, j) = saturate_cast<uchar>(grayImg.at<uchar>(i, j) - gradimg.at<uchar>(i, j));
        }
    }
    Qtemp = QImage((const uchar*)(gray2Img.data), gray2Img.cols, gray2Img.rows, gray2Img.cols * gray2Img.channels(), QImage::Format_Indexed8);
    ui.label_3->setPixmap(QPixmap::fromImage(Qtemp));
    Qtemp = Qtemp.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_3->setScaledContents(true);
    ui.label_3->resize(Qtemp.size());
    ui.label_3->show();

    Qtemp2 = QImage((const uchar*)(gradimg.data), gradimg.cols, gradimg.rows, gradimg.cols * gradimg.channels(), QImage::Format_Indexed8);
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
}

void Edge_Detection::laplace_image()//laplace算子
{
    Mat gradimg;
    gray2Img.create(grayImg.rows, grayImg.cols, CV_8UC1);
    grayImg.create(grayImg.rows, grayImg.cols, CV_8UC1);
    for (int i = 1; i < image1.rows - 1; i++)
    {
        for (int j = 1; j < image1.cols - 1; j++)
        {
            gradimg.at<uchar>(i, j) = saturate_cast<uchar>(-4 * grayImg.at<uchar>(i, j) + grayImg.at<uchar>(i + 1, j)
                + grayImg.at<uchar>(i, j + 1) + grayImg.at<uchar>(i - 1, j)
                + grayImg.at<uchar>(i, j - 1));
            gray2Img.at<uchar>(i, j) = saturate_cast<uchar>(5 * grayImg.at<uchar>(i, j) - grayImg.at<uchar>(i + 1, j)
                - grayImg.at<uchar>(i, j + 1) - grayImg.at<uchar>(i - 1, j)
                - grayImg.at<uchar>(i, j - 1));
        }
    }
    Qtemp = QImage((const uchar*)(gray2Img.data), gray2Img.cols, gray2Img.rows, gray2Img.cols * gray2Img.channels(), QImage::Format_Indexed8);
    ui.label_3->setPixmap(QPixmap::fromImage(Qtemp));
    Qtemp = Qtemp.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_3->setScaledContents(true);
    ui.label_3->resize(Qtemp.size());
    ui.label_3->show();

    Qtemp2 = QImage((const uchar*)(gradimg.data), gradimg.cols, gradimg.rows, gradimg.cols * gradimg.channels(), QImage::Format_Indexed8);
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
}


void Edge_Detection::return_up()//返回上一级
{
	home* homed = new home();
	this->close();
	homed->show();
}