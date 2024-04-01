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

char* getTagName(std::fstream& file, char currentChar)
{
	char buff[GlobalConstants::MAX_BUFFER_SIZE];
	int index = 0;

	//TODO DA GO OPRAVQ
	while (file.get(currentChar) && currentChar != '>')
	{
		buff[index++] = currentChar;
	}
	buff[index] = '\0';

	return buff;
}

int countTagOccurencesBetweenTags(std::fstream& file, const char* openTag, const char* closingTag, const char* endTag)
{
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
	int i = 0, j = 0;
	while (encoded[i]) {
		if (encoded[i] == '&') {
			if (encoded[i + 1] == '#') {
				int code = 0;
				int k = i + 2; // Skips '&#'
				while (encoded[k] >= '0' && encoded[k] <= '9') {
					code = code * 10 + (encoded[k] - '0');
					k++;
				}
				if ((code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z')) {
					decoded[j++] = code;
					i = k; // Updates i to point after the ;
				}
				else {
					// Not a valid letter code, copy the '&' and the following characters
					decoded[j++] = '&';
					i++;
				}
			}
			else {
				// Not a numeric entity reference, copy the '&' and the following characters
				decoded[j++] = '&';
				i++;
			}
		}
		else {
			// Normal character, copy
			decoded[j++] = encoded[i++];
		}
	}
	decoded[j] = '\0';
	return decoded;
}

void putPointerOnNextRow(std::fstream& file)
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

	char* getCellData(std::fstream& file);

	void setSymbols(const char* symbols);

	void setIsHeader(bool isHeader);

	void setSymbolsInCellCount(int count);

	void assignDataToCell(std::fstream& file);

	void fillCell(std::fstream& file);

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

char* Cell::getCellData(std::fstream& file)
{
	char buff[GlobalConstants::MAX_BUFFER_SIZE];
	file.getline(buff, GlobalConstants::MAX_BUFFER_SIZE, '<');
	return buff;
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

void Cell::assignDataToCell(std::fstream& file)
{
	char* cellData = nullptr;
	cellData = getCellData(file);

	strcpy(this->symbols, convertToValidString(cellData));
	this->symbolsInCellCount = strlen(this->symbols);
}

void Cell::fillCell(std::fstream& file)
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

	void fillRow(std::fstream& file);

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

void Row::fillRow(std::fstream& file)
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
			/*this->cells[cellIndex].setSymbols(value);
			this->cells[cellIndex].setIsHeader(false);
			this->cells[cellIndex].setSymbolsInCellCount(strlen(value));*/
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

	void fillTable(std::fstream& file);

	void parseTableFromFile(const char* fileName);

	int getMaxCellsCountInRowInTable();

	int countSymbols(int currColIndex);

	int* fillSymbolsCountArr(int maxCellsCountPerRow);

	void putPointerOnIndex(std::fstream& file, int index,
		const char* openTag, const char* closeTag, const char* endTag);

	void putPointerInsideTag(std::fstream& file, const char* tagName);

	const char* getRemainingContent(std::fstream& file, int currPos);

	void addNewRow(int rowNumber, std::stringstream& values, int valuesCount);

	void editValueInTable(int rowNumber, int colNumber, const char* value);

	void removeRow(int rowNumber);

	void insertRowInFile(const char* fileName, int rowNumber, std::stringstream& values, int valuesCount);

	void editCellInFile(const char* fileName, int rowNumber, int colNumber, const char* value);

	void removeRowInFile(const char* fileName, int rowNumber);

	void insertTableInFile(const char* fileName);

	void printTable();
};

int Table::getRowsCount() const
{
	return this->rowsCount;
}

void Table::fillTable(std::fstream& file)
{
	// Counting the <tr> tags in the table
	int countRows = countTagOccurencesBetweenTags(file, "tr", "/tr", "/table");
	this->rowsCount = countRows;
	file.seekg(0);

	// Filling the rows
	for (int i = 0; i < countRows; i++)
	{
		this->rows[i].fillRow(file);
		putPointerOnNextRow(file);
	}
}

void Table::parseTableFromFile(const char* fileName)
{
	std::fstream file(fileName);

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

void Table::putPointerOnIndex(std::fstream& file, int index,
	const char* openTag, const char* closeTag, const char* endTag)
{
	if (!openTag || !closeTag || !endTag)
		return;

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
				insideTag = true;
			}
			else if (strcmp(currentTagName, closeTag) == 0)
			{
				count++;
				insideTag = false;
			}
			else if (strcmp(currentTagName, endTag) == 0)
			{
				insideTag = false;
				file.seekg(currentPos);
				break;
			}

			if (count == index - 1)
			{
				file.seekg(1, std::ios::cur);
				break;
			}
		}
	}
}

void Table::putPointerInsideTag(std::fstream& file, const char* tagName)
{
	if (!tagName)
		return;

	char currentChar;
	char* currentTagName = nullptr;

	while (file.get(currentChar))
	{
		if (currentChar == '<')
		{
			currentTagName = getTagName(file, currentChar);

			if (strcmp(currentTagName, tagName) == 0)
			{
				file.seekp(0, std::ios::cur);
				break;
			}
		}
	}
}

