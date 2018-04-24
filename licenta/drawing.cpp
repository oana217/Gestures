#include "drawing.h"

#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Draw::Draw(ImageProcess &img_process) {
	this->img_process = img_process;
	drawing = Mat::zeros(img_process.img_thresholded.size(), CV_8UC3);
	gestures.resize(10);
	gestures.at(0) = "NO GESTURE";
	gestures.at(1) = "ROTATION - LEFT";
	gestures.at(2) = "ROTATION - RIGHT";
	gestures.at(3) = "FIST";
	gestures.at(4) = "CLAW";
	gestures.at(5) = "EXTENSION - CLOSED";
	gestures.at(6) = "ROTATION - UP";
	gestures.at(7) = "THUMBS UP";
	gestures.at(8) = "L SIGN";
	gestures.at(9) = "EXTENSION - PARTED";
	//gestureIndex = 0;
}

void Draw::DrawData() {
	int index = img_process.IndexOfBiggestContour();
	if (index > -1) {
		//draw biggest contour and its hull
		drawContours(drawing, img_process.GetContours(), index, Scalar(255, 255, 255), 2, 8, img_process.GetHierarchy(), 0, Point());
		drawContours(drawing, img_process.GetHulls(), index, Scalar(124, 100, 233), 2, 8, vector<Vec4i>(), 0, Point());

		//draw the bounding rectangle
		rectangle(drawing, img_process.GetBoundingBox()[index].tl(), img_process.GetBoundingBox()[index].br(), Scalar(178, 34, 34), 2, 8, 0);

		//draw finger points
		vector<vector<Point>> fingers_points = img_process.GetFingersPoints();
		for (int i = 0; i < fingers_points.size(); i++) {
			line(drawing, fingers_points[i][0], fingers_points[i][1], CV_RGB(0, 255, 0), 2); //0-ptStart, 1-ptFar, 2-ptEnd
			line(drawing, fingers_points[i][2], fingers_points[i][1], CV_RGB(0, 255, 0), 2);
			circle(drawing, fingers_points[i][0], 4, Scalar(100, 0, 255), 2);
			circle(drawing, fingers_points[i][1], 4, Scalar(255, 0, 100), 2);
		}
	}
}

void Draw::DrawGesture(int &gestureIndex) {
	//draw gesture
	Point pt(10, 300);
	putText(drawing, gestures[gestureIndex], pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
}

void Draw::SetGestureIndex(int &gi) {
	gestureIndex = gi;
}



