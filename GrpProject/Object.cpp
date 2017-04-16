#include "Object.h"

Object::Object()
{
	//set values for default constructor
	setType("Object");
	setColor(Scalar(0, 0, 0));

}

Object::Object(string name) {

	setType(name);

	if (name == "blue") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVminArea(Scalar(91, 213, 145));
		setHSVmaxArea(Scalar(143, 255, 255));
		setHSVmin(Scalar(93, 38, 134));
		setHSVmax(Scalar(119, 225, 206));

		//BGR value for Blue:
		setColor(Scalar(250, 0, 0));

	}
	if (name == "green") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVminArea(Scalar(47, 24, 162));
		setHSVmaxArea(Scalar(100, 255, 255));
		setHSVmin(Scalar(34, 50, 50));
		setHSVmax(Scalar(80, 220, 200));

		//BGR value for Green:
		setColor(Scalar(0, 250, 0));

	}
	if (name == "yellow") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVminArea(Scalar(20, 124, 123));
		setHSVmaxArea(Scalar(30, 255, 255));
		setHSVmin(Scalar(20, 124, 123));
		setHSVmax(Scalar(30, 255, 255));

		//BGR value for yellow:
		setColor(Scalar(0, 255, 255));

	}
	if (name == "red") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVminArea(Scalar(0, 100, 100));
		setHSVmaxArea(Scalar(10, 255, 255));
		setHSVmin(Scalar(160, 100, 100));
		setHSVmax(Scalar(179, 255, 255));

		//BGR value for Red:
		setColor(Scalar(0, 0, 250));

	}
}

Object::~Object(void)
{
}

int Object::getXPos() {

	return Object::xPos;

}

void Object::wait()
{
	waitKey(30);
}

void Object::setXPos(int x) {

	Object::xPos = x;

}

int Object::getYPos() {

	return Object::yPos;

}

void Object::setYPos(int y) {

	Object::yPos = y;

}

Scalar Object::getHSVmin() {

	return Object::HSVmin;

}
Scalar Object::getHSVmax() {

	return Object::HSVmax;
}

Scalar Object::getHSVminArea() {

	return Object::HSVminArea;

}
Scalar Object::getHSVmaxArea() {

	return Object::HSVmaxArea;
}

void Object::setHSVmin(Scalar min) {

	Object::HSVmin = min;
}


void Object::setHSVmax(Scalar max) {

	Object::HSVmax = max;
}

void Object::setHSVminArea(Scalar min) {

	Object::HSVminArea = min;
}


void Object::setHSVmaxArea(Scalar max) {

	Object::HSVmaxArea = max;
}

void Object::setArea(double Area)
{
	Object::area = Area;
}

double Object::getArea()
{
	return Object::area;
}
