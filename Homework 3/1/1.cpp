#include <iostream>
#include <fstream>
#include "PartialFunctionFactory.h"
#include "PartialFunctionByCriteria.hpp"


int main()
{

	int* arr = new int[3] {2, 3, 34};

	BoolFunctionalityClass boolF(arr, 3);
	PartialFunctionByCriteria<BoolFunctionalityClass> f3(boolF);

	std::cout << f3(3);

	PartialFunction* function = PartialFunctionFactory::createFunction("first.dat");


	int mode = 0;
	std::cout << "Choose working mode (1 or 2): ";

	while (mode != 1 && mode != 2)
		std::cin >> mode;

	if (mode == 1)
	{
		std::cout << "Enter lower & upper bound in which the function to be printed: ";
		int32_t upper, lower;
		std::cin >> upper >> lower;
		while (upper > lower)
			std::cin >> upper >> lower;

		for (int32_t i = upper; i <= lower; i++)
		{
			try
			{
				std::cout << "f(" << i << ") = " << (*function)(i) << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "An error occured: " << e.what();
			}
		}
	}
	else
	{
		int32_t n;
		std::cout << "Enter values to get the value of the function:" << std::endl;
		while (true)
		{
			std::cin >> n;
			try
			{
				std::cout << "f(" << n << ") = " << (*function)(n) << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
}