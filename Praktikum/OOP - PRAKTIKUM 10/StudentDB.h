#pragma once
#include "Student.h"

class StudentDB
{
public:
	StudentDB();
	explicit StudentDB(unsigned capacity);
	StudentDB(const StudentDB& other);
	StudentDB(StudentDB&& other) noexcept;
	StudentDB& operator=(const StudentDB& other);
	StudentDB& operator=(StudentDB&& other) noexcept;
	~StudentDB();

	unsigned getSize() const;
	Student* getStudents() const;

	void addAtBack(const Student& newStudent);
	void addAtBack(Student&& newStudent);
	void insert(const Student& newStudent, unsigned index);
	void insert(Student&& newStudent, unsigned index);
	void remove(unsigned fn);
	unsigned getStudentIndex(unsigned fn) const;
	Student& find(unsigned fn);
	void display() const;

private:
	Student* students;
	unsigned size;
	unsigned capacity;

	void resize(unsigned newAllocatedSize);
	void  copyFrom(const StudentDB& other);
	void  moveFrom(StudentDB&& other);
	void free();
};
