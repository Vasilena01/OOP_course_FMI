#pragma once
#include <iostream>
#include <fstream>

struct Point
{
private:
	int16_t x;
	int16_t y;
	bool isDisabled;
public:
	int16_t getX() const;
	int16_t getY() const;
	bool getIsDisabled() const;
	void setX(int16_t x);	
	void setY(int16_t y);
	void setIsDisabled(bool flag);
	friend class ModifiableIntegersFunction;
};