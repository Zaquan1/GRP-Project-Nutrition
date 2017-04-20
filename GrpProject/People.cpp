#include "People.h"

People::People()
{}

People::People(string n, string a, string g, string i, string j,
	int p, int c, int f, int fi)
{
	name = n;
	gender = g;
	age = a;
	illness = i;
	job = j;
	protein = p;
	carbs = c;
	fats = f;
	fibre = fi;
	CalculateStatus();
}

People::~People(void)
{}

void People::CalculateStatus()
{
	int total = protein + carbs + fats + fibre;
	carbs = intToPercentage(carbs, total);
	protein = intToPercentage(protein, total);
	fats = intToPercentage(fats, total);
	fibre = intToPercentage(fibre, total);
}

int People::intToPercentage(int a, int total)
{
	return a * 100 / total;
}

string People::getName() { return name; }
string People::getGender() { return gender; }
string People::getAge() { return age; }
string People::getIllness() { return illness; }
string People::getJob() { return job; }

void People::status()
{

	cout << "name: " << getName();
	cout << "gender: " << getGender();
	cout << "age: " << getAge();
	cout << "job: " << getJob();
	cout << "illness: " << getIllness();
	cout << "protein: " << getProtein() << endl;
	cout << "carbs: " << getCarbs() << endl;
	cout << "fats: " << getFats() << endl;
	cout << "fibre: " << getFibre() << endl;
}

int People::getProtein() { return protein; }
int People::getCarbs() { return carbs; }
int People::getFats() { return fats; }
int People::getFibre() { return fibre; }