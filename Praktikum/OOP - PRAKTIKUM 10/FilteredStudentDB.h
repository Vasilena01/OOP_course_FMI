#pragma once
#include "StudentDB.h"
#include "StudentCriteria.h"

class FilteredStudentDB : public StudentDB
{
public:
	using StudentDB::StudentDB;
	FilteredStudentDB& operator=(const FilteredStudentDB& other);
	
	void filterDataBase(const char* name);
	void filterDataBase(const Criteria cr, unsigned number);
	void saveFirstN(unsigned N);
private:
};
