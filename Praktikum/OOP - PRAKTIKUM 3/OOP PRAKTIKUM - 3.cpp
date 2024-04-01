#include <iostream>
#include <fstream>
#include <sstream>

/*Zad 1*/
const char ROWS_SEPARATOR = '|';
const char COLS_SEPARATOR = ',';
constexpr int MAX_BUFF_SIZE = 1024;

unsigned countRows(std::ifstream& file)
{
	unsigned count = 0;
	char separator;

	while (file.get(separator))
	{
		if (separator == ROWS_SEPARATOR)
			count++;

		if (file.eof())
		{
			file.clear();
			file.seekg(0);
			return count + 1;
		}
	}

	file.clear();

	file.seekg(0);

	return count + 1;
}

unsigned countCols(std::ifstream& file)
{
	unsigned count = 0;
	char buff = '\0';

	while (buff != ROWS_SEPARATOR)
	{
		file.get(buff);
		if (buff == COLS_SEPARATOR)
			count++;
	}

	file.clear();

	file.seekg(0);


	return count + 1;
}

int** createMatrix(int rows, int cols)
{
	int** mtx = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		mtx[i] = new int[cols] {0};
	}
	return mtx;
}

void freeMatrix(int** matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void print(int** mtx, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << mtx[i][j] << ' ';
		std::cout << std::endl;
	}
}

void fillMatrices(std::ifstream& file, int**& matrix, int rowsCount, int colsCount)
{
	for (int i = 0; i < rowsCount; i++)
	{
		char buff[MAX_BUFF_SIZE];
		file.getline(buff, MAX_BUFF_SIZE, ROWS_SEPARATOR);

		std::stringstream ss;
		ss << buff;

		//std::cout <<  "buff" << buff << std::endl;

		for (int j = 0; j < colsCount; j++)
		{
			char buffChar[MAX_BUFF_SIZE];
			ss.getline(buffChar, MAX_BUFF_SIZE, COLS_SEPARATOR);

			//std::cout << "buffchar" << buffChar[0] << std::endl;
			matrix[i][j] = buffChar[0] - '0';
			//std::cout <<  "matrix" << matrix[i][j] << std::endl;
		}
	}

	file.clear();

	file.seekg(0);
}

