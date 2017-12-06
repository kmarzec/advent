#pragma once

#include <unordered_map>


typedef std::vector<int> MemStateType;


struct MemStateTypeHash {
    size_t operator()(const MemStateType& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};



MemStateType ReallocateBanks(const MemStateType state)
{
    MemStateType newState = state;

    int bankIdx = 0;
    for (MemStateType::size_type i = 1; i < newState.size(); ++i)
    {
        if (newState[i] > newState[bankIdx])
        {
            bankIdx = i;
        }
    }

    int numBlocksToReallocate = newState[bankIdx];
    newState[bankIdx] = 0;

    while (numBlocksToReallocate > 0)
    {
        bankIdx = (bankIdx + 1) % newState.size();
        newState[bankIdx]++;
        numBlocksToReallocate--;
    }

    return newState;
}


void ReallocateUntilRepeats(const std::string& task, const std::string input)
{
    MemStateType currentState;

    int numBanks = 0;
    std::stringstream inputStream(input);
    while (!inputStream.eof())
    {
        inputStream >> numBanks;
        currentState.push_back(numBanks);
    }

    std::unordered_map<MemStateType, int, MemStateTypeHash> prevStates;

    int cycleIdx = 0;
    
    auto it = prevStates.end();
    while((it = prevStates.find(currentState)) == prevStates.end())
    {
        prevStates[currentState] = cycleIdx;
        currentState = ReallocateBanks(currentState);
        cycleIdx++;
    }

    int loopSize = cycleIdx - it->second;

    PrintDbg("Day6_1 %s: cycles: %d, loop: %d\n", task.c_str(), cycleIdx, loopSize);
}


void Day6()
{
    std::string input = "14	0	15	12	11	11	3	5	1	6	8	4	9	1	8	4";

    ReallocateUntilRepeats("sample", "0 2 7 0");
    ReallocateUntilRepeats("puzzle", input);
}