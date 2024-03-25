#include "group_handler.hpp"

namespace MyTask
{
    bool DataManager::splitGroups() {
        return SplitSubset(groupA, groupB, 0, 0, 0);
    }

    bool DataManager::SplitSubset(std::vector<DataEntry*> &groupA, std::vector<DataEntry*> &groupB,
                                  unsigned int groupACount, unsigned int groupBCount, size_t index)
    {
        if (index >= data.size())
            return false;

        if (groupACount > count || groupBCount > count)
            return false;

        if (groupACount == count && groupBCount == count && abs(getAverageStrength(groupA) - getAverageStrength(groupB)) < defaultStrengthThreshPercent)
            return true;

        groupA.push_back(&data[index]);
        if (SplitSubset(groupA, groupB, groupACount + data[index].getCount(), groupBCount, index + 1))
            return true;

        groupA.pop_back();
        groupB.push_back(&data[index]);

        if (SplitSubset(groupA, groupB, groupACount, groupBCount + data[index].getCount(), index + 1))
            return true;

        groupB.pop_back();

        if (SplitSubset(groupA, groupB, groupACount, groupBCount, index + 1));
            return true;

        return false;
    }

    unsigned int DataManager::getAverageStrength(std::vector<DataEntry*> &group)
    {
        unsigned int sumStrength = 0;
        unsigned int sumCount = 0;

        for (auto data_ptr: group)
        {
            if (!data_ptr)
                break;

            sumCount += data_ptr->getCount();
            sumStrength += data_ptr->getStrength() * data_ptr->getCount();
        }

        if (!sumCount)
            return 0;

        return sumStrength / sumCount;
    }

    void DataManager::Print() {
        std::cout<< "group A" << "\n";
        for (auto data_ptr: groupA)
        {
            std::cout<< (*data_ptr) << "\n";
        }

        std::cout<< "group B" << "\n";
        for (auto data_ptr: groupB)
        {
            std::cout<< (*data_ptr) << "\n";
        }
    }

    std::ostream& operator<<(std::ostream& os, const DataEntry& obj)
    {
        return os << "(" << obj.getId() << "," << obj.getCount() << "," << obj.getStrength() <<")";
    }
}