#ifndef DRAWING_H
#define DRAWING_H

#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "processing.h"

using namespace cv;
using namespace std;

class Draw {
public:
	Draw(ImageProcess &img_process);
	void DrawData();
	void DrawGesture(int &gestureIndex);
	Mat GetDrawing() { return drawing; }
	vector<string> GetGestures() { return gestures; }
	void SetGestureIndex(int &gestureIndex);
private:
	ImageProcess img_process;
	int gestureIndex;
	vector<string> gestures;
	Mat drawing;

};

#endif //!DRAWING_H