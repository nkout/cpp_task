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
            if (this->groupA.size() == 0 || this->groupB.size() == 0)
            {
                this->groupA = groupA;
                this->groupB = groupB;
            }
            else if (abs(getAverageStrength(groupA) - getAverageStrength(groupB)) <
                    abs(getAverageStrength(this->groupA) - getAverageStrength(this->groupB)))
            {
                this->groupA = groupA;
                this->groupB = groupB;
            }
        }

        groupA.push_back(&data[index]);
        SplitSubset(groupA, groupB, groupACount + data[index].getCount(), groupBCount, index + 1);
        groupA.pop_back();

        groupB.push_back(&data[index]);
        SplitSubset(groupA, groupB, groupACount, groupBCount + data[index].getCount(), index + 1);
        groupB.pop_back();

        SplitSubset(groupA, groupB, groupACount, groupBCount, index + 1);
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