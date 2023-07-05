#pragma once

#include <QMainWindow>
#include "ui_Noise.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QGraphicsScene>  
#include <QGraphicsView>               
#include <qfiledialog.h>               
#include <QLabel.h>                     
#include <qtimer.h>
#include <qimage.h>
#include<string>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp> 
#include <QGraphicsScene>
#include <QGraphicsView>
#include<iostream>
#include<vector>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;
class Noise : public QMainWindow
{
	Q_OBJECT

public:
	Noise(QWidget *parent = nullptr);
	~Noise();

private slots:
	void load_image();//º”‘ÿÕºœÒ
	void Pepper_noise();//Ω∑—Œ‘Î…˘
	void Gaussian_noise();//∏ﬂÀπ‘Î…˘
	void return_up();
private:
	Ui::NoiseClass ui;
	Mat image1;
	Mat image2;
	Mat noiseImg;
};
