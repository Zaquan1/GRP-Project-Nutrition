#pragma once
#include <vector>
#include "People.h"


class PeopleManager 
{
public:
	PeopleManager(string peopleInfo);

private:
	std::vector<People> Peoples;

	void CreatePeople();

};