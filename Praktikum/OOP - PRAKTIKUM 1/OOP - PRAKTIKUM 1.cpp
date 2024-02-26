#include <iostream>
#include <assert.h>

/*Zad 1*/
// (2 + 5i)(3 + 4i) = 2*3 + 2*4i + 3*5i + 5i*4i

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
constexpr int BOOKS_COUNT = 10;

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
    std::cout << "Title: " << book.title << "\nAuthor: " << book.author << "\nGenre: " << getGenreStr(book) << "\nAvailability: " << book.availability << std::endl;
}

void printLibrary(const Library& library)
{
    std::cout << "Books count: " << library.books_count << std::endl;
    for (int i = 0; i < library.books_count; i++)
    {
        printBook(library.books[i]);
        std::cout << std::endl;
    }
}

bool isInLibrary(const char* title, const Library& library)
{
    if (!title)
    {
        return false;
    }

    for (int i = 0; i < library.books_count; i++)
    {
        if (std::strcmp(title, library.books[i].title) == 0)
        {
            return true;
        }
    }
    return false;
}

int getBookIndex(const char* title, const Library& library)
{
    if (!title)
    {
        return -1;
    }

    for (int i = 0; i < library.books_count; i++)
    {
        if (std::strcmp(title, library.books[i].title) == 0)
        {
            return i;
        }
    }
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
    strcpy_s(newBook.title, title);
    strcpy_s(newBook.author, author);
    newBook.genre = genre;
    newBook.availability = availability;

    return newBook;
}

Library addBookToLibrary()
{
    Library library;
    int numberOfBooks;
    std::cout << "Enter the number of books you want to add: ";
    std::cin >> numberOfBooks;

    assert(numberOfBooks < BOOKS_COUNT - library.books_count);
    while (numberOfBooks && numberOfBooks < BOOKS_COUNT - library.books_count)
    {
        Book book = createBook();
        if (!isInLibrary(book.title, library))
        {
            library.books[library.books_count] = book;
            library.books_count++;
        }
        numberOfBooks--;
    }

    return library;
}

void getBookFromLibrary(Library& library)
{
    char title[BOOK_SIZE];
    std::cin >> title;
    int index = 0;

    if (isInLibrary(title, library))
        index = getBookIndex(title, library);
    else
        assert(isInLibrary(title, library));

    Book currentBook = library.books[index];

    if (currentBook.availability == 1)
    {
        currentBook.availability = 0;
        library.books_count--;
        std::cout << title << " has been taken from library successfuly!";
    }
    else
        std::cout << "Book is not in library!";
}

void returnBook(Library& library)
{
    char title[BOOK_SIZE];
    std::cin >> title;
    int index;

    if (isInLibrary(title, library))
        index = getBookIndex(title, library);
    else
        assert(isInLibrary(title, library));

    Book currentBook = library.books[index];
    if (currentBook.availability == 0)
    {
        currentBook.availability = 1;
        library.books_count++;
        std::cout << title << " has been returned to library successfuly!";
    }
    else
        std::cout << "Book is already in library!";
}

/*Zad 3*/
enum class Course
{
    FIRST = 1,
    SECOND,
    THIRD,
    FOURTH
};

struct Student
{
    unsigned fn;
    Course course;
    double grade;
};

Course getCourse()
{
    int course;
    std::cin >> course;

    switch (course)
    {
    case 1: return Course::FIRST;
    case 2: return Course::SECOND;
    case 3: return Course::THIRD;
    case 4: return Course::FOURTH;
    default: break;
    }
}

const char* getCourseStr(const Student& student)
{
    switch (student.course)
    {
    case Course::FIRST: return "First course";
    case Course::SECOND: return "Second course";
    case Course::THIRD: return "Third course";
    case Course::FOURTH: return "Fourth course";
    default: return "This student doesn't have a course.";
    }
}

Student initStudent()
{
    Student student;
    unsigned fn;
    double grade;

    do
    {
        std::cin >> fn;
    } while (fn < 10000 || fn > 99999);

    std::cin >> grade;

    student.fn = fn;
    student.grade = grade;
    student.course = getCourse();

    return student;
}

void printStudent(const Student& student)
{
    std::cout << "Fn: " << student.fn << "\n Course: " << getCourseStr(student) << "\n Course grade: " << student.grade;
}

/*Zad 4*/
constexpr int MAX_STUDENTS_COUNT = 20;
struct Group
{
    int studentsCount = 0;
    Student students[MAX_STUDENTS_COUNT];
    double averageGrade;
};

bool isStudentInGroup(unsigned fn, const Group& group)
{
    for (int i = 0; i < group.studentsCount; i++)
    {
        if (fn == group.students[i].fn)
            return true;
    }
    return false;
}

Group createGroup()
{
    double sum = 0;

    Group newGroup;
    int studentsCount;
    std::cout << "Enter the number of students in this group: ";
    std::cin >> studentsCount;

    assert(studentsCount < MAX_STUDENTS_COUNT - newGroup.studentsCount);

    while (studentsCount && studentsCount < MAX_STUDENTS_COUNT - newGroup.studentsCount)
    {
        Student student = initStudent();
        if (!isStudentInGroup(student.fn, newGroup))
        {
            newGroup.students[newGroup.studentsCount] = student;
            newGroup.studentsCount++;
            sum += student.grade;
        }
        studentsCount--;
    }

    newGroup.averageGrade = sum / newGroup.studentsCount;
    return newGroup;
}

void printGroup(const Group& group)
{
    for (int i = 0; i < group.studentsCount; i++)
    {
        printStudent(group.students[i]);
        std::cout << std::endl;
    }
    std::cout << "Average Grade: " << group.averageGrade << std::endl;
    std::cout << "Total: " << group.studentsCount;
}

