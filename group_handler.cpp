#include "group_handler.hpp"
#include <cmath>

namespace MyTask
{
    bool DataManager::splitGroups() {
        std::vector<DataEntry*> groupA;
        std::vector<DataEntry*> groupB;
        this->groupA.clear();
        this->groupB.clear();

        SplitSubset(groupA, groupB, 0, 0, 0);

        return (this->groupA.size() > 0 && this->groupB.size() > 0);
    }

    void DataManager::SplitSubset(std::vector<DataEntry*> &groupA, std::vector<DataEntry*> &groupB,
                                  unsigned int groupACount, unsigned int groupBCount, size_t index)
    {
        if (index >= data.size())
            return;

        if (groupACount > count || groupBCount > count)
            return;

        if (groupACount == count && groupBCount == count)
        {
            saveBestGroups(groupA, groupB);
        }

        groupA.push_back(&data[index]);
        SplitSubset(groupA, groupB, groupACount + data[index].getCount(), groupBCount, index + 1);
        groupA.pop_back();

        groupB.push_back(&data[index]);
        SplitSubset(groupA, groupB, groupACount, groupBCount + data[index].getCount(), index + 1);
        groupB.pop_back();

        SplitSubset(groupA, groupB, groupACount, groupBCount, index + 1);
    }

    void DataManager::saveBestGroups(std::vector<DataEntry *> &groupA, std::vector<DataEntry *> &groupB) {
        if (this->groupA.size() == 0 || this->groupB.size() == 0)
        {
            this->groupA = groupA;
            this->groupB = groupB;
        }
        else if (abs(getAverageStrength(groupA) - getAverageStrength(groupB)) <
                 abs(getAverageStrength(DataManager::groupA) - getAverageStrength(this->groupB)))
        {
            this->groupA = groupA;
            this->groupB = groupB;
        }
    }

    void DataManager::saveBestGroups2(std::set<unsigned int> &groupAIndex, std::set<unsigned int> &groupBIndex)
    {
        std::vector<DataEntry *> groupA;
        std::vector<DataEntry *> groupB;

        for (const auto index : groupAIndex)
        {
            groupA.push_back(&data[index]);
        }

        for (const auto index : groupBIndex)
        {
            groupB.push_back(&data[index]);
        }

        saveBestGroups(groupA, groupB);
    }

    bool DataManager::splitGroups2() {
        std::set<unsigned int> groupAIndex;
        std::set<unsigned int> groupBIndex;
        this->groupA.clear();
        this->groupB.clear();

        SplitSubset2(0, 0, groupAIndex, groupBIndex);
        return (this->groupA.size() > 0 && this->groupB.size() > 0);
    }

    void DataManager::SplitSubset2(unsigned int groupACount, unsigned int groupBCount,
                                   std::set<unsigned int> groupAIndex, std::set<unsigned int> groupBIndex)
    {
        if (groupACount == count && groupBCount == count &&
            groupAIndex.size() <= count && groupBIndex.size() <= count)
        {
            saveBestGroups2(groupAIndex, groupBIndex);
            return;
        }

        if (groupACount > count || groupBCount > count ||
            groupAIndex.size() >= count || groupBIndex.size() >= count)
            return;

        if (groupACount < count)
        {
            unsigned int start = groupAIndex.size() ? *groupAIndex.rbegin() + 1 : 0;

            for (auto index = start; index < data.size() ; index++)
            {
                if (groupACount + data[index].getCount() > count)
                    continue;

                groupAIndex.insert(index);
                SplitSubset2(groupACount + data[index].getCount(), groupBCount, groupAIndex, groupBIndex);
                groupAIndex.erase(index);
            }
        }
        else
        {
            unsigned int start = groupBIndex.size() ? *groupBIndex.rbegin() + 1 : 0;
            for (auto index = start; index < data.size() ; index++)
            {
                if (groupAIndex.find(index) != groupAIndex.end())
                {
                    continue;
                }

                if (groupBCount + data[index].getCount() > count)
                    continue;

                groupBIndex.insert(index);
                SplitSubset2(groupACount, groupBCount+ data[index].getCount(), groupAIndex, groupBIndex);
                groupBIndex.erase(index);

            }
        }


    }

    unsigned int DataManager::getAverageStrength(std::vector<DataEntry*> &group)
    {
        unsigned int sumStrength = 0;
        unsigned int sumCount = 0;

        for (const auto data_ptr: group)
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