#include "group_handler.hpp"
#include <cmath>
#include <algorithm>

namespace MyTask
{
    bool DataGroupHandler::splitGroups() {
        initIndexes();

        splitGroupsImpl(0, 0, 0);

        return getIsSplit();
    }

    void DataGroupHandler::initIndexes() {
        groupACurrentIndexes.clear();
        groupBCurrentIndexes.clear();
        groupABestIndexes.clear();
        groupBBestIndexes.clear();
    }

    //more clean code, but it can go  to deep recursion if we have lot of data
    void DataGroupHandler::splitGroupsImpl(unsigned int groupACount, unsigned int groupBCount, size_t index)
    {
        if (groupACount > count || groupBCount > count)
            return;

        if (groupACount == count && groupBCount == count)
        {
            updateBestGroups();
        }

        if (index >= data.size())
            return;

        //element can belong to group A
        groupACurrentIndexes.push_back(index);
        splitGroupsImpl(groupACount + data[index].getCount(), groupBCount, index + 1);
        groupACurrentIndexes.pop_back();

        //or it can belong to group B
        groupBCurrentIndexes.push_back(index);
        splitGroupsImpl(groupACount, groupBCount + data[index].getCount(), index + 1);
        groupBCurrentIndexes.pop_back();

        //or it can be left out
        splitGroupsImpl(groupACount, groupBCount, index + 1);
    }

    void DataGroupHandler::updateBestGroups() {
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

    bool DataGroupHandler::splitGroupsOpt() {
        initIndexes();

        splitGroupsOptImpl(0, 0);
        return (groupABestIndexes.size() > 0 && groupABestIndexes.size() > 0);
    }

    //this code is not so beautiful, but it takes advantage of count limited to 5,
    //so recursion is limited to 10
    void DataGroupHandler::splitGroupsOptImpl(unsigned int groupACount, unsigned int groupBCount)
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

    unsigned int DataGroupHandler::getAverageStrength(std::vector<unsigned int> &groupIndexes)
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
    std::vector<DataEntry> DataGroupHandler::getGroupA() const
    {
        std::vector<DataEntry> result;

        for (auto index : groupABestIndexes)
        {
            result.push_back(data[index]);
        }

        return result;
    }

    std::vector<DataEntry> DataGroupHandler::getGroupB() const
    {
        std::vector<DataEntry> result;

        for (auto index : groupBBestIndexes)
        {
            result.push_back(data[index]);
        }

        return result;
    }

    void DataGroupHandler::Print() {
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