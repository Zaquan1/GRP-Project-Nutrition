#include "People.h"

People::People(string n, string g, string a, string i, string j,
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
	return (int)((a / total) * 100);
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