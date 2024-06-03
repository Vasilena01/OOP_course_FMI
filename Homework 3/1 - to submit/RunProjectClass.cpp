#include "RunProjectClass.h"

void RunProjectClass::executeFunc(PartialFunction*& function)
{
	int mode = 0;
	std::cout << "Choose mode (1 or 2): ";

	while (mode != 1 && mode != 2)
		std::cin >> mode;

	mode == 1 ? funcMode1(function) : funcMode2(function);
}

void RunProjectClass::funcMode1(PartialFunction*& function)
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
			std::cout << std::endl;
		}
	}
}

void RunProjectClass::funcMode2(PartialFunction*& function)
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
