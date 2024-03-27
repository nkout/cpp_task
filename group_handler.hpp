#pragma once

#include <string>
#include <vector>
#include <array>
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
        size_t getEntriesCount() {return data.size();}
        bool splitGroups();
        bool splitGroups2();
        void Print();

        static const unsigned int count = 5;
    private:
        void SplitSubset(std::vector<DataEntry*> &groupA, std::vector<DataEntry*> &groupB,
                         unsigned int groupACount, unsigned int groupBCount, size_t index);

        void SplitSubset2(unsigned int depth, unsigned int groupACount, unsigned int groupBCount,
                          std::array<unsigned int, count> & indexA, std::array<unsigned int, count> & indexB);

        unsigned int getAverageStrength(std::vector<DataEntry*> &group);
        std::vector<DataEntry> data;
        std::vector<DataEntry*> groupA;
        std::vector<DataEntry*> groupB;
    };
}