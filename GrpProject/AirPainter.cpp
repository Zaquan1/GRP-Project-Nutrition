//Written by  Kyle Hounslow 2013

// modified by: Ahmad Kaifi, Hassan Althobaiti

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//IN THE SOFTWARE.
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include "Object.h"
#include <chrono>


//default capture width and height
//640x480,1080x720,1920x1080
const int FRAME_WIDTH = 1080;
const int FRAME_HEIGHT = 720;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 1000;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 3;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

vector< vector<Point> > contours;
vector<Vec4i> hierarchy;

//The following for canny edge detec
Mat src;


string intToString(int number) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

void drawObject(vector<Object> theObjects, Mat &frame, vector< vector<Point> > contours, vector<Vec4i> hierarchy) {

	for (int i = 0; i<theObjects.size(); i++) {
		cv::drawContours(frame, contours, i, theObjects.at(i).getColor(), 3, 8, hierarchy);
		cv::circle(frame, cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()), 5, theObjects.at(i).getColor());
		cv::putText(
			frame,
			intToString(theObjects.at(i).getXPos()) + " , " + intToString(theObjects.at(i).getYPos()) + " , " + intToString(theObjects.at(i).getArea()),
			cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos() + 20),
			1,
			1,
			theObjects.at(i).getColor()
		);
		cv::putText(
			frame,
			theObjects.at(i).getType(),
			cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos() - 20),
			1,
			2,
			theObjects.at(i).getColor()
		);
	}
}

//temperory, for testting purpose
void drawLine(int x, int y, Object object, Mat &canvas)
{
	line(canvas, Point(x, y), Point(x, y), object.getColor(), 10);
}

void drawLine(vector<Object> theObjects, Mat &drawingCanvas, Mat &drawingCanvasTemp)
{
	for (int i = 0; i < theObjects.size(); i++) {
		if (!(theObjects.at(i).getXPos() > FRAME_WIDTH / 2) && !(theObjects.at(i).getYPos() > FRAME_HEIGHT / 2))
		{
			line(
				drawingCanvas,
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				theObjects.at(i).getColor(),
				10
			);
		}
		else
		{
			line(
				drawingCanvasTemp,
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				theObjects.at(i).getColor(),
				10
			);
		}
	}
}


void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);

	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}

void trackFilteredObject(Object theObject, Mat &threshold, Mat &cameraFeed, Mat &drawingCanvas, Mat &drawingCanvasTemp) {
	vector <Object> objects;
	//these two vectors needed for output of findContours
	GaussianBlur(threshold, threshold, cv::Size(9, 9), 2, 2);

	//imshow(theObject.getType (), threshold);

	//find contours of filtered image using openCV findContours function
	
	findContours(threshold, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0])
			{
				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area>MIN_OBJECT_AREA && area <MAX_OBJECT_AREA)
				{
					Object object;
					object.setXPos(moment.m10 / area);
					object.setYPos(moment.m01 / area);
					object.setArea(area);
					object.setType(theObject.getType());
					object.setColor(theObject.getColor());
					objects.push_back(object);
					objectFound = true;
				}
				else objectFound = false;
			}
			//let user know you found an object
			if (objectFound == true) {
				//draw object location on screen
				drawObject(objects, cameraFeed, contours, hierarchy);
				drawLine(objects, drawingCanvas, drawingCanvasTemp);
			}

		}
		else {
			putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
		}
	}
}

void backgroundFilter(Ptr<BackgroundSubtractor> &bg_model, Mat &mask, Mat &display)
{
	Mat foregroundImg;
	bg_model->apply(display, mask, true ? -1 : 0);

	// smooth the mask to reduce noise in image
	GaussianBlur(mask, mask, Size(11, 11), 3.5, 3.5);

	// threshold mask to saturate at black and white values
	threshold(mask, mask, 10, 255, THRESH_BINARY);
	foregroundImg = Scalar::all(0);
	// Copy source image to foreground image only in area with white mask
	display.copyTo(foregroundImg, mask);
	foregroundImg.copyTo(display);
}

void ColorManager(Mat &cameraFeed, Mat &HSV, Mat &threshold, Mat &drawingCanvas, Mat &drawingCanvasTemp, Object colorObject)
{
	cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
	inRange(HSV, colorObject.getHSVmin(), colorObject.getHSVmax(), threshold);
	morphOps(threshold);
	trackFilteredObject(colorObject, threshold, cameraFeed, drawingCanvas, drawingCanvasTemp);
}

void ColorArea(Mat &drawingCanvas, Object &color)
{
	Mat tmpHsv;
	Mat tmpThreshold;
	cvtColor(drawingCanvas, tmpHsv, COLOR_BGR2HSV);
	inRange(tmpHsv, color.getHSVmin(), color.getHSVmax(), tmpThreshold);
	Moments moment = moments(tmpThreshold);


}

int main(int argc, char* argv[])
{
	//if we would like to calibrate our filter values, set to true.
	cvNamedWindow("Original Image", CV_WINDOW_NORMAL);
	cvSetWindowProperty("Original Image", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	Mat threshold;
	Mat HSV;
	Mat test;
	Mat drawingCanvas;
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open(0);
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	capture.read(cameraFeed);
	drawingCanvas = Mat::zeros(cameraFeed.size(), CV_8UC3);

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop

	//create background filtering object
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

	// Create empy input img, foreground and background image and foreground mask.
	Mat foregroundMask;


	while (waitKey(30) != 27) {

		auto start = std::chrono::high_resolution_clock::now();
		//store image to matrix
		capture.read(cameraFeed);

		Mat drawingCanvasTemp = Mat::zeros(cameraFeed.size(), CV_8UC3);

		flip(cameraFeed, cameraFeed, 1);
		test.setTo(Scalar(0, 0, 0));

		src = cameraFeed;
		if (!src.data)
		{
			return -1;
		}

		if (foregroundMask.empty()) {
			foregroundMask.create(cameraFeed.size(), cameraFeed.type());
		}

		backgroundFilter(bg_model, foregroundMask, cameraFeed);


		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
		//create some temp fruit objects so that
		//we can use their member functions/information
		Object blue("blue"), yellow("yellow"), red("red"), green("green");

		ColorManager(cameraFeed, HSV, threshold, drawingCanvas, drawingCanvasTemp, yellow);
		ColorManager(cameraFeed, HSV, threshold, drawingCanvas, drawingCanvasTemp, green);
		ColorManager(cameraFeed, HSV, threshold, drawingCanvas, drawingCanvasTemp, blue);
		ColorManager(cameraFeed, HSV, threshold, drawingCanvas, drawingCanvasTemp, red);

		//for low cpu process, hide ColorManager and backgroundFilter and uncomment drawline for area checking
		/*
		drawLine(200, 200, blue, drawingCanvas);
		drawLine(300, 300, red, drawingCanvas);
		drawLine(400, 400, yellow, drawingCanvas);
		drawLine(500, 500, green, drawingCanvas);
		*/

		drawingCanvasTemp = drawingCanvas + drawingCanvasTemp;

		//show frames
		imshow("Original Image", cameraFeed);
		imshow("canvas", drawingCanvasTemp);

		auto finish = std::chrono::high_resolution_clock::now();
		double fps = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000; //fps in millisecond
		std::cout << ((1 / fps) * 1000) << "fps\n";

		//std::cout << wait << "\n";

	}
	return 0;
}
