#pragma once
#include <fstream>
#include "PartialFunction.h"
#include <sstream>

 namespace HelperFunctions
{
	size_t getFileSize(std::ifstream& file)
	{
		size_t currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		size_t fileSize = file.tellg();
		file.seekg(currentPos);
		return fileSize;
	}

	size_t getCountToSentinel(const char* buffer)
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
}



