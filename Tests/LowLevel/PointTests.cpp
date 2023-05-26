#include "gtest/gtest.h"

#include "../../LowLevel/Point.h"

//  region constructs
TEST(PointConstructsTests, PointConstructsDiffType) {
    Point<long long> pt_ll(10);
    Point<int> pt_int(10);

    ASSERT_EQ(pt_ll, pt_int);
    ASSERT_EQ(pt_ll.size(), 10);
}

TEST(PointConstructsTests, PointConstructsFilled) {
    std::vector<std::vector<long long>> tmp = {{1}, {1}, {1}, {1}};
    ASSERT_EQ(Point<long long>(4, 1), Point<long long>(tmp));
    ASSERT_EQ(Point<long long>(5, 34), Point<long long>({34, 34, 34, 34, 34}));
}
//  endregion

//  region operator
TEST(PointOperatorTests, PointOperatorAdd) {
    Point<int> pt({1, 2, 3}), ptResAdd({2, 3, 4}), ptResSub({0, 1, 2});
    Vector<int> vecOne(3, 1), vecMOne(3, -1) ;

    ASSERT_EQ(pt + vecOne, ptResAdd);
    ASSERT_EQ(pt + vecMOne, ptResSub);
}

TEST(PointOperatorTests, PointOperatorSub) {
    Point<int> pt({1, 2, 3}), ptResAdd({2, 3, 4}), ptResSub({0, 1, 2});
    Vector<int> vecOne(3, 1), vecMOne(3, -1);
    ASSERT_EQ(pt - vecMOne, ptResAdd);
    ASSERT_EQ(pt - vecOne, ptResSub);
}
//  endregion