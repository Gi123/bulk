#pragma once
#include "commandProcessor.h"

#include <iostream>

/**
 * @brief Класс ConsoleOutput
 * 
 */

class ConsoleOutput : public CommandProcessor
{
public:
    ConsoleOutput(CommandProcessor* nextCommandProcessor = nullptr)
        : CommandProcessor(nextCommandProcessor)
    {
    }
    /**
     * @brief функция печати команды
     *  @tparam command - команда
     */
    void ProcessCommand(const Command& command) override
    {
        std::cout << command.Text << std::endl;

        if (mNextCommandProcessor)
            mNextCommandProcessor->ProcessCommand(command);
    }
};
