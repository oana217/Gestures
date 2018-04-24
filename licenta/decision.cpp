#include "decision.h"

#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Decision::Decision(ImageProcess &img_process) {
	this->img_process = img_process;
}

void Decision::DecideGesture() {
	gestureIndex = 0;
	int i = img_process.IndexOfBiggestContour();
	if (i > -1) {
		float box_ratio = ((float)img_process.GetBoundingBox()[i].height / (float)img_process.GetBoundingBox()[i].width);

		if (img_process.GetNoOfDefects() == 0) {
			float box_area = img_process.GetBoundingBox()[i].area();
			float contour_area = contourArea(img_process.GetHulls()[i]);
			float area_ratio = contour_area / box_area;

			//if area < 50% bounding box
			if (area_ratio < 0.5)
			{
				int y = img_process.GetBoundingBox()[i].tl().y; //these coordinates are for finding out the top right corner of the bounding box
				int x = img_process.GetBoundingBox()[i].br().x;

				double r_distance = pointPolygonTest(img_process.GetHulls()[i], Point(x, y), true);
				double l_distance = pointPolygonTest(img_process.GetHulls()[i], img_process.GetBoundingBox()[i].tl(), true);

				// if left corner is covered by hand
				if (l_distance > -5 && l_distance < 5)
				{
					gestureIndex = 1;
					//putText(drawing, "ROTATION - LEFT", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}

				// if right corner is covered by hand
				if (r_distance > -5 && l_distance < 5)
				{
					gestureIndex = 2;
					//putText(drawing, "ROTATION - RIGHT", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}
			}

			else
			{
				if (box_ratio > 0.9 && box_ratio < 1.3)
				{
					gestureIndex = 3;
					//putText(drawing, "FIST", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}

				if (box_ratio > 1.3 && box_ratio < 1.8)
				{
					gestureIndex = 4;
					//putText(drawing, "CLAW", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}

				if (box_ratio > 1.8 && box_ratio < 2.4)
				{
					gestureIndex = 5;
					//putText(drawing, "EXTENSION - CLOSED", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}

				if (box_ratio > 2.4 && box_ratio < 4.5)
				{
					gestureIndex = 6;
					//putText(drawing, "ROTATION - UP", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
				}
			}
		}

		if (img_process.GetNoOfDefects() == 1) {
			float angle = img_process.GetAngleXAxis(img_process.GetFingersPoints()[0][1], img_process.GetFingersPoints()[0][0]);
			if (angle > 75 && angle < 105)
			{
				gestureIndex = 7;
				//putText(drawing, "THUMBS UP", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
			}
			if (angle > 165 && angle < 195)
			{
				gestureIndex = 8;
				//putText(drawing, "L SIGN", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
			}
		}

		if (img_process.GetNoOfDefects() == 4) {
			gestureIndex = 9;
			//putText(drawing, "EXTENSION - PARTED", pt, FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2, 8);
		}
	}
}