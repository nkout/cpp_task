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
                id(std::move(id_)), count(count_), strength(strength_) {}
        DataEntry(const DataEntry &) = default;
        DataEntry & operator=(const DataEntry &) = default;
        bool operator== (const DataEntry &d) const {return (d.getId() == id && d.getCount() == count && d.getStrength() == strength);}

        std::string getId() const {return id;}
        unsigned int getCount() const {return count;}
        unsigned int getStrength() const {return strength;}

    private:
        std::string id;
        unsigned int count;
        unsigned int strength;
    };

    std::ostream& operator<<(std::ostream& os, const DataEntry& obj);

    class DataGroupHandler {
    public:
        bool addEntry(const DataEntry &entry) {return addEntryImpl(entry);}
        bool addEntry(DataEntry && entry) {return addEntryImpl(std::move(entry));}
        size_t getEntriesCount() const {return data.size();}
        bool getIsSplit() const {return (groupABestIndexes.size() > 0 && groupBBestIndexes.size() > 0);}
        bool splitGroups();
        bool splitGroupsOpt();
        std::vector<DataEntry> getGroupA() const;
        std::vector<DataEntry> getGroupB() const;
        void Print();

        static const unsigned int groupCountSummary = 5;
    private:
        void splitGroupsImpl(unsigned int groupACountSum, unsigned int groupBCountSum, size_t index);
        void splitGroupsOptImpl(unsigned int groupACountSum, unsigned int groupBCountSum);
        unsigned int getAverageStrength(std::vector<unsigned int> &groupIndexes);
        void updateBestGroups();
        void initIndexes();
        bool validateEntry(const DataEntry &entry) {return (entry.getStrength() > 0 && entry.getCount()>0);}

        template <typename T> bool addEntryImpl(T && entry) {
            if (validateEntry(entry)) {
                data.push_back(std::forward<T>(entry));
                return true;
            }
            return false;
        }

        std::vector<DataEntry> data;
        unsigned int bestAverageStrenthDiff;
        std::vector<unsigned int> groupABestIndexes;
        std::vector<unsigned int> groupBBestIndexes;
        std::vector<unsigned int> groupACurrentIndexes;
        std::vector<unsigned int> groupBCurrentIndexes;

    };
}