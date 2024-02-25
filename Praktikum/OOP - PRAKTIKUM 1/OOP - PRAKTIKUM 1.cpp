#include <iostream>

/*Zad 1*/
// (2 + 5i)(3 + 4i) = 2*3 + 2*4i + 3*5i + 5i*4i
#pragma warning (disable: 4996)

struct ComplexNum
{
    int real;
    int img;
};

void printComplex(const ComplexNum& num)
{
    std::cout << num.real << " + " << num.img << "i" << std::endl;
}

ComplexNum plusComplexNums(const ComplexNum& num1, const ComplexNum& num2)
{
    ComplexNum result;
    result.real = num1.real + num2.real;
    result.img = num1.img + num2.img;
    return result;
}

ComplexNum productComplexNums(const ComplexNum& num1, const ComplexNum& num2)
{
    ComplexNum result;
    result.real = (num1.real * num2.real) + (num1.img * num2.img *  (-1));
    result.img = (num1.real * num2.img) + (num2.real * num1.img);
    return result;
}


/*Zad 2*/
constexpr int BOOK_SIZE = 50;
constexpr int BOOKS_COUNT = 5;

enum class Genre
{
    NOVEL,
    HISTORY,
    POETRY,
    ANOTHER
};

struct Book
{
    char title[BOOK_SIZE];
    char author[BOOK_SIZE];
    Genre genre;
    bool availability;
};

struct Library
{
    unsigned books_count = 0;
    Book books[BOOKS_COUNT];
};

const char* getGenreStr(const Book& book)
{
    switch (book.genre)
    {
    case Genre::NOVEL: return "Novel";
    case Genre::HISTORY: return "History";
    case Genre::POETRY: return "Poetry";
    default: return "Another";
    }
}

void printBook(const Book& book)
{
    std::cout << book.title << " " << book.author << " " << getGenreStr(book) << " " << book.availability << std::endl;
}

Genre getGenreInput()
{
    int input;
    std::cin >> input;

    switch (input)
    {
    case 0: return Genre::NOVEL;
    case 1: return Genre::HISTORY;
    case 2: return Genre::POETRY;
    default: return Genre::ANOTHER;
    }
}

Book createBook()
{
    char title[BOOK_SIZE];
    char author[BOOK_SIZE];
    Genre genre = getGenreInput();
    bool availability;

    std::cin >> title >> author >> availability;

    Book newBook;
    std::strcpy(newBook.title, title);
    std::strcpy(newBook.author, author);
    newBook.genre = genre;
    newBook.availability = availability;

    return newBook;
}

int main()
{
    /*Zad 1
    ComplexNum num1 = { 2, 5 };
    ComplexNum num2 = { 3, 4 };

    ComplexNum resultPlus = plusComplexNums(num1, num2);
    ComplexNum resultProduct = productComplexNums(num1, num2);
    printComplex(resultPlus);
    printComplex(resultProduct);
    */

    /*Zad 2*/
    Book new_book = createBook();
    printBook(new_book);
}
