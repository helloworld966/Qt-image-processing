#pragma once

#include <QMainWindow>
#include "ui_home.h"
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
class home : public QMainWindow
{
	Q_OBJECT

public:
	home(QWidget *parent = nullptr);
	~home();
	
private slots:
	void Image_processing(); //1. Í¼ÏñÔ¤´¦Àí
	void Image_filter(); //2. Í¼ÏñÂË²¨Æ÷
	void Edge_detection(); //3. ±ßÔµ¼ì²â
	void noise(); //4. ÔëÉù´¦Àí
	void Feature_extraction(); //5. ÌØÕ÷ÌáÈ¡
	void Feature_matching(); //6. ÌØÕ÷Æ¥Åä
private:
	Ui::homeClass ui;
	
};
