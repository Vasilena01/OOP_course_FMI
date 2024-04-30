#include "SortedStudentDB.h"

void SortedStudentDB::sortByCriteria(const Criteria cr)
{
	switch (cr)
	{
	case Criteria::sortByName:return sortDataBase([](const Student& lhs, const Student& rhs) {return lhs.getName() == rhs.getName();});
	case Criteria::sortByFn:return sortDataBase([](const Student& lhs, const Student& rhs) {return lhs.getFn() < rhs.getFn();});
	case Criteria::sortByCourse:return sortDataBase([](const Student& lhs, const Student& rhs) {return lhs.getCourse() < rhs.getCourse();});
	}
}

void SortedStudentDB::sortDataBase(bool(*isLess)(const Student& lhs, const Student& rhs))
{
	for (int i = 0; i < this->getSize(); i++)
	{
		int minIndex = i;

		for (int j = i + 1; j < this->getSize(); j++)
		{
			if (isLess(this->getStudents()[j], this->getStudents()[minIndex]))
				minIndex = j;
		}

		if (minIndex != i)
		{
			std::swap(this->getStudents()[i], this->getStudents()[minIndex]);
		}
	}
}
