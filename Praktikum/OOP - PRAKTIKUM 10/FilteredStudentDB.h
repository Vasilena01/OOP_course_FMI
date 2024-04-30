#pragma once
#include "StudentDB.h"
#include "StudentCriteria.h"

class FilteredStudentDB : public StudentDB
{
public:
	using StudentDB::StudentDB;
	void filterByName(const char* name);
	void filterByCriteria(const Criteria& cr, unsigned number);
	void saveFirstN(unsigned N);
private:
	void filterByFn(unsigned fn);
	void filterByCourse(unsigned course);
};
