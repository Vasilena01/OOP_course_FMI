#include "FilteredStudentDB.h"

void FilteredStudentDB::filterByCriteria(const Criteria& cr, unsigned number)
{
	switch (cr)
	{
	case Criteria::sortByFn:return filterByFn(number);
	case Criteria::sortByCourse:return filterByCourse(number);
	}
}

void FilteredStudentDB::filterByName(const char* name)
{
	Student* newStudents = new Student[this->getCapacity() + 1];
	unsigned newSize = 0;

	for (int i = 0; i < this->getSize(); i++)
	{
		if (this->getStudents()[i].getName() == name)
		{
			newStudents[newSize++] = this->getStudents()[i];
		}
	}

	delete[] this->getStudents();
	this->setStudents(newStudents);
	this->setSize(newSize);
}

void FilteredStudentDB::filterByFn(unsigned fn)
{
	Student* newStudents = new Student[this->getCapacity() + 1];
	unsigned newSize = 0;

	for (int i = 0; i < this->getSize(); i++)
	{
		if (this->getStudents()[i].getFn() == fn)
		{
			newStudents[newSize++] = this->getStudents()[i];
		}
	}

	delete[] this->getStudents();
	this->setStudents(newStudents);
	this->setSize(newSize);
}

void FilteredStudentDB::filterByCourse(unsigned course)
{
	Student* newStudents = new Student[this->getCapacity() + 1];
	unsigned newSize = 0;

	for (int i = 0; i < this->getSize(); i++)
	{
		if (this->getStudents()[i].getCourse() == course)
		{
			newStudents[newSize++] = this->getStudents()[i];
		}
	}

	delete[] this->getStudents();
	this->setStudents(newStudents);
	this->setSize(newSize);
}

void FilteredStudentDB::saveFirstN(unsigned N)
{
	if (N > this->getSize())
		return;

	Student* newStudents = new Student[this->getCapacity() + 1];

	for (int i = 0; i < N; i++)
	{
		newStudents[i] = this->getStudents()[i];
	}

	delete[] this->getStudents();
	this->setStudents(newStudents);
	this->setSize(N);
}

