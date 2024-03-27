#include "group_handler.hpp"
#include <cmath>
#include <algorithm>

namespace MyTask
{
    bool DataManager::splitGroups() {
        initIndexes();

        splitGroupsImpl(0, 0, 0);

        return getIsSplitted();
    }

    void DataManager::initIndexes() {
        groupACurrentIndexes.clear();
        groupBCurrentIndexes.clear();
        groupABestIndexes.clear();
        groupBBestIndexes.clear();
    }

    void DataManager::splitGroupsImpl(unsigned int groupACount, unsigned int groupBCount, size_t index)
    {
        if (index >= data.size())
            return;

        if (groupACount > count || groupBCount > count)
            return;

        if (groupACount == count && groupBCount == count)
        {
            updateBestGroups();
        }

        groupACurrentIndexes.push_back(index);
        splitGroupsImpl(groupACount + data[index].getCount(), groupBCount, index + 1);
        groupACurrentIndexes.pop_back();

        groupBCurrentIndexes.push_back(index);
        splitGroupsImpl(groupACount, groupBCount + data[index].getCount(), index + 1);
        groupBCurrentIndexes.pop_back();

        splitGroupsImpl(groupACount, groupBCount, index + 1);
    }

    void DataManager::updateBestGroups() {
        if (groupABestIndexes.size() == 0 || groupBBestIndexes.size() == 0)
        {
            groupABestIndexes = groupACurrentIndexes;
            groupBBestIndexes = groupBCurrentIndexes;
        }
        else if (abs(getAverageStrength(groupACurrentIndexes) - getAverageStrength(groupBCurrentIndexes)) <
                 abs(getAverageStrength(groupABestIndexes) - getAverageStrength(groupBBestIndexes)))
        {
            groupABestIndexes = groupACurrentIndexes;
            groupBBestIndexes = groupBCurrentIndexes;
        }
    }

    bool DataManager::splitGroupsOpt() {
        initIndexes();

        splitGroupsOptImpl(0, 0);
        return (groupABestIndexes.size() > 0 && groupABestIndexes.size() > 0);
    }

    void DataManager::splitGroupsOptImpl(unsigned int groupACount, unsigned int groupBCount)
    {
        if (groupACount == count && groupBCount == count &&
            groupACurrentIndexes.size() <= count && groupBCurrentIndexes.size() <= count)
        {
            updateBestGroups();
            return;
        }

        if (groupACount > count || groupBCount > count ||
            groupACurrentIndexes.size() > count || groupBCurrentIndexes.size() > count)
            return;

        if (groupACount < count)
        {
            unsigned int start = groupACurrentIndexes.size() ? groupACurrentIndexes[groupACurrentIndexes.size() - 1] + 1 : 0;

            for (auto index = start; index < data.size() ; index++)
            {
                if (groupACount + data[index].getCount() > count)
                    continue;

                groupACurrentIndexes.push_back(index);
                splitGroupsOptImpl(groupACount + data[index].getCount(), groupBCount);
                groupACurrentIndexes.pop_back();
            }
        }
        else
        {
            unsigned int start = groupBCurrentIndexes.size() ? groupBCurrentIndexes[groupBCurrentIndexes.size() - 1] + 1 : 0;
            for (auto index = start; index < data.size() ; index++)
            {
                //it should be fast as small vector
                if (std::find(groupACurrentIndexes.begin(), groupACurrentIndexes.end(), index) != groupACurrentIndexes.end())
                {
                    continue;
                }

                if (groupBCount + data[index].getCount() > count)
                    continue;

                groupBCurrentIndexes.push_back(index);
                splitGroupsOptImpl(groupACount, groupBCount + data[index].getCount());
                groupBCurrentIndexes.pop_back();

            }
        }


    }

    unsigned int DataManager::getAverageStrength(std::vector<unsigned int> &groupIndexes)
    {
        unsigned int sumStrength = 0;
        unsigned int sumCount = 0;

        for (const auto data_index: groupIndexes)
        {
            if (data_index >= data.size())
                break;

            sumCount += data[data_index].getCount();
            sumStrength += data[data_index].getStrength() * data[data_index].getCount();
        }

        if (!sumCount)
            return 0;

        return sumStrength / sumCount;
    }

    void DataManager::Print() {
        std::cout<< "group A:" << "\n";
        for (auto data_index: groupABestIndexes)
        {
            std::cout<< data[data_index] << "\n";
        }

        std::cout<< "group B:" << "\n";
        for (auto data_index: groupBBestIndexes)
        {
            std::cout<< data[data_index] << "\n";
        }

        std::cout<<  "\n";
    }

    std::ostream& operator<<(std::ostream& os, const DataEntry& obj)
    {
        return os << "(" << obj.getId() << "," << obj.getCount() << "," << obj.getStrength() <<")";
    }
}