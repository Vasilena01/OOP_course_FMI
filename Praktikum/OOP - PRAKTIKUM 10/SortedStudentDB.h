#pragma once
#include "StudentDB.h"
#include "StudentCriteria.h"

class SortedStudentDB : public StudentDB
{
public:
	using StudentDB::StudentDB;
	void sortByCriteria(const Criteria cr);
private:
	void sortDataBase(bool(*isLess)(const Student& lhs, const Student& rhs));
};