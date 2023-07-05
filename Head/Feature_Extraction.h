#pragma once

#include <QMainWindow>
#include "ui_Feature_Extraction.h"
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
#include<opencv2/features2d/nonfree.hpp>

using namespace cv;
using namespace std;
class Feature_Extraction : public QMainWindow
{
	Q_OBJECT

public:
	Feature_Extraction(QWidget *parent = nullptr);
	~Feature_Extraction();
private slots:
	void load_image();
	void surf();
	void ORB();
	void Harris();
	void Fast();
	void return_up();
private:
	Ui::Feature_ExtractionClass ui;
	Mat image1, image2,gray;
	vector<KeyPoint>keyPoints;
};
