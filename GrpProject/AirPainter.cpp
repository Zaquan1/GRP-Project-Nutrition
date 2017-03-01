
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <Windows.h>
#include "Color.h"

//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

using namespace cv;
using namespace std;

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

void ColorDetect(Mat HSVImage, Color &coloredObject, Mat &display)
{
	Mat temp;
	inRange(HSVImage, coloredObject.getHSVMin(), coloredObject.getHSVMax(), temp);

	erode(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	erode(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));

	dilate(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(8, 8)));
	dilate(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(8, 8)));

	imshow(coloredObject.getName(), temp);
	Moments oMoments = moments(temp);

	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	if (dArea == 0)
	{
		return;
	}

	int posX, posY;

	if (dArea > 10000)
	{
		//calculate the position of the ball
		posX = dM10 / dArea;
		posY = dM01 / dArea;
		if (posX >= 0 && posY >= 0 && coloredObject.getposX() >= 0 && coloredObject.getposY() >= 0)
		{
			line(display, Point(posX, posY), Point(coloredObject.getposX(), coloredObject.getposY()), coloredObject.getColor(), 10);
		}

		coloredObject.setposX(posX);
		coloredObject.setposY(posY);
	}
}


int main(int argc, char** argv)
{
	//capture the video from webcam
	VideoCapture cap(0);

	// if not success, exit program
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	Mat imgTmp;
	cap.read(imgTmp);

	// Init background substractor
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

	// Create empy input img, foreground and background image and foreground mask.
	Mat foregroundMask;


	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	Color red("Red", Scalar(170, 150, 60), Scalar(179, 255, 255), Scalar(0, 0, 255));
	Color blue("Blue", Scalar(110, 150, 150), Scalar(130, 255, 255), Scalar(255, 0, 0));
	Color green("Green", Scalar(34, 50, 50), Scalar(80, 220, 200), Scalar(0, 255, 0));
	Color yellow("Yellow", Scalar(20, 124, 123), Scalar(30, 256, 256), Scalar(0, 255, 255));

	std::vector<Color> allColor{ red,blue,green,yellow };

	while (true)
	{
		// read a new frame from video
		Mat imgOriginal;
		//Mat imgLinestest = Mat::zeros(imgTmp.size(), CV_8UC3);
		
		//if not success, break loop
		bool bSuccess = cap.read(imgOriginal);
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		if (foregroundMask.empty()) {
			foregroundMask.create(imgOriginal.size(), imgOriginal.type());
		}

		backgroundFilter(bg_model, foregroundMask, imgOriginal);

		//blur the frame

		GaussianBlur(imgOriginal, imgOriginal, cv::Size(9, 9), 2, 2);
		//Convert the captured frame from BGR to HSV
		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

		for (int i = 0; i < allColor.size(); i++)
		{
			ColorDetect(imgHSV, allColor[i], imgLines);
		}

		imshow("Original", imgOriginal);
		imshow("ImageLines", imgLines);

		//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}


	return 0;
}