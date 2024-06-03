#include "PartialFunctionFactory.h"
#include "HelperFunctions.h"
#include "PartialFunctionByCriteria.hpp"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"
#include "BoolFunctionalityClass.h"
#include "DefinedFunctionalityClass.h"
#include "UndefinedFunctionalityClass.h"

void readFunctionFromFile(PartialFunction** partialFunctions, char* buffer, uint16_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		std::stringstream ss(buffer);

		size_t currentFilenameLength = HelperFunctions::getCountToSentinel(buffer);
		buffer += currentFilenameLength + 1;
		char* currentFileName = new char[currentFilenameLength];

		ss >> currentFileName;

		partialFunctions[i] = PartialFunctionFactory::createFunction(currentFileName);
	}
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

		file.read((char*)arguments, sizeof(int32_t) * N);
		file.read((char*)results, sizeof(int32_t) * N);

		DefinedFunctionalityClass function(arguments, results, N);
		return new PartialFunctionByCriteria<DefinedFunctionalityClass>(function);
	}
	case 1:
	{
		int32_t* undefinedResults = new int32_t[N];
		file.read((char*)undefinedResults, sizeof(int32_t) * N);

		UndefinedFunctionalityClass function(undefinedResults, N);
		return new PartialFunctionByCriteria<UndefinedFunctionalityClass>(function);
	}
	case 2:
	{
		int32_t* arguments = new int32_t[N];
		file.read((char*)arguments, sizeof(int32_t) * N);

		BoolFunctionalityClass function(arguments, N);
		return new PartialFunctionByCriteria<BoolFunctionalityClass>(function);
	}
	case 3:
	case 4:
	{
		PartialFunction** partialFunctions = new PartialFunction * [N];

		size_t fileSize = HelperFunctions::getFileSize(file);
		fileSize -= sizeof(uint16_t) * 2;

		char* buffer = new char[fileSize];
		file.read(buffer, fileSize);

		try {

			readFunctionFromFile(partialFunctions, buffer, N);
			delete[] buffer;
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		if(T == 3)
			return createMaxFunction(partialFunctions, N);
		return createMinFunction(partialFunctions, N);
	}	
	default:
		throw std::invalid_argument("Invalid value for N!");
		break;
	}
}

PartialFunction* PartialFunctionFactory::createMaxFunction(PartialFunction** functions, uint16_t N)
{
	return new MaxPartialFunction(functions, N);
}

PartialFunction* PartialFunctionFactory::createMinFunction(PartialFunction** functions, uint16_t N)
{
	return new MinPartialFunction(functions, N);
}
