#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include "People.h"


class PeopleManager 
{
public:
	PeopleManager();
	void testPurpose();
private:
	std::vector<People> peoples;
	std::vector<Status> ages;
	std::vector<Status> illnesses;
	std::vector<Status> jobs;

	void CreatePeople();
	int StringtoInt(string s);
	
};