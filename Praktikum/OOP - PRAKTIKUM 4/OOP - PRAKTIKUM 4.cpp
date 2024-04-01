#include <iostream>
#include <fstream>
#pragma warning (disable:4996)


/*Zad 1*/
struct User
{
    char name[25]{};
};

struct Message
{
    User from;
    char* text;
};

Message createMessage(const char* userName, const char* text)
{
    Message message;
    User user;

    strcpy(user.name, userName);

    message.from = user;
    strcpy(message.text, text);

    return message;
}

void initMessage(Message* messages)
{
    messages[0] = createMessage("vasi", "hi");
    messages[1] = createMessage("eli", "hellloo");
    messages[2] = createMessage("stela", "love");
}

void saveMessageInFile(const char* fileName, const Message* messages, size_t size)
{
    std::ofstream file(fileName, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Fail to open file!";
        return;
    }

    file.write((const char*)messages, sizeof(Message) * size);
}

size_t getFileSize(std::ifstream& file)
{
    int currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(currentPos);

    return size;
}


void printChat(const char* fileName)
{
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Fail to open file!";
        return;
    }

    size_t fileSize = getFileSize(file);


}

int main()
{
	/*Zad 1*/
    const char fileName[20] = "chat_zad1.txt";

    constexpr int SIZE = 3;
    Message messages[SIZE];

    initMessage(messages);
    saveMessageInFile(fileName, messages, SIZE);
    printChat(fileName);
}

