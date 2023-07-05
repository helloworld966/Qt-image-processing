#include "Feature_Extraction.h"
#include"home.h"
Feature_Extraction::Feature_Extraction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Feature_Extraction::~Feature_Extraction()
{}


void Feature_Extraction::load_image()
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
void Feature_Extraction::surf()
{

}
void Feature_Extraction::ORB()
{
	Ptr<cv::ORB> orbDetector = ORB::create();
    orbDetector->detect(image1, keyPoints);
    drawKeypoints(image1, keyPoints, image1, Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img1));
    ui.label_2->resize(ui.label->pixmap()->size());
}
void Feature_Extraction::Harris()
{
    cvtColor(image1, gray, COLOR_BGR2GRAY);
    Mat harris;
    cornerHarris(gray, harris, 2, 3, 0.04);
    //归一化便于进行数值比较和结果显示
    Mat harrisn;
    normalize(harris, harrisn, 0, 255, NORM_MINMAX);
    //将图像的数据类型变成CV_8U
    convertScaleAbs(harrisn, harrisn);
    for (int row = 0; row < harrisn.rows; row++)
    {
        for (int col = 0; col < harrisn.cols; col++)
        {
            int R = harrisn.at<uchar>(row, col);
            if (R > 125)
            {
                KeyPoint keyPoint;
                keyPoint.pt.y = row;
                keyPoint.pt.x = col;
                keyPoints.push_back(keyPoint);
            }
        }
    }
    drawKeypoints(image1, keyPoints, image1);
    QImage img = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img));
    ui.label_2->resize(ui.label->pixmap()->size());
   
}
void Feature_Extraction::Fast()
{
    auto fast = FastFeatureDetector::create();
    fast->detect(image1, keyPoints, Mat());
    drawKeypoints(image1, keyPoints, image1, Scalar::all(-1), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    QImage img = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img));
    ui.label_2->resize(ui.label->pixmap()->size());
    
}
void Feature_Extraction::return_up()
{
	home* homed = new home();
	this->close();
	homed->show();
}