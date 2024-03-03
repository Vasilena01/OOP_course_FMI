#include <iostream>
#include <fstream>

/*Zad - get the count of an element occurences in a file*/
int countElementOccur(const char* fileName, char ch)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Error!";
		return -1;
	}

	int count = 0;
	char currentChar;

	/*while (!file.eof())
	{
		file >> currentChar;
		std::cout << currentChar;
		if (currentChar == ch)
			count++;
	}*/

	while (file.get(currentChar))
	{
		if (currentChar == ch)
			count++;
	}

	file.close();

	return count;
}

/*Zad 1*/
void writeSumRestOfNumsToFile(const char* fileName)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error!";
		return;
	}

	int num1, num2;
	std::cin >> num1 >> num2;

	file << num1 + num2 << "\n" << abs(num1 - num2);

	file.close();
}

void getNumsFromFile(const char* fileName, int& num1, int& num2)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error!";
		return;
	}

	int sum, rest;

	file >> sum >> rest;

	num1 = (sum - rest) / 2;
	num2 = sum - num1;

	file.close();
}

/*Zad 2*/
int getMostOccuredDigitInArr(const int* numbers, size_t size)
{
	if (!numbers)
		return -1;

	int currentIndex = 0;
	int maxOccurences = 0;

	for (int i = 0; i < size; i++)
	{
		int countCurrentOccurences = 0;

		for (int j = i + 1; j < size; j++)
		{
			if (numbers[i] == numbers[j])
				countCurrentOccurences++;
		}

		if (countCurrentOccurences > maxOccurences)
		{
			maxOccurences = countCurrentOccurences;
			currentIndex = i;
		}
	}

	return numbers[currentIndex];
}

int getMostOccuredDigitFromFile(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error!";
		return -1;
	}

	int numbersCount;
	int mostOccuredNum = 0;
	int currentNum;

	file >> numbersCount;

	int numbers[64] = {};
	int indexOfNums = 0;

	while (indexOfNums < numbersCount)
	{
		file >> currentNum;
		numbers[indexOfNums] = currentNum;
		indexOfNums++;

		if (file.eof())
			break;
	}

	mostOccuredNum = getMostOccuredDigitInArr(numbers, numbersCount);
	return mostOccuredNum;
}

/*Zad 3*/
void selfPrintingCode(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
		return;

	char currentChar;

	//First solution
	while (file.get(currentChar))
	{
		std::cout << currentChar;
	}

	/*Second solution
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		std::cout << buff << std::endl;
	}*/
}

/*Zad 4*/
void getFirstDifferentLine(const char* firstFileName, const char* secondFileName)
{
	constexpr int BUFF_SIZE = 1024;

	std::ifstream firstFile(firstFileName);
	std::ifstream secondFile(secondFileName);

	if (!firstFile.is_open() || !secondFile.is_open())
	{
		std::cerr << "Failed to open files!";
		return;
	}

	while (!firstFile.eof() || !secondFile.eof())
	{
		char firstBuff[BUFF_SIZE];
		char secondBuff[BUFF_SIZE];

		firstFile.getline(firstBuff, BUFF_SIZE);
		secondFile.getline(secondBuff, BUFF_SIZE);

		if (std::strcmp(firstBuff, secondBuff) != 0)
		{
			std::cout << firstBuff << std::endl;
			return;
		}
	}

	std::cout << "The files are the same!";
}

/*Zad 5*/
constexpr int MAX_PAIRS_COUNT = 25;

struct Pair
{
	unsigned int num1 = 0;
	unsigned int num2 = 0;
};

struct Relation
{
	int pairsCount = 3;
	Pair pairs[MAX_PAIRS_COUNT];
};

void printPair(const Pair& pair)
{
	std::cout << pair.num1 << " " << pair.num2 << std::endl;
}

void printRelation(const Relation& relation)
{
	std::cout << relation.pairsCount << std::endl;

	for (int i = 0; i < relation.pairsCount; i++)
		printPair(relation.pairs[i]);
}

void getPair(std::ifstream& file, Pair& pair)
{
	file >> pair.num1;
	file >> pair.num2;
}

Pair& getPairInput()
{
	Pair pair;
	std::cin >> pair.num1 >> pair.num2;
	return pair;
}

void readRelationFromFile(const char* fileName, Relation& relation)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file!";
		return;
	}

	file >> relation.pairsCount;

	for (int i = 0; i < relation.pairsCount; i++)
	{
		getPair(file, relation.pairs[i]);

		if (file.eof())
			break;
	}
}

void addNewPairToRelation(Relation& relation)
{
	int index = relation.pairsCount;

	relation.pairs[index] = getPairInput();
	relation.pairsCount++;
}

void addPairToFile(std::ostream& file, const Pair& pair)
{
	file << pair.num1 << " " << pair.num2 << '\n';
}

void addRelationToFile(const char* fileName, const Relation& relation)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed opening file!";
		return;
	}

	file << relation.pairsCount << '\n';

	for (int i = 0; i < relation.pairsCount; i++)
	{
		addPairToFile(file, relation.pairs[i]);
	}
}

/*Zad 6*/
constexpr int MAX_NAME_SIZE = 63;
constexpr int MAX_CITIES_COUNT = 20;

struct City
{
	char name[MAX_NAME_SIZE];
	long citizensCount = 0;
};

struct District
{
	int citiesCount = 3;
	City cities[MAX_CITIES_COUNT];
};

