#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include "People.h"


class PeopleManager 
{
public:
	PeopleManager();
	void testPurpose();
private:
	std::vector<People> peoples;

	void CreatePeople();
	int StringtoInt(string s);
	
};