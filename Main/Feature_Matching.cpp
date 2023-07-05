#include "Feature_Matching.h"
#include"home.h"
Feature_Matching::Feature_Matching(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Feature_Matching::~Feature_Matching()
{}

void Feature_Matching::load_image1()
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

void Feature_Matching::load_image2()
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
        image2 = imread(str);
        cvtColor(image2, image2, CV_BGR2RGB);
        cv::resize(image2, image2, Size(300, 200));
        QImage img2 = QImage((const unsigned char*)(image2.data), image2.cols, image2.rows, QImage::Format_RGB888);


        ui.label_2->setPixmap(QPixmap::fromImage(img2));
        img2 = img2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui.label_2->setScaledContents(true);
        ui.label_2->resize(img2.size());
        ui.label_2->show();
    }
}


void Feature_Matching::sift_feature_extraction()
{
    Ptr<SiftFeatureDetector> siftDetector = SiftFeatureDetector::create();

    siftDetector->detect(image1, keyPoints1);
    siftDetector->detect(image2, keyPoints2);
    drawKeypoints(image1, keyPoints1, image1, Scalar(0, 0, 255));
    drawKeypoints(image2, keyPoints2, image2, Scalar(0, 0, 255));

    QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
    ui.label->setPixmap(QPixmap::fromImage(img1));
    ui.label->resize(ui.label->pixmap()->size());
    QImage img2 = QImage((const unsigned char*)(image2.data), image2.cols, image2.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img2));
    ui.label_2->resize(ui.label_2->pixmap()->size());
    
}

void Feature_Matching::sift_feature_matching()
{
    Mat image1_desc, image2_desc;

    Ptr<SiftDescriptorExtractor> featureExtractor = SiftDescriptorExtractor::create();
    featureExtractor->compute(image1, keyPoints1, image1_desc);
    featureExtractor->compute(image2, keyPoints2, image2_desc);
    FlannBasedMatcher matcher;
    vector<Mat> image1_desc_collection(1, image1_desc);
    matcher.add(image1_desc_collection);
    matcher.train();

    vector<vector<DMatch>> matches;
    matcher.knnMatch(image2_desc, matches, 2);

    vector<DMatch> good_matches;
    for (unsigned int i = 0; i < matches.size(); i++) {
        if (matches[i][0].distance < 0.6 * matches[i][1].distance)
            good_matches.push_back(matches[i][0]);
    }

    Mat img_show;

    drawMatches(image2, keyPoints2, image1, keyPoints1, good_matches, img_show);
    QImage img = QImage((const unsigned char*)(img_show.data), img_show.cols, img_show.rows, QImage::Format_RGB888);
    ui.label->setPixmap(QPixmap::fromImage(img));
    ui.label->resize(ui.label->pixmap()->size());
    ui.label_2->hide();
    
   
}


void Feature_Matching::surf_feature_extraction()
{
    /*Ptr<SURF> detector = SURF::create();
    detector->detect(image1, keyPoints1);
    detector->detect(image2, keyPoints2);
    drawKeypoints(image1, keyPoints1, image1, Scalar(0, 0, 255));
    drawKeypoints(image2, keyPoints2, image2, Scalar(0, 0, 255));
    QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
     ui.label->setPixmap(QPixmap::fromImage(img1));
    ui.label->resize(ui.label->pixmap()->size());
    QImage img2 = QImage((const unsigned char*)(image2.data), image2.cols, image2.rows, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(img2));
    ui.label_2->resize(ui.label_2->pixmap()->size());*/
}


void Feature_Matching::surf_feature_matching()
{

}


void Feature_Matching::brief()
{
   /* Ptr<SiftFeatureDetector> siftDetector = SiftFeatureDetector::create();

    siftDetector->detect(image1, keyPoints1);
    siftDetector->detect(image2, keyPoints2);

    BriefDescriptorExtractor brief;
    Mat descriptors_1, descriptors_2;
    brief.compute(image1, keyPoints1, descriptors_1);
    brief.compute(image2, keyPoints2, descriptors_2);

    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> mathces;
    matcher.match(descriptors_1, descriptors_2, mathces);
    Mat img_show;
    drawMatches(image1, keyPoints1, image2, keyPoints2, mathces, img_show);

    QImage img = QImage((const unsigned char*)(img_show.data), img_show.cols, img_show.rows, QImage::Format_RGB888);
    ui.label->setPixmap(QPixmap::fromImage(img));
    ui.label->resize(ui.label->pixmap()->size());
    ui.label_2->hide();*/
    
}

void Feature_Matching::return_up()
{
	home* homed = new home();
	this->close();
	homed->show();
}