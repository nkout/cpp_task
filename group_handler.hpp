#pragma once

#include <string>
#include <vector>
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
        DataManager(): count(defaultCount) {}
        void addEntry(const DataEntry &entry) {data.push_back(entry);}
        void addEntry(DataEntry && entry) {data.push_back(std::move(entry));}
        size_t getEntriesCount() {return data.size();}
        bool splitGroups();
        void Print();

        static const unsigned int defaultCount = 5;
        static const unsigned int defaultStrengthThreshPercent = 10;
        unsigned int count;
    private:
        void SplitSubset(std::vector<DataEntry*> &groupA, std::vector<DataEntry*> &groupB,
                         unsigned int groupACount, unsigned int groupBCount, size_t index);

        unsigned int getAverageStrength(std::vector<DataEntry*> &group);
        std::vector<DataEntry> data;
        std::vector<DataEntry*> groupA;
        std::vector<DataEntry*> groupB;
    };
}