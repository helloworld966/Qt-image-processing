#pragma once

#include <QMainWindow>
#include "ui_Feature_Matching.h"
#include"home.h"
//using namespace xfeatures2d;
class Feature_Matching : public QMainWindow
{
	Q_OBJECT

public:
	Feature_Matching(QWidget *parent = nullptr);
	~Feature_Matching();
	int t1, t2;
	double tkpt, tdes, tmatch_bf, tmatch_knn;
private slots:
	void load_image1();
	void load_image2();
	void sift_feature_extraction();
	void sift_feature_matching();
	void surf_feature_extraction();
	void surf_feature_matching();
	void brief();
	void return_up();

private:
	Ui::Feature_MatchingClass ui;
	Mat image1, image2;
	vector<KeyPoint>keyPoints1;
	vector<KeyPoint>keyPoints2;
};
