#include "include/sl_map.h"
#include "skiplist_map/greensky_skiplist_map.h"

#include "gtest/gtest.h"

TEST(SkiplistTest, TestGreenSkySKiplist) {
    sl_map_gc<int, int> slist;

    //   << Insertion >>
    // Insert 3 KV pairs: {0, 0}, {1, 10}, {2, 20}.
    for (int i = 0; i < 3; ++i) {
        slist.insert(std::make_pair(i, i * 10));
    }

    for (int i = 0; i < 3; ++i) {
        auto it = slist.find(i);
        ASSERT_TRUE(it != slist.end());
        ASSERT_EQ(it->second, i * 10);
    }

    {
        /// Look up a invalid key.
        auto it = slist.find(999);
        ASSERT_TRUE(it == slist.end());
    }

    //   << Erase >>
    // Erase the KV pair for key 1: {1, 10}.
    slist.erase(1);

    {
        /// Look up a erased key.
        auto it = slist.find(1);
        ASSERT_TRUE(it == slist.end());
    }
}

TEST(SkiplistTest, TestGreenSkySKiplistMap) {
    using namespace metable;
    std::unique_ptr<SkiplistMap<int, int>> map =
        std::make_unique<GreenSkySkiplistMap<int, int>>();
    ASSERT_TRUE(map->Put(1, 10));
    ASSERT_FALSE(map->Put(1, 20));

    {
        int value = 0;
        ASSERT_TRUE(map->Get(1, &value));
        ASSERT_EQ(10, value);
    }
    {
        int value = 0;
        ASSERT_FALSE(map->Get(2, &value));
        ASSERT_EQ(0, value);
    }

    {
        /// Contains
        ASSERT_TRUE(map->Contains(1));
        ASSERT_FALSE(map->Contains(3));
    }

    {
        /// Remove
        ASSERT_TRUE(map->Remove(1));
        ASSERT_FALSE(map->Remove(3));
        ASSERT_FALSE(map->Contains(1));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
