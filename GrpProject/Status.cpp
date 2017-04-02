#include "Status.h"

Status::Status(): protein(0), carbs(0), fats(0), vitamins(0), veggies(0), statusName("none\n") {}

Status::Status(string name)
{
	setStatusName(name);
}

void Status::setStatusName(string name)
{
	statusName = name;
}
void Status::setProtein(int p)
{
	protein = p;
}
void Status::setCarbs(int c)
{
	carbs = c;
}
void Status::setFats(int f)
{
	fats = f;
}
void Status::setVitamins(int vit)
{
	vitamins = vit;
}
void Status::setVeggies(int veg)
{
	veggies = veg;
}

string Status::getStatusName() { return statusName; }
int Status::getProtein() { return protein; }
int Status::getCarbs() { return carbs; }
int Status::getFats() { return fats; }
int Status::getVitamins() { return vitamins; }
int Status::getVeggies() { return veggies; }