#include <gtest/gtest.h>

#include "matrix.h"
#include <numeric>

TEST(MatrixTests, Construction)
{
    mcc::matrix<double, 3, 3> data;
    std::iota(data.begin(), data.end(), 0.0);

    for(std::size_t r = 0; r < data.rows(); r++)
    {
        for(std::size_t c = 0; c < data.columns(); c++)
        {
            auto index_value = r * data.columns() + c;
            ASSERT_DOUBLE_EQ(data.at(r, c), static_cast<double>(index_value));
        }
    }

    mcc::matrix<double, 2, 2> square{ 1.0, 3.0, 4.0, 6.0 };
}

TEST(MatrixTests, ModifyContents)
{
    mcc::matrix<double, 3, 2> data;
    std::iota(data.begin(), data.end(), 1.0);

    data(0, 0) *= 2.0;

    ASSERT_DOUBLE_EQ(data.at(0, 0), 2.0);
}