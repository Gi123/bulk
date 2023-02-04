#pragma once

#include "../include/observe.h"

#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <chrono>

class BatchCommandProcessor
{
public:
    BatchCommandProcessor(int bulkSize)
        :  mBulkSize(bulkSize),
         m_bracket_counter(0),
         counter(0)
    {}
    ~BatchCommandProcessor()
    {
        if (counter)
            notify();
    }
    void notify()
    {
        for (auto& u: m_obs)
        {
            u->print(mCommandBatch);
        }
        mCommandBatch.clear();
    }
    void addComand(const std::string &s) 
    {
         if (std::cin.eof()) { return; }

        /// Начало блока.
        if (s[0] == '{')
        {
            if (counter) {
                notify();
                counter = 0;
            }
            ++m_bracket_counter;
        } /// Конец блока.
        else if (s[0] == '}')
        {
            if (--m_bracket_counter == 0) 
                    notify();
        }
        else {
            mCommandBatch.push_back(Command{s, std::chrono::system_clock::now()});
            ++counter;
            if(counter == mBulkSize) {
                notify();
                counter = 0;
            }
        }
    }
    void subscribe(std::unique_ptr<Observe> &&obs)
    {
        m_obs.emplace_back(std::move(obs));
    }
private:
    int mBulkSize;
    int counter;
    int m_bracket_counter;
    std::vector<Command> mCommandBatch;
    std::vector<std::unique_ptr<Observe>> m_obs;

};