#pragma once
#include "Status.h"

class People
{
public:
	People(Status a, Status i, Status j);

	int getProtein();
	int getCarbs();
	int getFats();
	int getVitamins();
	int getVeggies();
	void status();

	string getAge();
	string getIllness();
	string getJob();

private:
	Status age;
	Status illness;
	Status job;

	int protein;
	int carbs;
	int fats;
	int vitamins;
	int veggies;

	void CalculateStatus();

};