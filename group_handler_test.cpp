#include "group_handler.hpp"
#include <gtest/gtest.h>

namespace MyTask {
    class DataManagerTest : public testing::Test {
    protected:
        void SetUp() override {}
        void TearDown() override {}
    };

    TEST_F(DataManagerTest, MethodHandleEvent) {
        DataManager m;
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
        m.Print();
    }
}