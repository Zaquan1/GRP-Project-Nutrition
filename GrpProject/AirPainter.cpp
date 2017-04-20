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

#include "AirPainter.h"
#define POSITIVE(n) ((n) < 0 ? 0 - (n) : (n))

/*
int lh = 179;
int hh = 225;
int ls = 225;
int hs = 91;
int lv = 213;
int hv = 143;
*/
//default constructor
AirPainter::AirPainter() :AirPainter(640, 480) {}

AirPainter::AirPainter(int frameWidth, int frameHeigth)
{
	FRAME_WIDTH = frameWidth;
	FRAME_HEIGHT = frameHeigth;
	MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 3;

	//change detection mode to circle detect
	change = true;

	capture.open(0);
	if (!capture.isOpened())
	{
		cout << "capture is not openned";
	}

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	capture.read(cameraFeed);

	//create empty mat with black background
	drawingCanvas = Mat::zeros(cameraFeed.size(), CV_8UC3);

	//create background filtering object
	bg_model = createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

	//create object to store area drawn by the user
	Object oriRed("red"), oriBlue("blue"), oriGreen("green"), oriYellow("yellow");
	
	allColor.push_back(oriRed);
	allColor.push_back(oriBlue);
	allColor.push_back(oriGreen);
	allColor.push_back(oriYellow);

	ignore = false;
}

//convert int to string
string intToString(int number) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

//set to only able to draw within a certain radius of circle
bool AirPainter::drawable(int x, int y)
{
	//cout << x << " " << y << endl;
	int centerx = 470;
	int centery = 362;
	int hypo = (int)sqrt(pow(POSITIVE(centerx - x), 2) + pow(POSITIVE(centery - y), 2));
	if (hypo > 284)
	{
		return false;
	}
	return true;
}

//draw the line on the canvas
void AirPainter::drawLine(vector<Object> theObjects, Mat &drawingCanvasTemp)
{
	for (int i = 0; i < theObjects.size(); i++) {
		//if (!(theObjects.at(i).getXPos() > FRAME_WIDTH / 2) && !(theObjects.at(i).getYPos() > FRAME_HEIGHT / 2))
		if (drawable(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()) && ignore)
		{
			line(
				drawingCanvas,
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				theObjects.at(i).getColor(),
				70
			);
		}
		else
		{
			line(
				drawingCanvasTemp,
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()),
				theObjects.at(i).getColor(),
				70
			);
		}
	}
}

//filter noise
void AirPainter::morphOps(Mat &thresh) {

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

//track all object with color
void AirPainter::trackFilteredObject(Object theObject, Mat &drawingCanvasTemp) {
	vector <Object> objects;
	GaussianBlur(threshold, threshold, cv::Size(9, 9), 2, 2);

	//find contours of filtered image using openCV findContours function
	findContours(threshold, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	//use moments method to find our filtered object
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0])
			{
				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//filtering object that is too small or too big
				if (area>MIN_OBJECT_AREA && area < MAX_OBJECT_AREA)
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
				drawLine(objects, drawingCanvasTemp);
			}

		}
		else {
			putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
		}
	}
}

//only track circle object
void AirPainter::TrackCircle(Object color, Mat &drawingCanvasTemp)
{
	vector <Object> objects;
	bool objectFound = false;
	vector<Vec3f> circles;
	// Apply the Hough Transform to find the circles
	HoughCircles(threshold, circles, CV_HOUGH_GRADIENT, 1, threshold.rows / 8, 100, 20, 40, 0);//threshold, circles, CV_HOUGH_GRADIENT, 1, threshold.rows / 8, 100, 20, 40, 0
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		Object object;
		object.setXPos(cvRound(circles[i][0]));
		object.setYPos(cvRound(circles[i][1]));
		object.setType(color.getType());
		object.setColor(color.getColor());
		objects.push_back(object);
		objectFound = true;

		// circle center
		circle(cameraFeed, center, 3, Scalar(0, 255, 0), -10, 8, 0);
		// circle outline
		circle(cameraFeed, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	if (objectFound)
	{
		drawLine(objects, drawingCanvasTemp);
	}
}

//filter all static background
void AirPainter::backgroundFilter()
{
	Mat foregroundImg;
	bg_model->apply(cameraFeed, foregroundMask, true ? -1 : 0);

	// smooth the mask to reduce noise in image
	GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);

	// threshold mask to saturate at black and white values
	cv::threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);
	foregroundImg = Scalar::all(0);

	// Copy source image to foreground image only in area with white mask
	cameraFeed.copyTo(foregroundImg, foregroundMask);
	foregroundImg.copyTo(cameraFeed);
}

