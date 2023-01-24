#include "../include/bathCommandProcessor.h"
#include "../include/commandProcessor.h"
#include "../include/consoleInput.h"
#include "../include/consoleOutput.h"
#include "../include/reportWriter.h"

#include <iostream>
#include <sstream>
#include <chrono>

void RunBulk(int bulkSize)
{
    ReportWriter reportWriter;
    ConsoleOutput consoleOutput(&reportWriter);
    BatchCommandProcessor batchCommandProcessor(bulkSize, &consoleOutput);
    ConsoleInput consoleInput(&batchCommandProcessor);
    std::string text;
    while (std::getline(std::cin, text))
        consoleInput.ProcessCommand(Command{text, std::chrono::system_clock::now()});
}

int main(int argc, char const** argv)
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Bulk size is not specified." << std::endl;
            return 1;
        }

        int bulkSize = atoi(argv[1]);
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