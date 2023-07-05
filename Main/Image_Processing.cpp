#include "Image_Processing.h"
#include"home.h"
Image_Processing::Image_Processing(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Image_Processing::~Image_Processing()
{}

Mat gray_to_level(Mat gray)//灰度直方图函数
{
	QVector<int> pixel(256, 0);

	for (int i = 0; i < gray.rows; i++)
		for (int j = 0; j < gray.cols; j++) {
			pixel[gray.at<uchar>(i, j)]++;
		}

	Mat gray_level;
	gray_level.create(350, 256, CV_8UC1);

	int max_rows = 0;
	for (int i = 0; i <= 255; i++) {
		if (pixel[i] > max_rows) {
			max_rows = pixel[i];
		}
	}

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 350; j++) {
			gray_level.at<uchar>(j, i) = 255;
		}
	}

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 350 - int(320. * float(pixel[i]) / float(max_rows)); j++) {
			gray_level.at<uchar>(j, i) = 0;
		}
	}

	return gray_level;

}


void Image_Processing::load_image1() //加载图像
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
void Image_Processing::image_rotate_45()//45图像旋转
{
	Mat rotated_image;
	double angle = 45;
	Point2f center((image1.cols - 1) / 2.0, (image1.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(image1, rotated_image, rotation_matix, image1.size());

	QImage img1 = QImage((const unsigned char*)(rotated_image.data), rotated_image.cols, rotated_image.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}



void Image_Processing::image_rotate_90()//90图像旋转
{
	Mat rotated_image;
	double angle = 90;
	Point2f center((image1.cols - 1) / 2.0, (image1.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(image1, rotated_image, rotation_matix, image1.size());

	QImage img1 = QImage((const unsigned char*)(rotated_image.data), rotated_image.cols, rotated_image.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Processing::image_rotate_180()//180图像旋转
{
	Mat rotated_image;
	double angle = 180;
	Point2f center((image1.cols - 1) / 2.0, (image1.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(image1, rotated_image, rotation_matix, image1.size());

	QImage img1 = QImage((const unsigned char*)(rotated_image.data), rotated_image.cols, rotated_image.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Processing::image_rotate_270()//270图像旋转
{
	Mat rotated_image;
	double angle = 270;
	Point2f center((image1.cols - 1) / 2.0, (image1.rows - 1) / 2.0);
	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(image1, rotated_image, rotation_matix, image1.size());

	QImage img1 = QImage((const unsigned char*)(rotated_image.data), rotated_image.cols, rotated_image.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}


void Image_Processing::Gaussian_smoothing()//高斯模糊
{
	Mat Gaussian_image;
	GaussianBlur(image1, Gaussian_image, cv::Size(5, 5), 3, 3);
	QImage img1 = QImage((const unsigned char*)(Gaussian_image.data), Gaussian_image.cols, Gaussian_image.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}


void Image_Processing::image_histogram()//图像直方图
{
	cvtColor(image1, grayImg, COLOR_BGR2GRAY);
	int histsize = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
	calcHist(&grayImg, 1, 0, Mat(), histogram, 1, &histsize, &histRanges, true, false);

	int bin_w = 512 / histsize;
	Mat histImage(300, 512, CV_8UC1, Scalar(0, 0, 0));

	normalize(histogram, histogram, 0, 300, NORM_MINMAX, -1, Mat());//归一化
	for (int i = 1; i < histsize; i++)
	{
		line(histImage, Point((i - 1) * bin_w, 300 - cvRound(histogram.at<float>(i - 1))),
			Point((i)*bin_w, 300 - cvRound(histogram.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("图像直方图", histImage);

	waitKey(0);
}
void Image_Processing::Histogram_equalization() //直方图均衡化
{
	
	
}
void Image_Processing::Gradient() //图像锐化
{
	Mat blur_img, usm;
	GaussianBlur(image1, blur_img, Size(0, 0), 25);
	addWeighted(image1, 1.5, blur_img, -0.5, 0, usm);

	QImage img1 = QImage((const unsigned char*)(usm.data), usm.cols, usm.rows, QImage::Format_Indexed8);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	img1 = img1.scaled(500, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Processing::Grayscale_histogram()//灰度直方图
{
	Mat gray;
	cvtColor(image1, gray, COLOR_BGR2GRAY);
	Mat hist;
	const int channels[1] = { 0 };
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };
	const int bins[1] = { 256 };
	calcHist(&image1, 1, channels, Mat(), hist, 1, bins, ranges);
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	for (int i = 1; i <= hist.rows; ++i) {
		rectangle(histImage, Point(width * (i - 1), hist_h - 1),
			Point(width * i - 1, hist_h - cvRound(hist.at<float>(i - 1) / 20)),
			Scalar(255, 255, 255), -1);
	}
	QImage img1 = QImage((const unsigned char*)(histImage.data), histImage.cols, histImage.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Processing::Grayscale() //灰度图
{
	grayImg.create(image1.rows, image1.cols, CV_8UC1);

	for (int i = 0; i < image1.rows; i++)
		for (int j = 0; j < image1.cols; j++) {
			grayImg.at<uchar>(i, j) = (int)0.11 * image1.at<Vec3b>(i, j)[0]
				+ 0.59 * image1.at<Vec3b>(i, j)[1]
				+ 0.3 * image1.at<Vec3b>(i, j)[2];
		}

	QImage img1 = QImage((const unsigned char*)(grayImg.data), grayImg.cols, grayImg.rows, QImage::Format_Indexed8);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
	
}
void Image_Processing::image_Filp_up()//上下翻转
{
	flip(image1, image1, 0);                                  
	QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}

void Image_Processing::image_Filp_left()//左右翻转
{
	flip(image1, image1, 4);                                 
	QImage img1 = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}


void Image_Processing::affine_transformation()//仿射变换
{
	Point2f srcTri[3], dstTri[3];
	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat dst, RGB;
	cvtColor(image1, RGB, CV_BGR2RGB);
	dst = Mat::zeros(RGB.rows, RGB.cols, RGB.type());
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(RGB.cols - 1, 0); 
	srcTri[2] = Point2f(0, RGB.rows - 1);
	dstTri[0] = Point2f(RGB.cols * 0.0, RGB.rows * 0.33);
	dstTri[1] = Point2f(RGB.cols * 0.85, RGB.rows * 0.25);
	dstTri[2] = Point2f(RGB.cols * 0.15, RGB.rows * 0.7);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(RGB, dst, warp_mat, RGB.size());
	QImage img1 = QImage((const unsigned char*)(dst.data), dst.cols, dst.rows, QImage::Format_RGB888);
	ui.label_2->setPixmap(QPixmap::fromImage(img1));
	ui.label_2->resize(ui.label->pixmap()->size());
}
void Image_Processing::return_image() //返回到主菜单
{
	home* home_menu = new home();
	this->close();
	home_menu->show();
}
