#include "Student.h"

Student::Student(const MyString& name, unsigned fn, unsigned course)
{
	this->name = name;
	this->fn = fn;
	this->course = course;
}

const MyString& Student::getName() const
{
	return name;
}

unsigned Student::getFn() const
{
	return fn;
}

unsigned Student::getCourse() const
{
	return course;
}

void Student::printStudent()
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Fn: " << fn << std::endl;
	std::cout << "Course: " << course << std::endl;
}
