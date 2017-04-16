#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include "People.h"
#include <algorithm>
#include <random>


class PeopleManager 
{
public:
	PeopleManager();
	void testPurpose();
	People getPeople();
	void removePeople();
private:
	std::vector<People> peoples;

	void CreatePeople();
	int StringtoInt(string s);
	
};