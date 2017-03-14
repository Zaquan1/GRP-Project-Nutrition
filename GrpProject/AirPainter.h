#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include "Object.h"
#include <chrono>

class AirPainter
{
	
public:
	AirPainter(int frameWidth, int frameHeigth);
	AirPainter();

	void run();

	Mat getCanvas()
	{
		return showCanvas;
	};

private:
	
	Mat cameraFeed;
	Mat threshold;
	Mat HSV;
	Mat drawingCanvas;
	Mat showCanvas;

	Mat src;

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

	//temp for testing
	void drawLine(int x, int y, Object object, Mat &canvas);
	void drawObject(vector<Object> theObjects, Mat &frame, vector< vector<Point> > contours, vector<Vec4i> hierarchy);

	void drawLine(vector<Object> theObjects, Mat &drawingCanvasTemp);
	void morphOps(Mat &thresh);
	void trackFilteredObject(Object theObject, Mat &drawingCanvasTemp);
	void backgroundFilter();
	void ColorManager(Mat &drawingCanvasTemp, Object colorObject);
	void ColorArea(Object &color);
};