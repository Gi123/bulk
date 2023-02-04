#pragma once
#include <chrono>
#include <iostream>

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