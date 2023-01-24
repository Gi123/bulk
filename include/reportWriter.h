#pragma once
#include <fstream>

#include "commandProcessor.h"

class ReportWriter : public CommandProcessor
{
public:
    ReportWriter(CommandProcessor* nextCommandProcessor = nullptr)
        : CommandProcessor(nextCommandProcessor)
    {
    }
    /**
     * @brief функция запись в файл
     *  @tparam command - команда
     */
    void ProcessCommand(const Command& command) override
    {
        std::ofstream file(GetFilename(command), std::ofstream::out);
        file << command.Text;

        if (mNextCommandProcessor)
            mNextCommandProcessor->ProcessCommand(command);
    }

private:
    /**
     * @brief создание файла
     * @tparam command - команда
     */
    std::string GetFilename(const Command& command)
    {
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
        command.Timestamp.time_since_epoch()).count();
        std::stringstream filename;
        filename << "bulk" << seconds << ".log";
        return filename.str();
    }
};