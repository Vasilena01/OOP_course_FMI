#include "GroupTicket.h"

GroupTicket::GroupTicket(const MyString& name, double price) : Ticket(name, price - (0.2 * price))
{
}

void GroupTicket::printGroupTicket() const
{
	this->printTicket();
}
