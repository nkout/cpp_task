#include "group_handler.hpp"
#include <cmath>
#include <algorithm>

namespace MyTask
{
    void DataGroupHandler::initIndexes() {
        groupACurrentIndexes.clear();
        groupBCurrentIndexes.clear();
        groupABestIndexes.clear();
        groupBBestIndexes.clear();
        bestAverageStrenthDiff = 0;
    }

    bool DataGroupHandler::splitGroups() {
        initIndexes();

        splitGroupsImpl(0, 0, 0);

        return getIsSplit();
    }

    //more clean code, but it can go  to deep recursion if we have lot of data
    void DataGroupHandler::splitGroupsImpl(unsigned int groupACountSum, unsigned int groupBCountSum, size_t index)
    {
        if (groupACountSum > groupCountSummary || groupBCountSum > groupCountSummary)
            return;

        if (groupACountSum == groupCountSummary && groupBCountSum == groupCountSummary)
        {
            updateBestGroups();
            return;
        }

        if (index >= data.size())
            return;

        //element can belong to group A
        groupACurrentIndexes.push_back(index);
        splitGroupsImpl(groupACountSum + data[index].getCount(), groupBCountSum, index + 1);
        groupACurrentIndexes.pop_back();

        //or it can belong to group B
        groupBCurrentIndexes.push_back(index);
        splitGroupsImpl(groupACountSum, groupBCountSum + data[index].getCount(), index + 1);
        groupBCurrentIndexes.pop_back();

        //or it can be left out
        splitGroupsImpl(groupACountSum, groupBCountSum, index + 1);
    }

    void DataGroupHandler::updateBestGroups() {
        unsigned int currentStrengthDiff = abs(getAverageStrength(groupACurrentIndexes) -
                                                getAverageStrength(groupBCurrentIndexes));

        if (groupABestIndexes.size() == 0 || groupBBestIndexes.size() == 0 || bestAverageStrenthDiff > currentStrengthDiff)
        {
            groupABestIndexes = groupACurrentIndexes;
            groupBBestIndexes = groupBCurrentIndexes;
            bestAverageStrenthDiff = currentStrengthDiff;
        }
    }

    bool DataGroupHandler::splitGroupsOpt() {
        initIndexes();

        splitGroupsOptImpl(0, 0);
        return (groupABestIndexes.size() > 0 && groupABestIndexes.size() > 0);
    }

    //this code is not so beautiful, but it takes advantage of group count summary limited to 5,
    //so recursion is limited to 10
    void DataGroupHandler::splitGroupsOptImpl(unsigned int groupACountSum, unsigned int groupBCountSum)
    {
        if (groupACountSum == groupCountSummary && groupBCountSum == groupCountSummary &&
            groupACurrentIndexes.size() <= groupCountSummary && groupBCurrentIndexes.size() <= groupCountSummary)
        {
            updateBestGroups();
            return;
        }

        if (groupACountSum > groupCountSummary || groupBCountSum > groupCountSummary ||
            groupACurrentIndexes.size() > groupCountSummary || groupBCurrentIndexes.size() > groupCountSummary)
            return;

        if (groupACountSum < groupCountSummary)
        {
            unsigned int start = groupACurrentIndexes.size() ? groupACurrentIndexes[groupACurrentIndexes.size() - 1] + 1 : 0;

            for (auto index = start; index < data.size() ; index++)
            {
                if (groupACountSum + data[index].getCount() > groupCountSummary)
                    continue;

                groupACurrentIndexes.push_back(index);
                splitGroupsOptImpl(groupACountSum + data[index].getCount(), groupBCountSum);
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

                if (groupBCountSum + data[index].getCount() > groupCountSummary)
                    continue;

                groupBCurrentIndexes.push_back(index);
                splitGroupsOptImpl(groupACountSum, groupBCountSum + data[index].getCount());
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