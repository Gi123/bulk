#pragma once
#include <vector>
#include <sstream>

#include "commandProcessor.h"

class BatchCommandProcessor : public CommandProcessor
{
public:
    BatchCommandProcessor(int bulkSize, CommandProcessor* nextCommandProcessor)
        : CommandProcessor(nextCommandProcessor)
        , mBulkSize(bulkSize)
        , mBlockForced(false)
    {
    }

    ~BatchCommandProcessor()
    {
        if (!mBlockForced)
            DumpBatch();
    }

    void StartBlock() override
    {
        mBlockForced = true;
        DumpBatch();
    }

    void FinishBlock() override
    {
        mBlockForced = false;
        DumpBatch();
    }

    void ProcessCommand(const Command& command) override
    {
        mCommandBatch.push_back(command);

        if (!mBlockForced && mCommandBatch.size() >= mBulkSize)
        {
            DumpBatch();
        }
    }
private:
    /**
     * @brief очистка вектора
     * 
     */
    void ClearBatch()
    {
        mCommandBatch.clear();
    }

    void DumpBatch()
    {
        if (mNextCommandProcessor && !mCommandBatch.empty())
        {
            std::stringstream ss;
            //std::string output = "bulk: " + Join(mCommandBatch);
            for(size_t i = 0; i < mCommandBatch.size(); ++i) {
                if(i != 0)
                    ss << ", ";
                ss << mCommandBatch[i].Text;
            }
            //mNextCommandProcessor->ProcessCommand(Command{output, mCommandBatch[0].Timestamp});
            mNextCommandProcessor->ProcessCommand(Command{ss.str(), mCommandBatch[0].Timestamp});
        }
        ClearBatch();
    }

    // static std::string Join(const std::vector<Command>& v)
    // {
    //     std::stringstream ss;
    //     for(size_t i = 0; i < v.size(); ++i)
    //     {
    //         if(i != 0)
    //             ss << ", ";
    //         ss << v[i].Text;
    //     }
    //     return ss.str();
    // }
    //std::stringstream ss;
    int mBulkSize;
    bool mBlockForced;
    std::vector<Command> mCommandBatch;
};