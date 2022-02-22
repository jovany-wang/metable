#include "include/sl_map.h"

#include "gtest/gtest.h"

TEST(SkiplistTest, TestBasic) {
    sl_map_gc<int, int> slist;

    //   << Insertion >>
    // Insert 3 KV pairs: {0, 0}, {1, 10}, {2, 20}.
    for (int i = 0; i < 3; ++i) {
        slist.insert(std::make_pair(i, i*10));
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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
