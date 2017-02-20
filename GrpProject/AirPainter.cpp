
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <Windows.h>
#include <mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from webcam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 170;
	int iHighH = 179;

	int iLowS = 150;
	int iHighS = 255;

	int iLowV = 60;
	int iHighV = 255;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastXr = -1;
	int iLastYr = -1;
	int iLastXb = -1;
	int iLastYb = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;
	
	cout << imgTmp.rows<< endl;

	int playRedFlag = 0;
	int playBlueFlag = 0;
	//cameraFeed.copyTo(test);
	//test.setTo(Scalar(0, 0, 0));

	while (true)
	{
		Mat imgOriginal;
		Mat imgLinestest = Mat::zeros(imgTmp.size(), CV_8UC3);
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat red;
		Mat blue;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), red); //Threshold red
		inRange(imgHSV, Scalar(110, 150, 150), Scalar(130, 255, 255), blue); //Threshold blue

																			 //morphological opening (removes small objects from the foreground)
		erode(red, red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(red, red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(red, red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(red, red, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		
		//Calculate the moments of the thresholded image
		Moments oMomentsRed = moments(red);

		double dM01Red = oMomentsRed.m01;
		double dM10Red = oMomentsRed.m10;
		double dAreaRed = oMomentsRed.m00;

		//moments for blue
		Moments oMomentsBlue = moments(blue);

		double dM01Blue = oMomentsBlue.m01;
		double dM10Blue = oMomentsBlue.m10;
		double dAreaBlue = oMomentsBlue.m00;

		int posX, posY;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dAreaRed > 10000)
		{

			//calculate the position of the ball
			posX = dM10Red / dAreaRed;
			posY = dM01Red / dAreaRed;

			if (iLastXr >= 0 && iLastYr >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastXr, iLastYr), Scalar(0, 0, 255), 3);
			}

			iLastXr = posX;
			iLastYr = posY;
		}

		if (dAreaBlue > 10000)
		{

			//calculate the position of the ball
			posX = dM10Blue / dAreaBlue;
			posY = dM01Blue / dAreaBlue;

			if (iLastXb >= 0 && iLastYb >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a blue line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(posX, posY), Scalar(255, 0, 0), 10);
				line(imgLinestest, Point(posX, posY), Point(posX, posY), Scalar(255, 0, 0), 10);
			}

			iLastXb = posX;
			iLastYb = posY;
		}


		imshow("Thresholded Image Blue", blue);
		imshow("Thresholded Image Red", red); //show the thresholded image
											  //imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgLinestest); //show the original image
		imshow("ImageLines", imgLines);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}