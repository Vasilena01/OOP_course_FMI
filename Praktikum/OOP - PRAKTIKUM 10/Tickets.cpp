#include "Tickets.h"

Ticket::Ticket(const MyString& name, double price)
{
	this->name = name;
	this->price = price;
}

void Ticket::printTicket() const
{
	std::cout << "Ticket Name: " << name << std::endl;
	std::cout << "Ticket Price: " << price << std::endl;
}
