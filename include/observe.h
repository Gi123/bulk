#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "../include/command.h"

class Observe
{
public:
    virtual void print(const  std::vector<Command>&) = 0;
    virtual ~Observe() = default;
};

class FileObserver: public Observe
{
public:
    FileObserver() {};

private: 
    void print(const std::vector<Command> &commands) override
{
    std::ofstream file;  
    for (auto& command : commands) {
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
        command.Timestamp.time_since_epoch()).count();
        std::stringstream filetime;
        filetime << "bulk" << seconds << ".log";
        std::string path(filetime.str());
        file.open(path);
        file << command.Text << "\n";
    }
    file.close();
}
};

class TerminalObserver: public Observe
{
public:
    TerminalObserver() {};

private: 
    void print(const std::vector<Command> &commands) override
{
    std::cout << "bulk: ";
    bool first = true;
    for (auto& command : commands) {
        if (!first && command.Text.length()) { std::cout << ","; }
        std::cout << command.Text;
        first = false;
    }
    std::cout << std::endl;
}
};