void printCity(const City& city)
{
	std::cout << "Name: " << city.name << " Citizens: " << city.citizensCount << std::endl;
}

void printDistrict(const District& district)
{
	std::cout << district.citiesCount << std::endl;

	for (int i = 0; i < district.citiesCount; i++)
	{
		printCity(district.cities[i]);
	}
}

void sortDistrictByCitizensCount(District& district)
{
	for (int i = 0; i < district.citiesCount; i++)
	{
		int maxIndex = i;

		for (int j = i + 1; j < district.citiesCount; j++)
		{
			if (district.cities[j].citizensCount > district.cities[maxIndex].citizensCount)
			{
				maxIndex = j;
			}
		}

		if (maxIndex != i)
		{
			std::swap(district.cities[i], district.cities[maxIndex]);
		}
	}
}

void getCityInput(City& city)
{
	std::cout << "Name: ";
	std::cin >> city.name;

	std::cout << "Citizens count: ";
	std::cin >> city.citizensCount;
}

void getDistrictInput(District& district)
{
	std::cout << "Cities count: ";
	std::cin >> district.citiesCount;

	for (int i = 0; i < district.citiesCount; i++)
	{
		std::cout << "City " << i << std::endl;
		getCityInput(district.cities[i]);
	}
}

void writeCityToFile(std::ofstream& file, const City& city)
{
	file << city.name << '\n' << city.citizensCount << '\n';
}

void addDistrictToFile(const char* fileName, const District& district)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed opening file!";
		return;
	}

	file << district.citiesCount << '\n';

	for (int i = 0; i < district.citiesCount; i++)
	{
		writeCityToFile(file, district.cities[i]);
	}
}

void readCityFromFile(std::ifstream& file, City& city)
{
	char buffer[63];
	file.getline(buffer, 63);
	strcpy_s(city.name, buffer);

	file >> city.citizensCount;
}

void readDistrictFromFile(const char* fileName, District& district)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Failed opening file!";
		return;
	}

	file >> district.citiesCount;
	file.ignore();

	for (int i = 0; i < district.citiesCount; i++)
	{
		readCityFromFile(file, district.cities[i]);
		file.ignore();

		if (file.eof())
			break;
	}
}

/*Zad 7*/
void fillDestBasedOnSource(std::ofstream& file, const char* buff)
{
	if (!buff)
		return;

	if (std::strcmp(buff, "title") == 0)
		file << "Morning";
	else if (std::strcmp(buff, "recipient_name") == 0)
		file << "Vasilena St";
	else if (std::strcmp(buff, "message") == 0)
		file << "my name is...";
	else if (std::strcmp(buff, "sender_name") == 0)
		file << "Anelia T";
}

void fillDestWithPlaceholderFileValues(std::ofstream& file, std::ifstream& placeholder, const char* buff)
{
	if (!buff)
		return;

	char placeholderBuff[1024];
	placeholder.getline(placeholderBuff, 1024, ' ');

	if (std::strcmp(placeholderBuff, buff) == 0)
	{
		char text[1024];
		placeholder.getline(text, 1024, '\n');
		file << text;
	}
}

void replacePlaceholders(const char* fileNameSource, const char* fileNameDest)
{
	std::ifstream fileSource(fileNameSource);
	std::ofstream fileDest(fileNameDest);
	std::ifstream placeholderFile("placeholderValues_zad7.txt");

	if (!fileSource.is_open() || !fileDest.is_open())
	{
		std::cerr << "Failed opening file!";
		return;
	}

	char currentChar;
	while (fileSource.get(currentChar))
	{
		if (currentChar == '{')
		{
			char buff[1024];
			fileSource.getline(buff, 1024, '}');
			//fillDestBasedOnSource(fileDest, buff);
			fillDestWithPlaceholderFileValues(fileDest, placeholderFile, buff);
		}
		else
			fileDest << currentChar;
	}

}

int main()
{
	const char FILE_NAME[] = "OOP - PRAKTIKUM 2.cpp";

	/*Count given element occurences in a file
	const char FILE_NAME[] = "test_read.txt";

	std::cout << countElementOccur(FILE_NAME, '\n');*/

	/*Zad 1
	int num1, num2;
	writeSumRestOfNumsToFile(FILE_NAME);
	getNumsFromFile(FILE_NAME, num1, num2);
	std::cout << num1 << " " << num2;*/

	/*Zad 2
	std::cout << getMostOccuredDigitFromFile(FILE_NAME);*/

	/*Zad 3
	selfPrintingCode(FILE_NAME);*/

	/*Zad 4
	getFirstDifferentLine("compareFirst_zad4.txt", "compareSecond_zad4.txt");*/

	/*Zad 5
	Relation relation;
	readRelationFromFile("relation_zad5.txt", relation);
	//printRelation(relation);

	addNewPairToRelation(relation);
	printRelation(relation);

	addRelationToFile("addedRelation_zad5.txt", relation);*/

	/*Zad 6
	District district;
	//getDistrictInput(district);
	//addDistrictToFile("district_zad6.txt", district);
	readDistrictFromFile("district_zad6.txt", district);
	sortDistrictByCitizensCount(district);
	printDistrict(district);
	addDistrictToFile("sortedDistrict_zad6.txt", district);*/

	/*Zad 7
	replacePlaceholders("textWithPlaceholders_zad7.txt", "fullText_zad7.txt");*/
}
