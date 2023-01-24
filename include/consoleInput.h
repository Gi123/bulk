#pragma once
#include "commandProcessor.h"

/**
 * @brief Класс ConsoleInput
 * 
 */

class ConsoleInput : public CommandProcessor
{
public:
    /**
     * @brief конструктор CommandProcessor
     * 
     * @tparam nextCommandProcessor - команда
     */
    ConsoleInput(CommandProcessor* nextCommandProcessor = nullptr)
        : CommandProcessor(nextCommandProcessor)
        , mBlockDepth(0)
    {
    }

    void ProcessCommand(const Command& command) override
    {
        if (mNextCommandProcessor)
        {
            /// Начало блока.
            if (command.Text == "{")
            {
                if (mBlockDepth++ == 0)
                    mNextCommandProcessor->StartBlock();
            } /// Конец блока.
            else if (command.Text == "}")
            {
                if (--mBlockDepth == 0)
                    mNextCommandProcessor->FinishBlock();
            }
            else
                mNextCommandProcessor->ProcessCommand(command);
        }
    }

private:
    int mBlockDepth;
};
