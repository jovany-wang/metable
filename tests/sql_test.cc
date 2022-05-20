#include "gtest/gtest.h"
#include "sql/sql_parser.h"

TEST(SqlTest, TestQuery) {
    SqlParser parser;
    SqlSelect select = parser.parse("select * from test");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}