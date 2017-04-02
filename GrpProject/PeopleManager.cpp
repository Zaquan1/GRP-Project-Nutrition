#include "PeopleManager.h"

PeopleManager::PeopleManager()
{
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

void PeopleManager::CreatePeople()
{

}

void PeopleManager::testPurpose()
{
	for (int i = 0; i < jobs.size(); i++)
	{
		cout << jobs.at(i).getStatusName()<< endl;
		cout << jobs.at(i).getCarbs() << endl;
		cout << jobs.at(i).getFats() << endl;
		cout << jobs.at(i).getProtein() << endl;
		cout << jobs.at(i).getVeggies() << endl;
		cout << jobs.at(i).getVitamins() << endl;
		int test = jobs.at(i).getCarbs() - jobs.at(i).getFats();
		cout << test << endl;
	}
}

int PeopleManager::StringtoInt(string s)
{
	double d;
	stringstream(s) >> d;
	return (int) d;
}