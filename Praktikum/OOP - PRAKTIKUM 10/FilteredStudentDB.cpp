#include "FilteredStudentDB.h"

FilteredStudentDB& FilteredStudentDB::operator=(const FilteredStudentDB& other)
{
	StudentDB::operator=(other);
	return *this;
}

void FilteredStudentDB::filterDataBase(const char* name)
{
	FilteredStudentDB newDatabase;

	for (int i = 0; i < this->getSize() - 1; i++)
	{
		if (this->getStudents()[i].getName() == name)
			newDatabase.addAtBack(this->getStudents()[i]);
	}

	*this = newDatabase;
	//return newDatabase;
}

void FilteredStudentDB::filterDataBase(const Criteria cr, unsigned number)
{
	FilteredStudentDB newDatabase;

	for (int i = 0; i < this->getSize() - 1; i++)
	{
		if (cr == Criteria::sortByFn && this->getStudents()[i].getFn() == number)
		{
			newDatabase.addAtBack(this->getStudents()[i]);
		}

		if (cr == Criteria::sortByCourse && this->getStudents()[i].getCourse() == number)
		{
			newDatabase.addAtBack(this->getStudents()[i]);
		}
	}

	*this = newDatabase;
}

void FilteredStudentDB::saveFirstN(unsigned N)
{
	FilteredStudentDB newDatabase;

	for (int i = 0; i < N; i++)
	{
		newDatabase.addAtBack(this->getStudents()[i]);
	}

	//delete[] this;
	*this = newDatabase;
}

