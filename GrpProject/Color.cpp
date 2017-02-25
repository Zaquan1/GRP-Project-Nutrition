#include "Color.h"

Color::Color()
{
	//setName("object");
	setColor(Scalar(0, 0, 0));
}

Color::Color(String Name, Scalar Min, Scalar Max, Scalar Color)
{
	setName(Name);
	setHSVMin(Min);
	setHSVMax(Max);
	setColor(Color);
	setposX(-1);
	setposY(-1);
}

void Color::setName(String Name)
{
	Color::name = Name;
}

void Color::setHSVMax(Scalar Max)
{
	Color::HSVMax = Max;
}

void Color::setHSVMin(Scalar Min)
{
	Color::HSVMin = Min;
}

void Color::setColor(Scalar Color)
{
	Color::color = Color;

}

void Color::setposX(int x)
{
	Color::posX = x;
}

void Color::setposY(int y)
{
	Color::posY = y;
}

Scalar Color::getHSVMax()
{
	return Color::HSVMax;
}

Scalar Color::getHSVMin()
{
	return Color::HSVMin;
}

Scalar Color::getColor()
{
	return Color::color;
}

int Color::getposX()
{
	return Color::posX;
}

int Color::getposY()
{
	return Color::posY;
}