#include "StudentTicket.h"

StudentTicket::StudentTicket(const MyString& name, double price) : Ticket(name, price / 2)
{
}

void StudentTicket::printStudentTicket() const
{
	this->printTicket();
}
