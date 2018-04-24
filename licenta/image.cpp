#include "image.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void MyImage::SetCamera(VideoCapture cam) {
	camera = cam;
}

bool MyImage::ImageFromCamera()
{
	bool read = camera.read(img_raw);
	if (!read)
	{
		cout << "Could not read from camera." << endl;
		return false;
	}
}

void MyImage::ROI()
{
	Rect rect = Rect(img_raw.size().width / 4.7, img_raw.size().height / 15, img_raw.size().height / 1.5, img_raw.size().width / 2);
	img_raw_roi = img_raw(rect);
}

void MyImage::Setup() {
	ImageFromCamera();
	ROI();
	ThresholdRawImage();
}
void MyImage::ThresholdRawImage()
{
	blur(img_raw_roi, img_raw_roi, Size(3, 3));

	//convert and threshold image
	cvtColor(img_raw_roi, img_converted, COLOR_BGR2YCrCb);
	//cvtColor(img_raw_roi, img_converted, CV_BGR2HSV);

	//YCrCb skin
	inRange(img_converted, Scalar(80, 133, 77), Scalar(179, 173, 127), img_thresholded);
	//inRange(img_converted, Scalar(0, 10, 60), Scalar(20, 150, 255), img_thresholded);


	//morphological opening (remove small objects from the foreground)
	erode(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
}

/*Size MyImage::getImgSize() {
return img_raw_roi.size();
}*/