#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include "sorting.h"

TEST(BubbleSortTest, EmptyVector)
{
    std::vector<int> data;
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(BubbleSortTest, SingleElement)
{
    std::vector<int> data = {52};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({52}));
}

TEST(BubbleSortTest, UnsortedVector)
{
    std::vector<int> data = {4, 3, 2, 1};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSortTest, VectorWithDuplicates)
{
    std::vector<int> data = {1, 1, 2, 2, 3, 3};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSortTest, EmptyVector)
{
    std::vector<int> data;
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(QuickSortTest, SingleElement)
{
    std::vector<int> data = {52};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({52}));
}

TEST(QuickSortTest, UnsortedVector)
{
    std::vector<int> data = {4, 3, 2, 1};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSortTest, VectorWithDuplicates)
{
    std::vector<int> data = {1, 1, 2, 2, 3, 3};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}
