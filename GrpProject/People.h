#pragma once
#include <string>
#include <iostream>
using namespace std;

class People
{
public:
	People();
	~People(void);
	People(string n, string a, string g, string i, string j,
		int p, int c, int f, int fi);

	int getProtein();
	int getCarbs();
	int getFats();
	int getFibre();
	int intToPercentage(int a, int total);
	void status();

	string getName();
	string getGender();
	string getAge();
	string getIllness();
	string getJob();

private:
	string name;
	string gender;
	string age;
	string illness;
	string job;

	int protein;
	int carbs;
	int fats;
	int fibre;

	void CalculateStatus();

};