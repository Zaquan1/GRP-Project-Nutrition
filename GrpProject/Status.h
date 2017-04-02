#pragma once
#include <string>
#include <iostream>
using namespace std;

class Status
{
public:
	Status();
	Status(string name);
	void setStatusName(string name);
	void setProtein(int p);
	void setCarbs(int c);
	void setFats(int f);
	void setVitamins(int vit);
	void setVeggies(int veg);

	string getStatusName();
	int getProtein();
	int getCarbs();
	int getFats();
	int getVitamins();
	int getVeggies();

private:
	string statusName;
	int protein;
	int carbs;
	int fats;
	int vitamins;
	int veggies;
};