const char* Table::getRemainingContent(std::fstream& file, int currPos)
{
	// Getting the size of the remaining content, after my insertion
	file.seekg(0, std::ios::end);
	int remainingContentSize = (int)file.tellg() - currPos;
	file.seekg(currPos, std::ios::beg);

	// Reading the remaining content from the file
	char* remainingContent = new char[remainingContentSize + 1];
	int i = 0;
	while (file.get(remainingContent[i]) && i < remainingContentSize) {
		i++;
	}
	remainingContent[i] = '\0';

	// Moving back to the insertion point
	file.clear();
	file.seekg(currPos, std::ios::beg);
	return remainingContent;
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

	if (rowNumber > rowsCount)
	{
		std::cout << "Invalid row index!";
		return;
	}

	for (int i = 0; i < getRowsCount(); i++)
	{
		if ((rowNumber - 1) == i)
		{
			rows[i].editRow(colNumber, value);
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

void Table::insertRowInFile(const char* fileName, int rowNumber, std::stringstream& values, int valuesCount)
{
	std::fstream file(fileName, std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	if (rowNumber > this->rowsCount)
		return;
	else
		putPointerOnIndex(file, rowNumber, "tr", "/tr", "/table");

	int modifiedPointerPos = file.tellg();

	const char* remainingContent = getRemainingContent(file, modifiedPointerPos);

	// Inserting the tags + values
	int cellIndex = 0;
	file << "<tr>" << '\n';
	while (values && cellIndex < valuesCount)
	{
		char value[GlobalConstants::MAX_CELL_SIZE];
		values.getline(value, sizeof(value), ' ');

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
			file << ' ' << ' ' << ' ' << "<td>";
			file << value;
			file << "</td>" << '\n';
			cellIndex++;
		}
	}
	file << "</tr>" << '\n';

	// Appending the remaining content
	file << remainingContent;

	file.clear();
	file.seekg(0);
}

void Table::editCellInFile(const char* fileName, int rowNumber, int colNumber, const char* value)
{
	if (!fileName || !value)
		return;

	std::fstream file(fileName, std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	if (rowNumber > this->rowsCount)
		return;
	else
		putPointerOnIndex(file, rowNumber, "tr", "/tr", "/table");

	if (colNumber > this->rows[rowNumber - 1].getCellsCount())
	{
		std::cerr << "Invalid cell index!";
		return;
	}
	else
		putPointerOnIndex(file, colNumber, "td", "/td", "/tr");

	// Replacing the line with spaces
	file << " ";

	// Inserting the new line
	file << "<td> " << value << " </td>";

	file.clear();
	file.seekg(0);
}

void Table::removeRowInFile(const char* fileName, int rowNumber)
{
	if (!fileName)
		return;

	std::fstream file(fileName, std::ios::in | std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Fail to open file!";
		return;
	}

	if (rowNumber > this->rowsCount)
		return;
	else
		putPointerOnIndex(file, rowNumber, "tr", "/tr", "/table");
	//file << 'S';

	char currentChar;
	char* currentTagName = nullptr;
	bool insideTag = false;

	while (file.get(currentChar))
	{
		currentTagName = getTagName(file, currentChar);
		file << " ";
		if (strcmp(currentTagName, "/tr"))
		{
			file << " ";
			return;
		}
		//std::cout << currentTagName << std::endl;
	}
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
	for (int i = 0; i < rowsCount; i++)
	{
		rows[i].insertRowInFile(file);
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
	if (!fileName)
		return;

	// Getting the command
	bool isFinalCommand = false;

	while (!isFinalCommand)
	{
		std::cout << "Enter a command (add, edit, remove, print): ";
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
			values.clear();
			values.seekg(0);

			//table.insertRowInFile(fileName, rowNumber, values, valuesCount);
		}
		else if (strcmp(command, "edit") == 0)
		{
			int colNumber;
			char newValue[GlobalConstants::MAX_CELL_SIZE];
			ss >> colNumber >> newValue;

			table.editValueInTable(rowNumber, colNumber, newValue);
			//table.editCellInFile(fileName, rowNumber, colNumber, newValue);
		}
		else if (strcmp(command, "remove") == 0)
		{
			table.removeRow(rowNumber);
			//table.removeRowInFile(fileName, rowNumber);
		}
		else if (strcmp(command, "print") == 0)
		{
			table.printTable();
			isFinalCommand = true;
		}
	}

	table.insertTableInFile(fileName);
}

int main()
{
	char fileName[GlobalConstants::MAX_FILE_NAME_SIZE];
	/*std::cout << "Enter file path: ";
	std::cin >> fileName;
	std::cout << std::endl;
	clearInputBuffer();*/
	strcpy(fileName, "htmlFile3.txt");

	Table table;
	table.parseTableFromFile(fileName);
	getCommandFromUser(table, fileName);
}
