#ifndef PROCESSING_H
#define PROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "image.h"

using namespace cv;
using namespace std;

class ImageProcess {
public:
	ImageProcess();
	ImageProcess(Mat &img_thresholded);
	int IndexOfBiggestContour();
	void GetData();
	Mat img_thresholded;

	vector<vector<Point>> GetApproxContour() { return contours_poly; }
	vector<vector<Point>> GetContours() { return contours; }
	vector<Vec4i> GetHierarchy() { return hierarchy; }

	vector<vector<Point>> GetHulls() { return hulls; }
	vector<vector<int>> GetHullsI() { return hullsI; }
	//vector<vector<Vec4i>> GetDefects() { return defects; }
	int GetNoOfDefects() { return noOfDefects; }
	vector<vector<Point>> GetFingersPoints() { return fingers_points; }
	vector<Rect> GetBoundingBox() { return boundRect; }

	float GetDistance(Point a, Point b);
	float GetAngle(Point s, Point f, Point e);
	float GetAngleXAxis(Point s, Point e);

private:
	vector<vector<Point>> contours;
	vector<vector<Point>> contours_poly;
	vector<Vec4i> hierarchy;
	vector<Rect> boundRect;

	vector<vector<Point>> hulls;
	vector<vector<int>> hullsI; //indices to contour points 
	vector<vector<Vec4i>> defects;
	vector<vector<Point>> fingers_points;

	int noOfDefects;

	void FilterDefects();
	void ExtractContour();
	void ProcessContours();

};

#endif // !PROCESSING_H