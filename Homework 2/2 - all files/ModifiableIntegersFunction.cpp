#include "ModifiableIntegersFunction.h"

// Homework 2
// Zad 2
// Vasilena Stanoyska
// fn: 4MI0600290

namespace GlobalConstants
{
	int MAX_POINTS_ARR_SIZE = std::pow(2, 16);
}

// Big 6 
void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	points = new Point[GlobalConstants::MAX_POINTS_ARR_SIZE];

	for (int i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		points[i] = other.points[i];
	}
}

void ModifiableIntegersFunction::moveFrom(ModifiableIntegersFunction&& other)
{
	points = other.points;
	other.points = nullptr;
}

void ModifiableIntegersFunction::free()
{
	delete[] points;
}

ModifiableIntegersFunction::ModifiableIntegersFunction()
{
	points = new Point[GlobalConstants::MAX_POINTS_ARR_SIZE];
	int64_t index = 0;

	for (int64_t i = INT16_MIN; i <= INT16_MAX; i++) {
		points[index].x = i;
		points[index].y = i;
		points[index].isDisabled = false;
		index++;
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(FunctionPointer f)
{
	points = new Point[GlobalConstants::MAX_POINTS_ARR_SIZE];
	int64_t index = 0;

	for (int64_t i = INT16_MIN; i <= INT16_MAX; i++) {
		points[index].x = i;
		points[index].y = f(i);
		points[index].isDisabled = false;
		index++;
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction::ModifiableIntegersFunction(ModifiableIntegersFunction&& other) noexcept
{
	moveFrom(std::move(other));
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(ModifiableIntegersFunction&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

// Additional functions
void ModifiableIntegersFunction::setModification(int16_t valueToModify, int16_t newValue)
{
	int index = valueToModify - INT16_MIN;
	points[index].y = newValue;
	points[index].isDisabled = false;
}

void ModifiableIntegersFunction::disableValue(int16_t valueToDisable)
{
	int index = valueToDisable - INT16_MIN;
	points[index].isDisabled = true;
}

int16_t ModifiableIntegersFunction::operator()(int16_t x) const
{
	int index = x - INT16_MIN;
	if (points[index].isDisabled) {
		throw std::logic_error("Function is not defined for this value!");
	}
	return points[index].y;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator()(const ModifiableIntegersFunction& other) const
{
	ModifiableIntegersFunction result;

	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {

		int16_t composedInput = other.points[i].y;
		if (composedInput >= INT16_MIN && composedInput <= INT16_MAX) {
			int index = composedInput - INT16_MIN;

			if (other.points[index].isDisabled || points[i].isDisabled)
			{
				result.points[i].isDisabled = true;
			}
			else
			{
				result.points[i].y = points[index].y;
				result.points[i].isDisabled = false;
			}
		}
		else
		{
			result.points[i].isDisabled = true;
		}
	}

	return result;
}

ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int times) const
{
	ModifiableIntegersFunction result;

	if (times == 0) {
		return result;
	}
	else if (times == -1)
	{
		return inverse(*this);
	}
	else
	{
		result = *this;
	}

	ModifiableIntegersFunction temp = *this;

	for (int i = 1; i < times; ++i) {
		result = result(temp);
	}

	return result;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		if (points[i].y + other.points[i].y > INT16_MAX || points[i].y + other.points[i].y < INT16_MIN)
		{
			points[i].isDisabled = true;
		}
		else
		{
			points[i].y += other.points[i].y;
		}

		if (points[i].isDisabled || other.points[i].isDisabled)
			points[i].isDisabled = true;
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		if (points[i].y - other.points[i].y > INT16_MAX || points[i].y - other.points[i].y < INT16_MIN)
		{
			points[i].isDisabled = true;
		}
		else
		{
			points[i].y -= other.points[i].y;
		}

		if (points[i].isDisabled || other.points[i].isDisabled)
			points[i].isDisabled = true;
	}

	return *this;
}

void ModifiableIntegersFunction::serializeInBinaryFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ofstream file(fileName, std::ios::binary | std::ios::out);

	if(!file.is_open())
		throw std::runtime_error("Failed to open file to write to!");

	file.write((const char*)points, GlobalConstants::MAX_POINTS_ARR_SIZE * sizeof(Point));
}

void ModifiableIntegersFunction::deserializeFromBinaryFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ifstream file(fileName, std::ios::binary | std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file to read from!");

	file.read((char*)points, GlobalConstants::MAX_POINTS_ARR_SIZE * sizeof(Point));
}

void ModifiableIntegersFunction::printInInterval(int16_t x1, int16_t y1) const {
	int16_t x2 = x1 + 20;
	int16_t y2 = y1 + 20;

	if (x2 > INT16_MAX) x2 = INT16_MAX;
	if (y2 > INT16_MAX) y2 = INT16_MAX;

	for (int16_t i = y2; i >= y1; i--) {
		std::cout << "|";

		for (int16_t j = x1; j <= x2; j++) {
			int16_t result = this->operator()(j);

			if (result == i) {
				std::cout << "*";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "|" << std::endl;
	}
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		int16_t lhsRes = lhs.points[i].getIsDisabled() ? INT16_MIN : lhs.points[i].getY();
		int16_t rhsRes = rhs.points[i].getIsDisabled() ? INT16_MIN : rhs.points[i].getY();

		if (lhsRes <= rhsRes)
			return false;
	}
	return true;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		int16_t lhsRes = lhs.points[i].getIsDisabled() ? INT16_MIN : lhs.points[i].getY();
		int16_t rhsRes = rhs.points[i].getIsDisabled() ? INT16_MIN : rhs.points[i].getY();
		
		if (lhsRes >= rhsRes)
			return false;
	}
	return true;
}

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		int16_t lhsRes = lhs.points[i].getIsDisabled() ? INT16_MIN : lhs.points[i].getY();
		int16_t rhsRes = rhs.points[i].getIsDisabled() ? INT16_MIN : rhs.points[i].getY();

		if (lhsRes != rhsRes)
			return false;
	}
	return true;
}

bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		int16_t lhsRes = lhs.points[i].getIsDisabled() ? INT16_MIN : lhs.points[i].getY();
		int16_t rhsRes = rhs.points[i].getIsDisabled() ? INT16_MIN : rhs.points[i].getY();

		if (lhsRes == rhsRes)
			return false;
	}
	return true;
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	bool differenceSet = false;
	int16_t initialDifference = 0;

	// Finding the first valid difference to set as baseline
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		if (!lhs.points[i].getIsDisabled() && !rhs.points[i].getIsDisabled()) {
			initialDifference = lhs.points[i].getY() - rhs.points[i].getY();
			differenceSet = true;
			break;
		}
	}

	// If no difference was set, return true (assuming no difference means parallel)
	if (!differenceSet)
		return true;

	// Validating that all other differences match the initial one found
	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		if (!lhs.points[i].getIsDisabled() && !rhs.points[i].getIsDisabled()) {
			int16_t currentDifference = lhs.points[i].getY() - rhs.points[i].getY();
			if (currentDifference != initialDifference)
				return false;
		}
		else if ((!lhs.points[i].getIsDisabled() && rhs.points[i].getIsDisabled()) || (lhs.points[i].getIsDisabled() && !rhs.points[i].getIsDisabled())) {
			return false;
		}
	}

	return true;
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction lhsCopy(lhs);
	lhsCopy += rhs;

	return lhsCopy;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction lhsCopy(lhs);
	lhsCopy -= rhs;

	return lhsCopy;
}

