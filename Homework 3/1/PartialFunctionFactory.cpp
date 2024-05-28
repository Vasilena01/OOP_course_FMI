#include "PartialFunctionFactory.h"
#include "PartialFunctionByCriteria.h"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"
#include "BaseFunctionalityClass.h"
#include "BoolFunctionalityClass.h"
#include "DefinedFunctionalityClass.h"
#include "UndefinedFunctionalityClass.h"
#include <fstream>
#include <sstream>

size_t getFileSize(std::ifstream& file)
{
	size_t currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(currentPos);
	return fileSize;
}

size_t getCountToTerminatingZero(const char* buffer)
{
	size_t counter = 0;

	while (*buffer)
	{
		counter++;
		buffer++;
	}
	buffer++;

	return counter;
}

PartialFunction* PartialFunctionFactory::createFunction(const char* fileName)
{
	if (!fileName)
		throw std::invalid_argument("Null ptr!");

	std::ifstream file(fileName, std::ios::binary | std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Can't open file!");

	uint16_t N;
	uint16_t T;

	file.read((char*)&N, sizeof(uint16_t));
	file.read((char*)&T, sizeof(uint16_t));

	return createFunctionByType(N, T, file);
}

PartialFunction* PartialFunctionFactory::createFunctionByType(uint16_t N, uint16_t T, std::ifstream& file)
{
	if (N < 0 || T > 32)
		throw std::invalid_argument("Invalid value for N or T!");

	switch (T)
	{
	case 0:
	{
		int32_t* arguments = new int32_t[N];
		int32_t* results = new int32_t[N];

		file.read((char*)&arguments, sizeof(int32_t) * N);
		file.read((char*)&results, sizeof(int32_t) * N);

		return createFunctionByCriteria(new DefinedFunctionalityClass(arguments, results, N));
	}
	case 1:
	{
		int32_t* undefinedResults = new int32_t[N];
		file.read((char*)&undefinedResults, sizeof(int32_t) * N);

		return createFunctionByCriteria(new UndefinedFunctionalityClass(undefinedResults, N));
	}
	case 2:
	{
		int32_t* arguments = new int32_t[N];
		file.read((char*)&arguments, sizeof(int32_t) * N);

		return createFunctionByCriteria(new UndefinedFunctionalityClass(arguments, N));
	}
	case 3:
	{
		PartialFunction** partialFunctions = new PartialFunction * [N];

		size_t fileSize = getFileSize(file);
		fileSize -= sizeof(uint16_t) * 2;

		char* buffer = new char[fileSize];
		file.read(buffer, fileSize);

		try {

			for (size_t i = 0; i < N; i++)
			{
				std::stringstream ss(buffer);

				size_t currentFilenameLength = getCountToTerminatingZero(buffer);
				buffer += currentFilenameLength + 1;
				char* currentFileName = new char[currentFilenameLength];

				ss >> currentFileName;

				partialFunctions[i] = PartialFunctionFactory::createFunction(currentFileName);
			}

		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		return createMaxFunction(partialFunctions, N);
	}
	case 4:
	{
		// return createMinFunction
	}
	default:
		throw std::invalid_argument("Invalid value for N!");
		break;
	}
}

PartialFunction* PartialFunctionFactory::createFunctionByCriteria(const BaseFunctionalityClass* obj)
{
	return new PartialFunctionByCriteria(obj);
}

PartialFunction* PartialFunctionFactory::createMaxFunction(PartialFunction** functions, uint16_t N)
{
	return new MaxPartialFunction(functions, N);
}

PartialFunction* PartialFunctionFactory::createMinFunction(PartialFunction** functions, uint16_t N)
{
	return new MinPartialFunction(functions, N);
}