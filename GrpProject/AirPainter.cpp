
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <Windows.h>
#include "Color.h"

//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

using namespace cv;
using namespace std;

void ColorDetect(Mat HSVImage, Color &coloredObject, Mat &display)
{
	Mat temp;
	inRange(HSVImage, coloredObject.getHSVMin(), coloredObject.getHSVMax(), temp);
	blur(temp, temp, Size(10, 10));
	//blur(imgOriginal, imgOriginal, Size(20, 20));


	erode(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	erode(temp, temp, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	blur(temp, temp, Size(10, 10));

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

	if (dArea > 10000 && dArea < 360000)
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
	VideoCapture cap(0); //capture the video from webcam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	cout << imgTmp.rows << endl;

	Color red("Red", Scalar(170, 150, 60), Scalar(179, 255, 255), Scalar(0, 0, 255));
	Color blue("Blue", Scalar(110, 150, 150), Scalar(130, 255, 255), Scalar(255, 0, 0));
	Color green("Green", Scalar(34, 50, 50), Scalar(80, 220, 200), Scalar(0, 255, 0));
	Color yellow("Yellow", Scalar(20, 124, 123), Scalar(30, 256, 256), Scalar(0, 255, 255));

	std::vector<Color> allColor{ red,blue,green,yellow };


	while (true)
	{
		// read a new frame from video
		Mat imgOriginal;
		Mat imgLinestest = Mat::zeros(imgTmp.size(), CV_8UC3);
		bool bSuccess = cap.read(imgOriginal); 

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		for (int i = 0; i < allColor.size(); i++)
		{
			ColorDetect(imgHSV, allColor[i], imgLines);
		}
		//ColorDetect(imgHSV, &allColor[1], &imgLines);

		imshow("Original", imgOriginal); //show the original image
		imshow("ImageLines", imgLines);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}


	return 0;
}