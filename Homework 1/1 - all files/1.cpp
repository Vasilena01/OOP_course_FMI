// Homework 1
// Vasilena Stanoyska
// fn: 4MI0600290
// Zad 1

#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning (disable : 4996)

namespace GlobalConstants
{
	constexpr size_t MAX_CELL_SIZE = 50;
	constexpr size_t MAX_CELLS_COUNT = 30;
	constexpr size_t MAX_ROWS_COUNT = 300;
	constexpr size_t MAX_FILE_NAME_SIZE = 50;
	constexpr size_t MAX_BUFFER_SIZE = 1024;
	constexpr size_t MAX_COMMAND_SIZE = 50;
}

char* getTagName(std::ifstream& file, char currentChar)
{
	char buff[GlobalConstants::MAX_BUFFER_SIZE];
	int index = 0;

	while (file.get(currentChar) && currentChar != '>')
	{
		buff[index++] = currentChar;
	}
	buff[index] = '\0';

	return buff;
}

int countTagOccurencesBetweenTags(std::ifstream& file, const char* openTag, const char* closingTag, const char* endTag)
{
	if (!openTag || !closingTag || !endTag)
		return -1;

	char currentChar;
	char* currentTagName = nullptr;
	int count = 0;
	bool insideTag = false;
	int currentPos = file.tellg();

	while (file.get(currentChar))
	{
		if (currentChar == '<')
		{
			currentTagName = getTagName(file, currentChar);

			if (strcmp(currentTagName, openTag) == 0 && !insideTag)
			{
				count++;
				insideTag = true;
			}
			else if (strcmp(currentTagName, closingTag) == 0)
				insideTag = false;
			else if (strcmp(currentTagName, endTag) == 0)
			{
				insideTag = false;
				file.seekg(currentPos);
				return count;
			}
		}
	}
	file.seekg(currentPos);
	return count;
}

