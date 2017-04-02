#include "People.h"

People::People(Status a, Status i, Status j) :age(a), illness(i), job(j)
{
	CalculateStatus();
}

void People::CalculateStatus()
{
	int mix = 100;
	protein = (age.getProtein() + illness.getProtein() + job.getProtein()) * mix;
	if (protein < 0)
		protein = 0;
	carbs = (age.getCarbs() + illness.getCarbs() + job.getCarbs()) * mix;
	if (carbs < 0)
		carbs = 0;
	fats = (age.getFats() + illness.getFats() + job.getFats()) * mix;
	if (fats < 0)
		fats = 0;
	vitamins = (age.getVitamins() + illness.getVitamins() + job.getVitamins()) * mix;
	if (vitamins < 0)
		vitamins = 0;
	veggies = (age.getVeggies() + illness.getVeggies() + job.getVeggies()) * mix;
	if (veggies < 0)
		veggies = 0;
}

string People::getAge() { return age.getStatusName(); }
string People::getIllness() { return illness.getStatusName(); }
string People::getJob() { return job.getStatusName(); }

void People::status()
{
	cout << "age: " << getAge();
	cout << "job: " << getJob();
	cout << "illness: " << getIllness();
	cout << "protein: " << getProtein() << endl;
	cout << "carbs: " << getCarbs() << endl;
	cout << "fats: " << getFats() << endl;
	cout << "vit: " << getVitamins() << endl;
	cout << "veggies: " << getVeggies() << endl;
}

int People::getProtein() { return protein; }
int People::getCarbs() { return carbs; }
int People::getFats() { return fats; }
int People::getVitamins() { return vitamins; }
int People::getVeggies() { return veggies; }