void getProductOfMatrices(int** firstMatrix, int** secondMatrix, int**& productMatrix,
	int rowsCountFirst, int rowsColsCount, int colsCountSecond)
{
	for (int i = 0; i < rowsCountFirst; i++)
	{
		for (int j = 0; j < colsCountSecond; j++)
		{
			for (int k = 0; k < rowsColsCount; k++)
			{
				productMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
}

void saveMatrixInFile(const char* fileName, int** matrix, int rowsCount, int colsCount)
{
	std::ofstream file("productMatrix.txt");

	if (!file.is_open())
	{
		std::cerr << "Failed to open file!";
		return;
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			file << matrix[i][j];

			if (j < colsCount - 1)
				file << ',';
		}

		if(i < rowsCount - 1)
			file << '|';
	}

}

/*Zad 2*/
namespace GLOBAL_CONSTANTS
{
	constexpr int MAX_NAME_SIZE = 100;
	constexpr int MAX_CATEGORIES_PRODUCTS_COUNT = 100;
}

enum class Category
{
	ELECTRONICS, 
	CLOTHING, 
	BOOKS, 
	FOOD,
	BEAUTY
};

struct Product
{
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
	unsigned quantity;
	double cost;
	Category category;
	char deliverer[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
};

size_t getFileSize(std::fstream& f) {
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void initProduct(Product& product)
{
	// A function for only the first point from the task
	strcpy_s(product.name, "Laptop");
	product.quantity = 333;
	product.cost = 678.34;
	product.category = Category::ELECTRONICS;
	strcpy_s(product.deliverer, "Most Computers");
}

Category getCategoryInput()
{
	int input;
	std::cin >> input;

	switch (input)
	{
	case 0: return Category::ELECTRONICS;
	case 1: return Category::CLOTHING;
	case 2: return Category::BOOKS;
	case 3: return Category::FOOD;
	case 4: return Category::BEAUTY;
	default: return Category::ELECTRONICS;
	}
}

const char* readProductCategory(const Product& product)
{
	switch (product.category)
	{
	case Category::ELECTRONICS: return "Electronics";
	case Category::CLOTHING: return "Clothing";
	case Category::BOOKS: return "Books";
	case Category::FOOD: return "Food";
	case Category::BEAUTY: return "Beauty";
	default: return "No category";
	}
}

void printProduct(const Product& product)
{
	std::cout << "Name: " << product.name << "\nQuantity: " << product.quantity << "\nCost: " << product.cost << "\nCategory: " << readProductCategory(product)
		<< "\nDeliverer: " << product.deliverer << std::endl;
}

Product* readProductFromConsole(int& productsToInsertCount)
{
	std::cout << "Number of products to insert: " << std::endl;
	std::cin >> productsToInsertCount;

	Product* products = new Product[productsToInsertCount];

	for (int i = 0; i < productsToInsertCount; i++)
	{
		Product product;

		std::cout << "Name: " << std::endl;
		std::cin >> product.name;
		std::cout << "Quantity: " << std::endl;
		std::cin >> product.quantity;
		std::cout << "Cost: " << std::endl;
		std::cin >> product.cost;
		std::cout << "Category: " << std::endl;
		product.category = getCategoryInput();
		std::cout << "Deliverer: " << std::endl;
		std::cin >> product.deliverer;

		products[i] = product;
	}

	return products;
}

Product* readProductsFromFile(std::fstream& file, const Product& product, int& countProductsInFile)
{
	file.seekp(0, std::ios::beg);

	size_t fileSize = getFileSize(file);
	countProductsInFile = fileSize / sizeof(product);

	//std::cout << "count: " << countProductsInFile;

	Product* products = new Product[countProductsInFile];
	file.read((char*)products, fileSize);

	file.clear();
	file.seekg(0);

	return products;
}

bool checkIfFileContainsProduct(std::fstream& file,const Product& product)
{
	int countProductsInFile;

	Product* products = readProductsFromFile(file, product, countProductsInFile);

	for (int i = 0; i < countProductsInFile; i++)
	{
		if (strcmp(products[i].name, product.name) == 0)
			return true;
	}

	return false;
}

void printAllProductsInFile(std::fstream& file)
{
	int count;
	Product product;
	Product* products = readProductsFromFile(file, product, count);

	for (int i = 0; i < count; i++)
	{
		std::cout << "Product no." << i << std::endl;
		printProduct(products[i]);
		std::cout << std::endl;
	}
}

void saveProductInFile(const char* fileName, Product& product)
{
	std::fstream file(fileName, std::ios::out | std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Error while writing to binary file!" << std::endl;
		return;
	}

	/*std::cout << "Before" << std::endl;
	printAllProductsInFile(file);*/

	int productsToInsertCount;
	Product* products = readProductFromConsole(productsToInsertCount);


	for (int i = 0; i < productsToInsertCount; i++)
	{
		if (!checkIfFileContainsProduct(file, products[i]))
		{
			//std::cout << "NOT EQUAL PRODUCT";
			//printProduct(products[i]);

			file.seekp(0, std::ios::end);
			file.write((const char*)&products[i], sizeof(product));
		}
		else
			std::cout << "The product with name: " << products[i].name << " already exists!";
	}

	/*std::cout << "After" << std::endl;
	printAllProductsInFile(file);*/

	file.clear();
	file.seekp(0);
	delete[] products;
}

void getProductFromFileByName(const char* fileName,const Product& product)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening file!" << std::endl;
		return;
	}

	printAllProductsInFile(file);

	int countProductsInFile;
	char name[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
	std::cout << "Enter a product name to search for: ";
	std::cin >> name;

	Product* products = readProductsFromFile(file, product, countProductsInFile);
	for (int i = 0; i < countProductsInFile; i++)
	{
		if (strcmp(products[i].name, name) == 0)
		{
			printProduct(products[i]);
			return;
		}
	}
	std::cout << "Product with the name " << name << " could not be found!" << std::endl;
}

void editProductQuantity(const char* fileName, const Product& product)
{
	std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening file!" << std::endl;
		return;
	}

	int productsCount;
	unsigned newQuantity;
	char productName[GLOBAL_CONSTANTS::MAX_NAME_SIZE];
	int productIndex = -1;
	std::cout << "Enter the name of the product you want to edit: ";
	std::cin >> productName;
	
	Product* products = readProductsFromFile(file, product, productsCount);

	for (int i = 0; i < productsCount; i++)
	{
		if (strcmp(products[i].name, productName) == 0)
		{
			productIndex = i;
			break;
		}
	}

	if (productIndex == -1)
	{
		std::cout << "The product with name " << productName << " could not be found!" << std::endl;
		return;
	}

	std::cout << "Enter a new quantity value: ";
	std::cin >> newQuantity;
	Product modifiedProduct;

	file.seekg(productIndex * sizeof(product));
	file.read((char*)&modifiedProduct, sizeof(product));

	modifiedProduct.quantity = newQuantity;

	file.seekg(productIndex * sizeof(product));
	file.write((const char*)&modifiedProduct, sizeof(product));
	printAllProductsInFile(file);
}

void sortProductsBasedOnCategoryInNewFile(const char* sourcefileName, const Product& product, const char* destFileName)
{
	std::fstream fileSource(sourcefileName, std::ios::in | std::ios::binary);
	std::fstream fileDest(destFileName, std::ios::in | std::ios::out | std::ios::binary);

	if (!fileSource.is_open() || !fileDest.is_open()) {
		std::cout << "Error while opening files!" << std::endl;
		return;
	}

	int productsCount;
	int categoryIndex;
	std::cout << "Enter a category index to sort by (0-4): ";
	std::cin >> categoryIndex;

	if (categoryIndex < 0 || categoryIndex > 4)
	{
		std::cout << "No category with index " << categoryIndex << " found!" << std::endl;
		return;
	}

	Product* products = readProductsFromFile(fileSource, product, productsCount);


	Product productsFromCategory[GLOBAL_CONSTANTS::MAX_CATEGORIES_PRODUCTS_COUNT];
	int productsFromCategoryCount = 0;

	for (int i = 0; i < productsCount; i++)
	{
		if ((int)products[i].category == categoryIndex)
			productsFromCategory[productsFromCategoryCount++] = products[i];
	}

	for (int i = 0; i < productsFromCategoryCount; i++)
	{
		//printProduct(productsFromCategory[i]);
		//std::cout << std::endl;
		fileDest.write((const char*)&productsFromCategory[i], sizeof(Product));
	}

	fileDest.clear();
	fileDest.seekg(0);

	printAllProductsInFile(fileDest);
}

int main()
{
	/*Zad 1
	std::ifstream firstMatrixFile("firstMatrix.txt");
	std::ifstream secondMatrixFile("secondMatrix.txt");

	if (!firstMatrixFile.is_open() || !secondMatrixFile.is_open())
	{
		std::cerr << "Failed to open file!";
		return -1;
	}

	int rowsCountFirst = countRows(firstMatrixFile);
	int rowsCountSecond = countRows(secondMatrixFile);

	int colsCountFirst = countCols(firstMatrixFile);
	int colsCountSecond = countCols(secondMatrixFile);

	int** firstMatrix = createMatrix(rowsCountFirst, colsCountFirst);
	int** secondMatrix = createMatrix(rowsCountSecond, colsCountSecond);
	int** productMatrix = createMatrix(rowsCountFirst, colsCountSecond);

	fillMatrices(firstMatrixFile, firstMatrix, rowsCountFirst, colsCountFirst);
	fillMatrices(secondMatrixFile, secondMatrix, rowsCountSecond, colsCountSecond);

	//print(firstMatrix, rowsCountFirst, colsCountFirst);
	//print(secondMatrix, rowsCountSecond, colsCountSecond);

	getProductOfMatrices(firstMatrix, secondMatrix, productMatrix, rowsCountFirst, 
		rowsCountSecond, colsCountSecond);

	//print(productMatrix, rowsCountFirst, colsCountSecond);

	saveMatrixInFile("productMatrix.txt", productMatrix, rowsCountFirst, colsCountSecond);

	freeMatrix(firstMatrix, rowsCountFirst);
	freeMatrix(secondMatrix, rowsCountSecond);
	freeMatrix(productMatrix, rowsCountFirst);*/

	/*Zad 2*/
	const char fileName[GLOBAL_CONSTANTS::MAX_NAME_SIZE] = "products_zad2.txt";

	Product product;
	/*initProduct(product);
	saveProductInFile(fileName, product);
	readProductFromFile(fileName, product);*/

	//saveProductInFile(fileName, product);
	//getProductFromFileByName(fileName, product);
	//editProductQuantity(fileName, product);
	//sortProductsBasedOnCategoryInNewFile(fileName, product, "productsBasedOnCategory_zad2.txt");
}