int countScolarships(const Group& group, double minGrade)
{
    const int MIN_REST = 0.0001;
    int scolarshipsCount = 0;
    for (int i = 0; i < group.studentsCount; i++)
    {
        if (group.students[i].grade > minGrade || (fabs(minGrade - group.students[i].grade) < MIN_REST))
            scolarshipsCount++;
    }

    return scolarshipsCount;
}

/*Zad 5*/
void sortGroupByGrade( Group& group)
{
    for (int i = 0; i < group.studentsCount; i++)
    {
        int minIndex = i;

        for (int j = 1; j < group.studentsCount; j++)
        {
            if (group.students[j].grade > group.students[minIndex].grade)
            {
                minIndex = j;
            }
        }

        if (i != minIndex)
        {
            std::swap(group.students[i], group.students[minIndex]);
        }
    }
}

void getAllStudentsWithScolarships(const Group& group, double minGrade)
{
    for (int i = 0; i < group.studentsCount; i++)
    {
        if (group.students[i].grade >= minGrade)
        {
            printStudent(group.students[i]);
            std::cout << std::endl;
        }
    }
}

/*Zad 6 - Test simulation */
constexpr int TITLE_MAX_SIZE = 50;
constexpr int ANSWERS_COUNT = 4;
constexpr int QUESTIONS_COUNT = 3;

enum class AnswerLetters
{
    A = 1,
    B,
    C,
    D
};

struct Answer
{
    char A[TITLE_MAX_SIZE];
    char B[TITLE_MAX_SIZE];
    char C[TITLE_MAX_SIZE];
    char D[TITLE_MAX_SIZE];
};

struct Question
{
    char title[TITLE_MAX_SIZE];
    Answer answer;
    AnswerLetters correctAnswer;
    int points;
};

struct Test
{
    int questionsCount = QUESTIONS_COUNT;
    Question questions[QUESTIONS_COUNT];
};

AnswerLetters getCorrectAnswer(const Question& question)
{
    int guess;
    std::cout << "Provide an answer to this question: ";
    std::cin >> guess;

    switch (guess)
    {
    case 1: return AnswerLetters::A;
    case 2: return AnswerLetters::B;
    case 3: return AnswerLetters::C;
    case 4: return AnswerLetters::D;
    }
}

Answer createAnswer()
{
    Answer answer;
    std::cin >> answer.A >> answer.B >> answer.C >> answer.D;
    return answer;
}

Question createQuestion()
{
    Question question;
    std::cout << "Question title: ";
    std::cin >> question.title;

    std::cout << "Question answers: ";
    std::cin >> question.answer.A  >> question.answer.B >> question.answer.C >> question.answer.D;

    question.correctAnswer = getCorrectAnswer(question);

    std::cout << "Enter points for this question: ";
    std::cin >> question.points;

    return question;
}

Test createTest()
{
    Test test;
    for (int i = 0; i < test.questionsCount; i++)
    {
        test.questions[i] = createQuestion();
    }

    return test;
}

void printAnswers(const Answer& answer)
{
    std::cout << answer.A << std::endl;
    std::cout << answer.B << std::endl;
    std::cout << answer.C << std::endl;
    std::cout << answer.D << std::endl;
}

const char* getCorrectAnswerStr(const Question& question)
{
    switch (question.correctAnswer)
    {
    case AnswerLetters::A: return "A is the correct answer!";
    case AnswerLetters::B: return "B is the correct answer!";
    case AnswerLetters::C: return "C is the correct answer!";
    case AnswerLetters::D: return "D is the correct answer!";
    default: return "You have not given a valid answer to this question.";
    }
}

void printQuestion(const Question& question)
{
    std::cout << "Title: " << question.title << std::endl;

    std::cout << "Answers: " << std::endl;
    std::cout << "A: " << question.answer.A << "\nB: " << question.answer.B << "\nC: " << question.answer.C << "\nD: " << question.answer.D << std::endl;

    /*std::cout << "Correct answer (1 - 4): " << getCorrectAnswerStr(question);
    std::cout << std::endl;*/

    std::cout << "Points you gain: " << question.points << std::endl;
}

void printTest(const Test& test)
{
    std::cout << "Questions count: " << test.questionsCount << std::endl;
    for (int i = 0; i < test.questionsCount; i++)
    {
        printQuestion(test.questions[i]);
        std::cout << std::endl;
    }
}

int doTest(const Test& test)
{
    std::cout << "START TEST!" << std::endl;
    AnswerLetters userAnswer;
    int totalPoints = 0;

    for (int i = 0; i < test.questionsCount; i++)
    {
        std::cout << "Give an answer to question " << i << ". (1-4): ";
        userAnswer = getCorrectAnswer(test.questions[i]);

        if (userAnswer == test.questions[i].correctAnswer)
        {
            totalPoints += test.questions[i].points;
        }
    }
    return totalPoints;
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
    /*Create a new book
    Book new_book = createBook();
    printBook(new_book);*/

    /*Add a new non-existing book in library
    Library library = addBookToLibrary();
    printLibrary(library);*/

    /*Get a book based on an author
    getBookFromLibrary(library);*/

    /*Return a book based on an author
    returnBook(library);*/

    /*Zad 3
    Student newStudent = initStudent();
    printStudent(newStudent);*/

    double minScolarshipGrade = 4;
    /*Zad 4
    Group group = createGroup();
    printGroup(group);
    std::cout << std::endl << "Scolarships count: " << countScolarships(group, minScolarshipGrade);*/

    /*Zad 5
    Group group = createGroup();
    sortGroupByGrade(group);
    getAllStudentsWithScolarships(group, minScolarshipGrade);*/

    /*Zad 6
    Test test = createTest();
    printTest(test);
    std::cout << "Yout total points are: " << doTest(test);*/
}
