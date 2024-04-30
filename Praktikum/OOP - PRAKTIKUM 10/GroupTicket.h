#pragma once
#include "Tickets.h"

class GroupTicket : public Ticket
{
public:
	GroupTicket(const MyString& name, double price);
	void printGroupTicket() const;
private:
};