const char* convertToValidString(const char* encoded)
{
	char decoded[GlobalConstants::MAX_FILE_NAME_SIZE];
	int encodedIndex = 0, decodedIndex = 0;

	while (encoded[encodedIndex]) {
		if (encoded[encodedIndex] == '&') {
			if (encoded[encodedIndex + 1] == '#') {
				int code = 0;
				// Skips '&#'
				int k = encodedIndex + 2;
				while (encoded[k] >= '0' && encoded[k] <= '9') {
					code = code * 10 + (encoded[k] - '0');
					k++;
				}
				if ((code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z')) {
					decoded[decodedIndex++] = code;
					// Updates i to point after the ;
					encodedIndex = k;
				}
				else {
					// When we have not a valid letter code, copy the '&' and the following characters
					decoded[decodedIndex++] = '&';
					encodedIndex++;
				}
			}
			else {
				// When we have not a numeric entity reference, copy the '&' and the following characters
				decoded[decodedIndex++] = '&';
				encodedIndex++;
			}
		}
		else {
			// Normal character, copy
			decoded[decodedIndex++] = encoded[encodedIndex++];
		}
	}
	decoded[decodedIndex] = '\0';
	return decoded;
}

void putPointerOnNextRow(std::ifstream& file)
{
	char currentChar;
	char* tagName = nullptr;

	while (file >> currentChar)
	{
		if (currentChar == '<')
		{
			tagName = getTagName(file, currentChar);

			if (strcmp(tagName, "tr") == 0)
			{
				file.seekg(-2, std::ios::cur);
				break;
			}
		}
	}
}

void printSpaces(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << " ";
}

// CELL CLASS
class Cell
{
private:
	bool isHeader;
	size_t symbolsInCellCount;
	char symbols[GlobalConstants::MAX_CELL_SIZE];
public:
	Cell()
	{
		this->isHeader = false;
		this->symbolsInCellCount = 0;
		strcpy(this->symbols, "");
	}

	Cell(bool isHeader, size_t symbolsInCellCount, const char* symbols)
	{
		this->isHeader = isHeader;
		this->symbolsInCellCount = symbolsInCellCount;
		strcpy(this->symbols, symbols);
	}

	bool getIsHeader() const;

	size_t getSymbolsCount() const;

	char* getSymbols();

	char* getCellData(std::ifstream& file);

	void setSymbols(const char* symbols);

	void setIsHeader(bool isHeader);

	void setSymbolsInCellCount(int count);

	void assignDataToCell(std::ifstream& file);

	void fillCell(std::ifstream& file);

	void printCell(int maxSymbolsCount);

	void insertCellInFile(std::ofstream& file);
};

bool Cell::getIsHeader() const
{
	return this->isHeader;
}

size_t Cell::getSymbolsCount() const
{
	return this->symbolsInCellCount;
}

char* Cell::getSymbols()
{
	return this->symbols;
}

void Cell::setSymbols(const char* symbols)
{
	strcpy(this->symbols, symbols);
}

void Cell::setIsHeader(bool isHeader)
{
	this->isHeader = isHeader;
}

void Cell::setSymbolsInCellCount(int count)
{
	this->symbolsInCellCount = count;
}

char* Cell::getCellData(std::ifstream& file)
{
	char buff[GlobalConstants::MAX_BUFFER_SIZE];
	file.getline(buff, GlobalConstants::MAX_BUFFER_SIZE, '<');
	return buff;
}

void Cell::assignDataToCell(std::ifstream& file)
{
	char* cellData = nullptr;
	cellData = getCellData(file);

	strcpy(this->symbols, convertToValidString(cellData));
	this->symbolsInCellCount = strlen(this->symbols);
}

void Cell::fillCell(std::ifstream& file)
{
	char currentChar;
	char* tagName = nullptr;

	while (file >> currentChar)
	{
		if (currentChar == '<')
		{
			tagName = getTagName(file, currentChar);
			if (strcmp(tagName, "th") == 0)
			{
				this->isHeader = true;
				assignDataToCell(file);
				break;
			}
			else if (strcmp(tagName, "td") == 0)
			{
				this->isHeader = false;
				assignDataToCell(file);
				break;
			}
		}
	}
}

void Cell::printCell(int maxSymbolsCount)
{
	int spacesCount = maxSymbolsCount - this->symbolsInCellCount;

	if (this->isHeader)
	{
		std::cout << "|*" << this->symbols;
		printSpaces(spacesCount);
		std::cout << "*|";
	}
	else
	{
		std::cout << "| " << this->symbols;
		printSpaces(spacesCount);
		std::cout << " |";
	}
}

void Cell::insertCellInFile(std::ofstream& file)
{
	if (isHeader)
		file << "      <th>" << symbols << "</th>" << '\n';
	else
		file << "      <td>" << symbols << "</td>" << '\n';
}

// ROW CLASS
class Row
{
private:
	size_t cellsCount;
	Cell cells[GlobalConstants::MAX_CELLS_COUNT];
public:
	Row()
	{
		this->cellsCount = 0;
		for (int i = 0; i < GlobalConstants::MAX_CELLS_COUNT; i++)
			this->cells[i] = Cell();
	}

	int getCellsCount() const;

	Cell* getCells();

	void fillRow(std::ifstream& file);

	void printRow(int maxCellsCount, int* maxSymbolsCount);

	void addCellsInRow(std::stringstream& values, int valuesCount);

	void editRow(int cellIndex, const char* value);

	void clearRow();

	void insertRowInFile(std::ofstream& file);
};

int Row::getCellsCount() const
{
	return this->cellsCount;
}

Cell* Row::getCells()
{
	return this->cells;
}

void Row::fillRow(std::ifstream& file)
{
	// Counting the header and data cells separatly between one <tr> tag
	int countHeaderCells = countTagOccurencesBetweenTags(file, "th", "/th", "/tr");
	int countDataCells = countTagOccurencesBetweenTags(file, "td", "/td", "/tr");
	this->cellsCount = countHeaderCells + countDataCells;

	// Filling the cells
	for (int i = 0; i < this->cellsCount; i++)
	{
		this->cells[i].fillCell(file);
	}
}

void Row::printRow(int maxCellsCount, int* maxSymbolsCount)
{
	for (int i = 0; i < this->cellsCount; i++)
	{
		this->cells[i].printCell(maxSymbolsCount[i]);
	}

	int currCellsCount = this->cellsCount;
	while (currCellsCount < maxCellsCount)
	{
		std::cout << "| ";
		printSpaces(maxSymbolsCount[currCellsCount]);
		std::cout << " |";
		currCellsCount++;
	}
}

void Row::addCellsInRow(std::stringstream& values, int valuesCount)
{
	this->cellsCount = valuesCount;
	int cellIndex = 0;

	while (values && cellIndex < valuesCount)
	{
		char value[GlobalConstants::MAX_CELL_SIZE];
		values.getline(value, sizeof(value), ' ');

		// Check if the value is empty or just contains whitespace
		bool isEmptyOrWhitespace = true;
		for (int i = 0; value[i] != '\0'; i++)
		{
			if (value[i] != ' ')
			{
				isEmptyOrWhitespace = false;
				break;
			}
		}

		if (!isEmptyOrWhitespace)
		{
			Cell cell(false, strlen(value), value);
			this->cells[cellIndex] = cell;
			cellIndex++;
		}
	}
}

void Row::editRow(int cellIndex, const char* value)
{
	if (cellIndex < 1 || cellIndex > this->cellsCount)
	{
		std::cerr << "Invalid cell index!" << std::endl;
		return;
	}

	for (int i = 0; i < this->cellsCount; i++)
	{
		if ((cellIndex - 1) == i)
		{
			this->cells[i].setSymbols(value);
			this->cells[i].setSymbolsInCellCount(strlen(value));
		}
	}
}

void Row::clearRow()
{
	for (int i = 0; i < this->cellsCount; i++)
	{
		this->cells[i].setSymbols("\0");
		this->cells[i].setSymbolsInCellCount(0);
	}
	this->cellsCount = 0;
}

void Row::insertRowInFile(std::ofstream& file)
{
	file << "   <tr>" << '\n';
	for (int i = 0; i < cellsCount; i++)
	{
		cells[i].insertCellInFile(file);
	}
	file << "   </tr>" << '\n';
}

// TABLE CLASS
class Table
{
private:
	size_t rowsCount;
	Row rows[GlobalConstants::MAX_ROWS_COUNT];
public:
	Table()
	{
		this->rowsCount = 0;
		for (int i = 0; i < GlobalConstants::MAX_ROWS_COUNT; i++)
			this->rows[i] = Row();
	}

	int getRowsCount() const;

	void fillTable(std::ifstream& file);

	void parseTableFromFile(const char* fileName);

	int getMaxCellsCountInRowInTable();

	int countSymbols(int currColIndex);

	int* fillSymbolsCountArr(int maxCellsCountPerRow);

	void addNewRow(int rowNumber, std::stringstream& values, int valuesCount);

	void editValueInTable(int rowNumber, int colNumber, const char* value);

	void removeRow(int rowNumber);

	void insertTableInFile(const char* fileName);

	void printTable();
};

int Table::getRowsCount() const
{
	return this->rowsCount;
}

void Table::fillTable(std::ifstream& file)
{
	// Counting the <tr> tags in the table
	this->rowsCount = countTagOccurencesBetweenTags(file, "tr", "/tr", "/table");
	file.seekg(0);

	// Filling the rows
	for (int i = 0; i < this->rowsCount; i++)
	{
		this->rows[i].fillRow(file);
		putPointerOnNextRow(file);
	}
}

void Table::parseTableFromFile(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	char currentChar;
	char* tagName = nullptr;

	while (file >> currentChar)
	{

		if (currentChar == '<')
		{
			tagName = getTagName(file, currentChar);
		}

		if (tagName != nullptr && strcmp(tagName, "table") == 0)
		{
			fillTable(file);
		}
	}
}

int Table::getMaxCellsCountInRowInTable()
{
	int countCellsPerRow = 0;

	for (int i = 0; i < this->rowsCount; i++)
	{
		if (this->rows[i].getCellsCount() > countCellsPerRow)
			countCellsPerRow = this->rows[i].getCellsCount();
	}
	return countCellsPerRow;
}

int Table::countSymbols(int currColIndex)
{
	int count = 0;
	for (int i = 0; i < this->rowsCount; i++)
	{
		Cell cell = this->rows[i].getCells()[currColIndex];
		if (count < cell.getSymbolsCount())
			count = cell.getSymbolsCount();
	}
	return count;
}

int* Table::fillSymbolsCountArr(int maxCellsCountPerRow)
{
	int* symbolsCountArr = new int[maxCellsCountPerRow];
	int currCol = 0;
	while (currCol < maxCellsCountPerRow)
	{
		symbolsCountArr[currCol] = countSymbols(currCol);
		currCol++;
	}
	return symbolsCountArr;
}

void Table::addNewRow(int rowNumber, std::stringstream& values, int valuesCount)
{
	if (rowNumber < 1 || rowNumber > this->rowsCount + 1) {
		std::cout << "Invalid row index." << std::endl;
		return;
	}

	// Shift existing rows to make space for the new row
	for (int i = this->rowsCount; i >= rowNumber; i--) {
		this->rows[i] = this->rows[i - 1];
	}

	Row newRow;
	newRow.addCellsInRow(values, valuesCount);

	// Inserting the new row at the specified position
	this->rows[rowNumber - 1] = newRow;
	this->rowsCount++;
}

void Table::editValueInTable(int rowNumber, int colNumber, const char* value)
{
	if (!value)
		return;

	if (rowNumber > this->rowsCount)
	{
		std::cout << "Invalid row index!";
		return;
	}

	for (int i = 0; i < getRowsCount(); i++)
	{
		if ((rowNumber - 1) == i)
		{
			this->rows[i].editRow(colNumber, value);
		}
	}
}

void Table::removeRow(int rowNumber)
{
	if (rowNumber < 1 || rowNumber > this->rowsCount) {
		std::cout << "Invalid row number." << std::endl;
		return;
	}

	for (int i = 0; i < this->rowsCount; i++)
	{
		if ((rowNumber - 1) == i)
		{
			this->rows[i].clearRow();
		}
	}

	for (int i = rowNumber - 1; i < this->rowsCount - 1; i++) {
		this->rows[i] = this->rows[i + 1];
	}

	this->rowsCount--;
}

void Table::insertTableInFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ofstream file(fileName, std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	file << "<table>" << '\n';
	for (int i = 0; i < this->rowsCount; i++)
	{
		this->rows[i].insertRowInFile(file);
	}
	file << "</table>";
}

void Table::printTable()
{
	int maxCellsCountPerRow = getMaxCellsCountInRowInTable();
	int maxSymbolsCountPerCol;
	int* symbolsCountArr = fillSymbolsCountArr(maxCellsCountPerRow);

	for (int i = 0; i < this->rowsCount; i++)
	{
		Row row;
		this->rows[i].printRow(maxCellsCountPerRow, symbolsCountArr);
		std::cout << std::endl;
	}

	delete[] symbolsCountArr;
}

void clearInputBuffer() {
	while (std::cin.get() != '\n') {
		// This does nothing, just consumes characters
	}
}

void getCommandFromUser(Table& table, const char* fileName)
{
	if (!fileName || table.getRowsCount() <= 0)
		return;

	// Getting the command
	bool isFinalCommand = false;

	while (!isFinalCommand)
	{
		std::cout << "Enter a command (add, edit, remove, print, end): ";
		char input[GlobalConstants::MAX_COMMAND_SIZE];
		int rowNumber;

		std::cin.getline(input, sizeof(input));

		char command[GlobalConstants::MAX_COMMAND_SIZE];

		std::stringstream ss(input);
		ss >> command >> rowNumber;

		if (strcmp(command, "add") == 0)
		{
			char valuesBuff[GlobalConstants::MAX_CELLS_COUNT];
			ss.getline(valuesBuff, sizeof(valuesBuff));
			std::stringstream values(valuesBuff);

			// Get values count
			int valuesCount = 0;
			while (values)
			{
				char value[GlobalConstants::MAX_CELL_SIZE];
				values.getline(value, sizeof(value), ' ');
				if (value[0] != '\0')
					valuesCount++;
			}

			// Setting the get pointer to be again at index 0
			values.clear();
			values.seekg(0);

			table.addNewRow(rowNumber, values, valuesCount);
		}
		else if (strcmp(command, "edit") == 0)
		{
			int colNumber;
			char newValue[GlobalConstants::MAX_CELL_SIZE];
			ss >> colNumber >> newValue;

			table.editValueInTable(rowNumber, colNumber, newValue);
		}
		else if (strcmp(command, "remove") == 0)
		{
			table.removeRow(rowNumber);
		}
		else if (strcmp(command, "print") == 0)
		{
			table.printTable();
		}
		else if (strcmp(command, "end") == 0)
			isFinalCommand = true;
	}

	table.insertTableInFile(fileName);
}

int main()
{
	char fileName[GlobalConstants::MAX_FILE_NAME_SIZE];
	std::cout << "Enter file path: ";
	std::cin >> fileName;
	std::cout << std::endl;
	clearInputBuffer();

	Table table;
	table.parseTableFromFile(fileName);
	getCommandFromUser(table, fileName);
}
