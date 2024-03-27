#pragma once

#include <string>
#include <vector>
#include <set>
#include "iostream"
#include "iosfwd"

namespace MyTask {
    class DataEntry {
    public:
        DataEntry(const std::string & id_, unsigned int count_, unsigned int strength_):
            id(id_), count(count_), strength(strength_) {}
        DataEntry(const std::string && id_, unsigned int count_, unsigned int strength_):
                id(id_), count(count_), strength(strength_) {}
        DataEntry(const DataEntry &) = default;
        DataEntry & operator=(const DataEntry &) = default;

        std::string getId() const {return id;}
        unsigned int getCount() const {return count;}
        unsigned int getStrength() const {return strength;}

    private:
        std::string id;
        unsigned int count;
        unsigned int strength;
    };

    std::ostream& operator<<(std::ostream& os, const DataEntry& obj);

    class DataManager {
    public:
        void addEntry(const DataEntry &entry) {data.push_back(entry);}
        void addEntry(DataEntry && entry) {data.push_back(std::move(entry));}
        size_t getEntriesCount() const {return data.size();}
        bool getIsSplitted() const {return (groupABestIndexes.size() > 0 && groupBBestIndexes.size() > 0);}
        bool splitGroups();
        bool splitGroupsOpt();
        void Print();

        static const unsigned int count = 5;
    private:
        void splitGroupsImpl(unsigned int groupACount, unsigned int groupBCount, size_t index);
        void splitGroupsOptImpl(unsigned int groupACount, unsigned int groupBCount);
        unsigned int getAverageStrength(std::vector<unsigned int> &groupIndexes);
        void updateBestGroups();

        std::vector<DataEntry> data;
        std::vector<unsigned int> groupABestIndexes;
        std::vector<unsigned int> groupBBestIndexes;
        std::vector<unsigned int> groupACurrentIndexes;
        std::vector<unsigned int> groupBCurrentIndexes;

        void initIndexes();
    };
}