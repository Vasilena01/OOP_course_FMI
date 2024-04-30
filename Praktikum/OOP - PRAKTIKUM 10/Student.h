#pragma once
#include "MyString.h"

class Student
{
public:
	Student() = default;
	Student(const MyString& name, unsigned fn, unsigned course);

	const MyString& getName() const;
	unsigned getFn() const;
	unsigned getCourse() const;
	void printStudent();
private:
	MyString name;
	unsigned fn;
	unsigned course;
};
