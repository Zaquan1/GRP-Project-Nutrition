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

		setHSVmin(Scalar(70, 128, 3));
		setHSVmax(Scalar(164, 225, 255));

		//BGR value for Blue:
		setColor(Scalar(250, 0, 0));

	}
	if (name == "green") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(47, 24, 162));
		setHSVmax(Scalar(100, 255, 255));

		//BGR value for Green:
		setColor(Scalar(0, 250, 0));

	}
	if (name == "yellow") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(20, 124, 123));
		setHSVmax(Scalar(30, 255, 255));

		//BGR value for yellow:
		setColor(Scalar(0, 255, 255));

	}
	if (name == "red") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(0, 100, 100));
		setHSVmax(Scalar(10, 255, 255));

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

void Object::setHSVmin(Scalar min) {

	Object::HSVmin = min;
}


void Object::setHSVmax(Scalar max) {

	Object::HSVmax = max;
}

void Object::setArea(double Area)
{
	Object::area = Area;
}

double Object::getArea()
{
	return Object::area;
}
