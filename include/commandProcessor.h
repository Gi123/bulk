#pragma once
#include <chrono>

/**
 * @brief структура Command
 * 
 * @tparam Text - название команды
 * @tparam Timestamp - время команды 
 */
struct Command
{
    std::string Text;
    std::chrono::system_clock::time_point Timestamp;
};
/**
 * @brief Интерфейс CommandProcessor
 * 
 */
class CommandProcessor
{
public:
    /**
     * @brief конструктор CommandProcessor
     * 
     * @tparam nextCommandProcessor - команда
     */
    CommandProcessor(CommandProcessor* nextCommandProcessor = nullptr)
        : mNextCommandProcessor(nextCommandProcessor)
    {
    }
    /**
     * @brief деструктор CommandProcessor
     */
    virtual ~CommandProcessor() = default;
    /**
     * @brief функция для определения начала блока, который нужно игнорировать
     */
    virtual void StartBlock() {}
    /**
     * @brief функция для определения конца блока, который нужно игнорировать
     */
    virtual void FinishBlock() {}

    virtual void ProcessCommand(const Command& command) = 0;

protected:
    CommandProcessor* mNextCommandProcessor;
};