#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include "People.h"
#include <algorithm>
#include <time.h>


class PeopleManager 
{
public:
	PeopleManager();
	void testPurpose();
	void removePeople();
	People getPeople();
	int peopleLeft();

private:
	std::vector<People> peoples;

	void shufflePeople();
	int StringtoInt(string s);
	
};