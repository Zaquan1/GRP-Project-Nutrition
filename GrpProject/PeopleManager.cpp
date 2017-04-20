#include "PeopleManager.h"
#include <time.h>

PeopleManager::PeopleManager()
{
	//add none status for both illness and jobs

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
		cout << str;
		do
		{
			if (strcmp(str, "*\n") == 0)
			{
				string name, age, gender, job, illness;
				int carbs, fats, protein, fibre;
				fgets(str, 100, fp);
				name = str;
				fgets(str, 100, fp);
				age = str;
				fgets(str, 100, fp);
				gender = str;
				fgets(str, 100, fp);
				illness = str;
				fgets(str, 100, fp);
				job = str;
				fgets(str, 100, fp);
				carbs = StringtoInt(str);
				fgets(str, 100, fp);
				fats = StringtoInt(str);
				fgets(str, 100, fp);
				protein = StringtoInt(str);
				fgets(str, 100, fp);
				fibre = StringtoInt(str);
				peoples.push_back(
					People(name, age, gender, job, illness, 
						protein, carbs, fats, fibre)
				);
			}
		} while (fgets(str, 100, fp) != NULL);

		fclose(fp);
	}
	shufflePeople();
}

void PeopleManager::shufflePeople()
{
		srand(time(NULL));
		random_shuffle(begin(peoples), end(peoples));

}

void PeopleManager::testPurpose()
{
	for (int i = 0; i < peoples.size(); i++)
	{
		cout << "people " << i << endl;
		peoples.at(i).status();
		cout << endl << endl;
	}
}

People PeopleManager::getPeople()
{
	return peoples.back();
}

void PeopleManager::removePeople()
{
	peoples.pop_back();
}

int PeopleManager::StringtoInt(string s)
{
	double d;
	stringstream(s) >> d;
	return (int) d;
}

int PeopleManager::peopleLeft()
{
	return peoples.size();
}