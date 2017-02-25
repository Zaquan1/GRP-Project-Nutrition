#pragma once

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

class Color
{
public:
	Color();
	Color(String Name, Scalar Min, Scalar Max, Scalar Color);

	void setName(String Name);

	Scalar getHSVMin();
	Scalar getHSVMax();
	Scalar getColor();

	void setName(string Name);
	String getName()
	{
		return name;
	}

	float getArea();
	float setArea(float Area);

	void setHSVMin(Scalar Min);
	void setHSVMax(Scalar Max);
	void setColor(Scalar Color);

	int getposX();
	int getposY();
	void setposX(int x);
	void setposY(int y);

private:

	double area;
	String name;
	Scalar HSVMin, HSVMax, color;
	int posX, posY;



};