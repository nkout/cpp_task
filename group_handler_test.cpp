#include "group_handler.hpp"
#include <gtest/gtest.h>

namespace MyTask {
    class DataManagerTest : public testing::Test {
    protected:
        void SetUp() override {}
        void TearDown() override {}
    };

    TEST_F(DataManagerTest, TestSplitGroups) {
        DataGroupHandler m;
        m.addEntry({"nikos", 1, 10});
        m.addEntry({"party", 3, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"hat", 4, 10});
        m.addEntry({"laptop", 4, 60});
        m.addEntry({"server", 3, 30});
        m.addEntry({"ship", 1, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 3, 200});

        EXPECT_EQ(m.getEntriesCount(), 9);
        EXPECT_EQ(m.splitGroups(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"party", 3, 20});
        expA.push_back({"plane", 2, 100});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 1, 15});
        expB.push_back({"laptop", 4, 60});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOpt) {
        DataGroupHandler m;
        m.addEntry({"nikos", 1, 10});
        m.addEntry({"party", 3, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"hat", 4, 10});
        m.addEntry({"laptop", 4, 60});
        m.addEntry({"server", 3, 30});
        m.addEntry({"ship", 1, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 3, 200});

        EXPECT_EQ(m.getEntriesCount(), 9);
        EXPECT_EQ(m.splitGroupsOpt(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"party", 3, 20});
        expA.push_back({"plane", 2, 100});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 1, 15});
        expB.push_back({"laptop", 4, 60});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsExact) {
        DataGroupHandler m;
        m.addEntry({"party", 3, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"laptop", 4, 60});
        m.addEntry({"plane", 2, 100});

        EXPECT_EQ(m.getEntriesCount(), 4);
        EXPECT_EQ(m.splitGroups(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"party", 3, 20});
        expA.push_back({"plane", 2, 100});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 1, 15});
        expB.push_back({"laptop", 4, 60});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOptExact) {
        DataGroupHandler m;
        m.addEntry({"party", 3, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"laptop", 4, 60});
        m.addEntry({"plane", 2, 100});

        EXPECT_EQ(m.getEntriesCount(), 4);
        EXPECT_EQ(m.splitGroupsOpt(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"party", 3, 20});
        expA.push_back({"plane", 2, 100});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 1, 15});
        expB.push_back({"laptop", 4, 60});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsFewElements) {
        DataGroupHandler m;
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"laptop", 1, 60});
        m.addEntry({"plane", 2, 100});

        EXPECT_EQ(m.getEntriesCount(), 4);
        EXPECT_EQ(m.splitGroups(), false);
        EXPECT_EQ(m.getIsSplit(), false);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOptFewElements) {
        DataGroupHandler m;
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"laptop", 1, 60});
        m.addEntry({"plane", 2, 100});

        EXPECT_EQ(m.getEntriesCount(), 4);
        EXPECT_EQ(m.splitGroupsOpt(), false);
        EXPECT_EQ(m.getIsSplit(), false);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOneValueElements) {
        DataGroupHandler m;
        m.addEntry({"nikos", 1, 10});
        m.addEntry({"party", 1, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"hat", 1, 10});
        m.addEntry({"laptop", 1, 60});
        m.addEntry({"server", 1, 30});
        m.addEntry({"ship", 1, 5});
        m.addEntry({"plane", 1, 100});
        m.addEntry({"submarine", 1, 200});
        m.addEntry({"jp", 1, 400});

        EXPECT_EQ(m.getEntriesCount(), 10);
        EXPECT_EQ(m.splitGroups(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"nikos", 1, 10});
        expA.push_back({"wolf", 1, 15});
        expA.push_back({"hat", 1, 10});
        expA.push_back({"ship", 1, 5});
        expA.push_back({"jp", 1, 400});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"party", 1, 20});
        expB.push_back({"laptop", 1, 60});
        expB.push_back({"server", 1, 30});
        expB.push_back({"plane", 1, 100});
        expB.push_back({"submarine", 1, 200});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOptOneValueElements) {
        DataGroupHandler m;
        m.addEntry({"nikos", 1, 10});
        m.addEntry({"party", 1, 20});
        m.addEntry({"wolf", 1, 15});
        m.addEntry({"hat", 1, 10});
        m.addEntry({"laptop", 1, 60});
        m.addEntry({"server", 1, 30});
        m.addEntry({"ship", 1, 5});
        m.addEntry({"plane", 1, 100});
        m.addEntry({"submarine", 1, 200});
        m.addEntry({"jp", 1, 400});

        EXPECT_EQ(m.getEntriesCount(), 10);
        EXPECT_EQ(m.splitGroupsOpt(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"nikos", 1, 10});
        expA.push_back({"wolf", 1, 15});
        expA.push_back({"hat", 1, 10});
        expA.push_back({"ship", 1, 5});
        expA.push_back({"jp", 1, 400});
        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"party", 1, 20});
        expB.push_back({"laptop", 1, 60});
        expB.push_back({"server", 1, 30});
        expB.push_back({"plane", 1, 100});
        expB.push_back({"submarine", 1, 200});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestSplitGroupsCannotSplit) {
        DataGroupHandler m;
        m.addEntry({"nikos", 2, 10});
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 2, 15});
        m.addEntry({"hat", 2, 10});
        m.addEntry({"laptop", 2, 60});
        m.addEntry({"server", 2, 30});
        m.addEntry({"ship", 2, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 2, 200});
        m.addEntry({"jp", 2, 400});

        EXPECT_EQ(m.getEntriesCount(), 10);
        EXPECT_EQ(m.splitGroups(), false);
        EXPECT_EQ(m.getIsSplit(), false);
    }

    TEST_F(DataManagerTest, TestSplitGroupsOptCannotSplit) {
        DataGroupHandler m;
        m.addEntry({"nikos", 2, 10});
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 2, 15});
        m.addEntry({"hat", 2, 10});
        m.addEntry({"laptop", 2, 60});
        m.addEntry({"server", 2, 30});
        m.addEntry({"ship", 2, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 2, 200});
        m.addEntry({"jp", 2, 400});

        EXPECT_EQ(m.getEntriesCount(), 10);
        EXPECT_EQ(m.splitGroupsOpt(), false);
        EXPECT_EQ(m.getIsSplit(), false);
    }

    TEST_F(DataManagerTest, TestSplitGroupManyElements) {
        DataGroupHandler m;
        m.addEntry({"nikos", 2, 10});
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 2, 15});
        m.addEntry({"hat", 2, 10});
        m.addEntry({"laptop", 2, 60});
        m.addEntry({"server", 2, 30});
        m.addEntry({"ship", 2, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 2, 200});
        m.addEntry({"fire", 2, 400});
        m.addEntry({"desk", 2, 400});
        m.addEntry({"pen", 2, 440});
        m.addEntry({"headset", 1, 10});
        m.addEntry({"mouse", 1, 15});

        EXPECT_EQ(m.getEntriesCount(), 14);
        EXPECT_EQ(m.splitGroups(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"nikos", 2, 10});
        expA.push_back({"party", 2, 20});
        expA.push_back({"headset", 1, 10});

        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 2, 15});
        expB.push_back({"hat", 2, 10});
        expB.push_back({"mouse", 1, 15});
        EXPECT_EQ(m.getGroupB(), expB);
    }


    TEST_F(DataManagerTest, TestSplitGroupOptManyElements) {
        DataGroupHandler m;
        m.addEntry({"nikos", 2, 10});
        m.addEntry({"party", 2, 20});
        m.addEntry({"wolf", 2, 15});
        m.addEntry({"hat", 2, 10});
        m.addEntry({"laptop", 2, 60});
        m.addEntry({"server", 2, 30});
        m.addEntry({"ship", 2, 5});
        m.addEntry({"plane", 2, 100});
        m.addEntry({"submarine", 2, 200});
        m.addEntry({"fire", 2, 400});
        m.addEntry({"desk", 2, 400});
        m.addEntry({"pen", 2, 440});
        m.addEntry({"headset", 1, 10});
        m.addEntry({"mouse", 1, 15});

        EXPECT_EQ(m.getEntriesCount(), 14);
        EXPECT_EQ(m.splitGroupsOpt(), true);
        EXPECT_EQ(m.getIsSplit(), true);

        std::vector<DataEntry> expA;
        expA.push_back({"nikos", 2, 10});
        expA.push_back({"party", 2, 20});
        expA.push_back({"headset", 1, 10});

        EXPECT_EQ(m.getGroupA(), expA);

        std::vector<DataEntry> expB;
        expB.push_back({"wolf", 2, 15});
        expB.push_back({"hat", 2, 10});
        expB.push_back({"mouse", 1, 15});
        EXPECT_EQ(m.getGroupB(), expB);
    }

    TEST_F(DataManagerTest, TestInsertInvalidEntry) {
        DataGroupHandler m;
        EXPECT_EQ(m.getEntriesCount(), 0);

        EXPECT_EQ(m.addEntry({"nikos", 0, 10}), false);
        EXPECT_EQ(m.getEntriesCount(), 0);

        EXPECT_EQ(m.addEntry({"nikos", 2, 0}), false);
        EXPECT_EQ(m.getEntriesCount(), 0);

        EXPECT_EQ(m.addEntry({"nikos", 0, 0}), false);
        EXPECT_EQ(m.getEntriesCount(), 0);

        EXPECT_EQ(m.addEntry({"nikos", 1, 10}), true);
        EXPECT_EQ(m.getEntriesCount(), 1);
    }
}