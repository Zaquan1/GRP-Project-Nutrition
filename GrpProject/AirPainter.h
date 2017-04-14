#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Object.h"
#include <chrono>

class AirPainter
{
	
public:
	AirPainter(int frameWidth, int frameHeigth);
	AirPainter();

	void run();
	void ChangeDetect()
	{
		change = !change;
	};

	Mat getCanvas(){ return showCanvas; };

	string getColorArea(string color);
	void resetArea_Canvas();

private:
	
	Mat cameraFeed;
	Mat threshold;
	Mat HSV;
	Mat drawingCanvas;
	Mat showCanvas;

	Mat src;

	bool change;

	VideoCapture capture;

	Mat foregroundMask;
	Ptr<BackgroundSubtractor> bg_model;

	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	vector<Object> allColor;
	//640x480,1080x720,1920x1080
	int FRAME_HEIGHT;
	int FRAME_WIDTH;

	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area
	const int MIN_OBJECT_AREA = 1000;
	int MAX_OBJECT_AREA;

	bool drawable(int x, int y);

	void drawLine(vector<Object> theObjects, Mat &drawingCanvasTemp);
	void morphOps(Mat &thresh);
	void trackFilteredObject(Object theObject, Mat &drawingCanvasTemp);
	void backgroundFilter();
	void ColorManager(Mat &drawingCanvasTemp, Object colorObject);
	void TrackCircle(Object color, Mat &drawingCanvasTemp);
	void ColorArea(Object &color);
};