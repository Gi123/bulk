#include "../include/bathCommandProcessor.h"
#include "../include/command.h"

#include <iostream>
#include <sstream>

void RunBulk(int bulkSize)
{
    BatchCommandProcessor batchCommandProcessor(bulkSize);
    batchCommandProcessor.subscribe(std::make_unique<FileObserver>());
    batchCommandProcessor.subscribe(std::make_unique<TerminalObserver>());
    std::string text;
    while (std::getline(std::cin, text)) 
        batchCommandProcessor.addComand(text);
}

int main(int argc, char const** argv)
{
    argc = 2;
    try
    {
        if (argc < 2)
        {
            std::cerr << "Bulk size is not specified." << std::endl;
            return 1;
        }

        int bulkSize = atoi(argv[1]);
        bulkSize = 3;
        if (bulkSize == 0)
        {
            std::cerr << "Invalid bulk size." << std::endl;
            return 1;
        }

        RunBulk(bulkSize);
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}