//managing specific color to be filter and drawn
void AirPainter::ColorManager(Mat &drawingCanvasTemp, Object colorObject)
{
	cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
	inRange(HSV, colorObject.getHSVmin(), colorObject.getHSVmax(), threshold);
	morphOps(threshold);
	GaussianBlur(threshold, threshold, Size(9, 9), 2, 2);
	//imshow(colorObject.getType(), threshold);
	//convert between 2 different types of tracking
	if (change)
	{
		TrackCircle(colorObject, drawingCanvasTemp);
	}
	else
	{
		trackFilteredObject(colorObject, drawingCanvasTemp);
	}
}

//get the area where the user had drawn
void AirPainter::ColorArea(Object &color)
{
	Mat tmpHsv;
	Mat tmpThreshold;
	cvtColor(drawingCanvas, tmpHsv, COLOR_BGR2HSV);
	inRange(tmpHsv, color.getHSVminArea(), color.getHSVmaxArea(), tmpThreshold);
	morphOps(tmpThreshold);
	Moments moment = moments(tmpThreshold);
	//imshow(color.getType(), tmpThreshold);
	color.setArea((moment.m00/10000)/8290*100);
}

//get the area that the user had drawn
string AirPainter::getColorArea(string name)
{
	int area = 0;
	for (int i = 0; i < allColor.size(); i++)
	{
		if (allColor.at(i).getType() == name)
		{
			area = allColor.at(i).getArea();
		}
	}
	return intToString(area);
}

//reset canvas into blank and area information to 0
void AirPainter::resetArea_Canvas()
{
	for (int i = 0; i < allColor.size(); i++)
	{
		allColor.at(i).setArea(0);
	}
	drawingCanvas = Mat::zeros(cameraFeed.size(), CV_8UC3);
}

vector<Object> AirPainter::getAllColor()
{
	return allColor;
}


void AirPainter::run()
{
		capture >> cameraFeed;

		if (!cameraFeed.data)
		{
			cout << "error taking video" << endl;
			return;
		}
		else
		{
			Mat drawingCanvasTemp = Mat::zeros(cameraFeed.size(), CV_8UC3);

			flip(cameraFeed, cameraFeed, 1);
			src = cameraFeed;

			if (foregroundMask.empty()) {
				foregroundMask.create(cameraFeed.size(), cameraFeed.type());
			}

			backgroundFilter();


			//convert frame from BGR to HSV colorspace
			medianBlur(cameraFeed, cameraFeed, 3);
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

			Object blue("blue"), yellow("yellow"), red("red"), green("green");

			ColorManager(drawingCanvasTemp, yellow);
			ColorManager(drawingCanvasTemp, green);
			ColorManager(drawingCanvasTemp, blue);
			ColorManager(drawingCanvasTemp, red);

			
			//search for area drawn by the user
			for (int i = 0; i < allColor.size(); i++)
			{
				ColorArea(allColor[i]);
			}

			drawingCanvasTemp = drawingCanvas + drawingCanvasTemp;
			showCanvas = drawingCanvasTemp;
		
			//imshow("Original Image", cameraFeed);
		
		}

}
