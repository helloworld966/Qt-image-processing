#include "Noise.h"
#include"home.h"
Noise::Noise(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Noise::~Noise()
{}
Mat addSaltNoise(const Mat srcImage, int n)
{
    Mat dstImage = srcImage.clone();
    for (int k = 0; k < n; k++)
    {
        //���ȡֵ����
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        //ͼ��ͨ���ж�
        if (dstImage.channels() == 1)
        {
            dstImage.at<uchar>(i, j) = 255;		//������
        }
        else
        {
            dstImage.at<Vec3b>(i, j)[0] = 255;
            dstImage.at<Vec3b>(i, j)[1] = 255;
            dstImage.at<Vec3b>(i, j)[2] = 255;
        }
    }
    for (int k = 0; k < n; k++)
    {
        //���ȡֵ����
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        //ͼ��ͨ���ж�
        if (dstImage.channels() == 1)
        {
            dstImage.at<uchar>(i, j) = 0;		//������
        }
        else
        {
            dstImage.at<Vec3b>(i, j)[0] = 0;
            dstImage.at<Vec3b>(i, j)[1] = 0;
            dstImage.at<Vec3b>(i, j)[2] = 0;
        }
    }
    return dstImage;
}

double generateGaussianNoise(double mu, double sigma)
{
    //����Сֵ
    const double epsilon = std::numeric_limits<double>::min();
    static double z0, z1;
    static bool flag = false;
    flag = !flag;
    //flagΪ�ٹ����˹�������X
    if (!flag)
        return z1 * sigma + mu;
    double u1, u2;
    //�����������
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    } while (u1 <= epsilon);
    //flagΪ�湹���˹�������
    z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
    return z0 * sigma + mu;
}

Mat addGaussianNoise(Mat& srcImag)
{
    Mat dstImage = srcImag.clone();
    for (int i = 0; i < dstImage.rows; i++)
    {
        for (int j = 0; j < dstImage.cols; j++)
        {
            //��Ӹ�˹����
            dstImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[0] + generateGaussianNoise(2, 0.8) * 32);
            dstImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[1] + generateGaussianNoise(2, 0.8) * 32);
            dstImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[2] + generateGaussianNoise(2, 0.8) * 32);
        }
    }
    return dstImage;
}

void Noise::load_image()
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
        QImage img = QImage((const unsigned char*)(image1.data), image1.cols, image1.rows, QImage::Format_RGB888);

        
        ui.label->setPixmap(QPixmap::fromImage(img));
        img = img.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui.label->setScaledContents(true);
        ui.label->resize(img.size());
        ui.label->show();
    }
}

void Noise::Pepper_noise() //��������
{
    Mat salt;
    Mat temp;
    salt.create(image1.rows, image1.cols, CV_8UC3);
    salt = addSaltNoise(image1, 800);
    QImage Qtemp2;
    cvtColor(salt, temp, CV_BGR2RGB);//BGR convert to RGB

    noiseImg = temp.clone();

    Qtemp2 = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
}
void Noise::Gaussian_noise()  //��˹����
{
    Mat salt;
    Mat temp;
    salt.create(image1.rows, image1.cols, CV_8UC3);
    salt = addGaussianNoise(image1);
    QImage Qtemp2;
    cvtColor(salt, temp, CV_BGR2RGB);//BGR convert to RGB
    noiseImg = temp.clone();

    Qtemp2 = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    ui.label_2->setPixmap(QPixmap::fromImage(Qtemp2));
    Qtemp2 = Qtemp2.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.label_2->setScaledContents(true);
    ui.label_2->resize(Qtemp2.size());
    ui.label_2->show();
}

void Noise::return_up()
{
	home* homed = new home();
	this->close();
	homed->show();
}