#ifndef IMAGE_H
#define IMAGE_H
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class MyImage {
public:
	void SetCamera(VideoCapture cam);
	void Setup();
	Mat GetThresholdedImage() { return img_thresholded; }
	Mat GetConvertedImage() { return img_converted; }
	Mat GetROI() { return img_raw_roi; }
	//static Size getImgSize();
private:
	VideoCapture camera;
	Mat img_raw;
	Mat img_raw_roi;
	Mat img_converted;
	Mat img_thresholded;
	void ThresholdRawImage();
	bool ImageFromCamera();
	void ROI();

};

#endif // !IMAGE_H