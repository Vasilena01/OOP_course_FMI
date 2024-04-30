#include <iostream>
#include "Tickets.h"
#include "StudentTicket.h"
#include "GroupTicket.h"

#include "StudentDB.h"
#include "SortedStudentDB.h"
#include "FilteredStudentDB.h"
#include "StudentCriteria.h"

int main()
{
	/*Zad 1
	Ticket normalTicket("normal", 34.5);
	StudentTicket studentTicket("student", 45.8);
	GroupTicket groupTicket("group", 45.8);

	normalTicket.printTicket();	
	studentTicket.printTicket();
	groupTicket.printTicket();*/

	/*Zad 2*/
	Student student1("vasi", 12346, 3);
	Student student2("dani", 12346, 2);
	Student student3("enisel", 123456, 1);

	StudentDB database(5);
	
	database.addAtBack(student1);
	database.addAtBack(student2);
	database.addAtBack(student3);
	//database.display();

	SortedStudentDB sortedDataBase(2);
	sortedDataBase.addAtBack(student1);
	sortedDataBase.addAtBack(student2);
	sortedDataBase.addAtBack(student3);
	
	sortedDataBase.sortByCriteria(Criteria::sortByCourse);
	//sortedDataBase.display();

	FilteredStudentDB filteredStudentDB(2);
	filteredStudentDB.addAtBack(student1);
	filteredStudentDB.addAtBack(student2);
	filteredStudentDB.addAtBack(student3);

	//filteredStudentDB.filterByName("enisel");
	//filteredStudentDB.filterByCriteria(Criteria::sortByCourse, 1);
	filteredStudentDB.saveFirstN(2);
	filteredStudentDB.display();
}
