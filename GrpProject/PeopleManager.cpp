#include "PeopleManager.h"

PeopleManager::PeopleManager()
{
	//add none status for both illness and jobs
	Status none;
	illnesses.push_back(none);
	jobs.push_back(none);

	const char* filename = "record.txt";
	FILE *fp;
	char str[100];
	errno_t err;
	err = fopen_s(&fp, filename, "r");
	if (err != 0)
	{
		fprintf(stderr, "cannot open file '%s':\n",
			filename);
	}
	else
	{
		fgets(str, 100, fp);
		//read age categories in the file
		if (strcmp(str, "*age\n") == 0)
		{
			fgets(str, 100, fp);
			fgets(str, 100, fp);
			do {
				
				Status age(str);
				fgets(str, 100, fp);
				age.setCarbs(StringtoInt(str));
				fgets(str, 100, fp);
				age.setProtein(StringtoInt(str));
				fgets(str, 100, fp);
				age.setVeggies(StringtoInt(str));
				fgets(str, 100, fp);
				age.setFats(StringtoInt(str));
				fgets(str, 100, fp);
				age.setVitamins(StringtoInt(str));
				ages.push_back(age);
				fgets(str, 100, fp);
				fgets(str, 100, fp);
			} while (strcmp(str, "*jobs\n") != 0);
			fgets(str, 100, fp);
			fgets(str, 100, fp);
			//read jobs categories in file
			do {
				Status job(str);
				fgets(str, 100, fp);
				job.setCarbs(StringtoInt(str));
				fgets(str, 100, fp);
				job.setProtein(StringtoInt(str));
				fgets(str, 100, fp);
				job.setVeggies(StringtoInt(str));
				fgets(str, 100, fp);
				job.setFats(StringtoInt(str));
				fgets(str, 100, fp);
				job.setVitamins(StringtoInt(str));
				jobs.push_back(job);
				fgets(str, 100, fp);
				fgets(str, 100, fp);
			} while (strcmp(str, "*illness\n") != 0);
			fgets(str, 100, fp);
			fgets(str, 100, fp);
			//read illness categories in file
			do {
				Status illness(str);
				fgets(str, 100, fp);
				illness.setCarbs(StringtoInt(str));
				fgets(str, 100, fp);
				illness.setProtein(StringtoInt(str));
				fgets(str, 100, fp);
				illness.setVeggies(StringtoInt(str));
				fgets(str, 100, fp);
				illness.setFats(StringtoInt(str));
				fgets(str, 100, fp);
				illness.setVitamins(StringtoInt(str));
				illnesses.push_back(illness);
				fgets(str, 100, fp);
			} while (fgets(str, 100, fp) != NULL);

		}
	}
	CreatePeople();
}
//make the combination of status from the file
void PeopleManager::CreatePeople()
{
	for (int i = 0; i < ages.size(); i++)
	{
		for (int j = 0; j < illnesses.size(); j++)
		{
			if(StringtoInt(ages.at(i).getStatusName()) <16)
			{
				People p(ages.at(i), illnesses.at(j), jobs.at(0));
				peoples.push_back(p);
			}
			else
			{
				for (int k = 0; k < jobs.size(); k++)
				{
					People p(ages.at(i), illnesses.at(j), jobs.at(k));
					peoples.push_back(p);
				}
			}
		}
	}
}

void PeopleManager::testPurpose()
{
	cout << "age: " << ages.size() << endl;
	cout << "illness: " << illnesses.size() << endl;
	cout << "job: " << jobs.size() << endl;
	cout << "total people: " << peoples.size() << endl;
	for (int i = 0; i < peoples.size(); i++)
	{
		cout << "people " << i << endl;
		peoples.at(i).status();
		cout << endl << endl;
	}

}

int PeopleManager::StringtoInt(string s)
{
	double d;
	stringstream(s) >> d;
	return (int) d;
}