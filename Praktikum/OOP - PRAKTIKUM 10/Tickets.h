#pragma once
#include "MyString.h"

class Ticket
{
public:
	Ticket(const MyString& name, double price);
	void printTicket() const;
private:
	MyString name;
	double price;
};