ModifiableIntegersFunction inverse(const ModifiableIntegersFunction& other)
{
	if (!isBijective(other))
		throw std::logic_error("The function is not bijective, so it can't be reversed!");

	ModifiableIntegersFunction inverse;

	for (int i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		inverse.points[i].setIsDisabled(true);
	}

	for (int i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++) {
		if (!other.points[i].getIsDisabled()) {
			int16_t input = i + INT16_MIN;
			int16_t output = other.points[i].getY();
			int index = output - INT16_MIN;


			if (index >= 0 && index < GlobalConstants::MAX_POINTS_ARR_SIZE && inverse.points[index].getIsDisabled()) {
				inverse.points[index].setY(input);
				inverse.points[index].setIsDisabled(false);
			}
			else {
				throw std::logic_error("Output out of range can't be inverted!");
			}
		}
	}
	return inverse;
}

bool isInjective(const ModifiableIntegersFunction& other)
{
	bool seenYValues[GlobalConstants::POINTS_COUNT_CONST]{false};

	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		if (seenYValues[other.points[i].getY() + INT16_MAX + 1] == true)
			return false;

		if (!other.points[i].getIsDisabled())
			seenYValues[other.points[i].getY() + INT16_MAX + 1] = true;
	}

	return true;
}

bool isSurjective(const ModifiableIntegersFunction& other)
{
	bool seenXValues[GlobalConstants::POINTS_COUNT_CONST]{ false };

	for (int64_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		if (!other.points[i].getIsDisabled())
		{
			seenXValues[other.points[i].getY() + INT16_MAX + 1] = true;
		}
	}

	for (size_t i = 0; i < GlobalConstants::MAX_POINTS_ARR_SIZE; i++)
	{
		if (!seenXValues[i])
			return false;
	}

	return true;
}

bool isBijective(const ModifiableIntegersFunction& other)
{
	if (isInjective(other) && isSurjective(other))
		return true;
	return false;
}


