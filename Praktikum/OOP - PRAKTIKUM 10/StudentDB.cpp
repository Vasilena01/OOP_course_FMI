#include "StudentDB.h"

// BIG 6
StudentDB::StudentDB()
{
	students = nullptr;
	capacity = 0;
	size = 0;
}

StudentDB::StudentDB(unsigned capacity)
{
	this->students = new Student[capacity];
	this->capacity = capacity;
	this->size = 0;
}

StudentDB::StudentDB(const StudentDB& other)
{
	copyFrom(other);
}

StudentDB::StudentDB(StudentDB&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentDB& StudentDB::operator=(const StudentDB& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StudentDB& StudentDB::operator=(StudentDB&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

StudentDB::~StudentDB()
{
	free();
}

unsigned StudentDB::getSize() const
{
	return size;
}

Student* StudentDB::getStudents() const
{
	return students;
}


// Additional functions
void StudentDB::resize(unsigned newAllocatedSize)
{
	Student* newStudents = new Student[newAllocatedSize + 1];
	for (int i = 0; i < size; i++)
	{
		newStudents[i] = students[i];
	}

	delete[] students;
	students = newStudents;
	capacity = newAllocatedSize;
}

void StudentDB::addAtBack(const Student& newStudent)
{
	if (size == capacity)
		resize(capacity * 2);

	students[size++] = newStudent;
}

void StudentDB::addAtBack(Student&& newStudent)
{
	if (size == capacity)
		resize(capacity * 2);

	students[size++] = std::move(newStudent);
}

void StudentDB::insert(const Student& newStudent, unsigned index)
{
	if (index >= capacity)
		return;

	if (size == capacity)
		resize(capacity * 2);

	for (int i = size - 1; i > index; i--)
	{
		students[i] = students[i - 1];
	}

	students[index] = newStudent;
	size++;
}

void StudentDB::insert(Student&& newStudent, unsigned index)
{
	if (index >= capacity)
		return;

	if (size >= capacity)
		resize(capacity * 2);

	for (int i = size - 1; i > index; i--)
	{
		students[i] = students[i - 1];
	}

	students[index] = std::move(newStudent);
	size++;
}

void StudentDB::remove(unsigned fn)
{
	int index = getStudentIndex(fn);
	if (!(index >= 0))
		return;

	for (int i = index; i < size; i++)
	{
		students[i] = students[i + 1];
	}
	size--;
}

unsigned StudentDB::getStudentIndex(unsigned fn) const
{
	for (int i = 0; i < size; i++)
	{
		if (students[i].getFn() == fn)
			return i;
	}
	return -1;
}

Student& StudentDB::find(unsigned fn)
{
	int index = getStudentIndex(fn);

	return students[index];
}

void StudentDB::display() const
{
	for (int i = 0; i < size; i++)
	{
		students[i].printStudent();
	}
}

void StudentDB::copyFrom(const StudentDB& other)
{
	students = new Student[other.capacity];
	for (int i = 0; i < other.size; i++)
	{
		students[i] = other.students[i];
	}

	capacity = other.capacity;
	size = other.size;
}

void StudentDB::moveFrom(StudentDB&& other)
{
	students = other.students;
	other.students = nullptr;

	capacity = other.capacity;
	other.capacity = 0;

	size = other.size;
	other.size = 0;
}

void StudentDB::free()
{
	delete[] students;
}
