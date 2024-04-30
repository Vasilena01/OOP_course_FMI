#pragma once
#include "Tickets.h"

class StudentTicket : public Ticket
{
public:
	StudentTicket(const MyString& name, double price);
	void printStudentTicket() const;
private:
};


