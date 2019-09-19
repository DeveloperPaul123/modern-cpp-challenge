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

TEST(MatrixTests, MatrixTypeTraits)
{
	auto check = mcc::is_array_or_expression<mcc::matrix<double, 3, 3>>();
	ASSERT_TRUE(check());
}

TEST(MatrixTests, AddMatrix)
{
	mcc::matrix<double, 3, 3> first;
	mcc::matrix<double, 3, 3> second;

	std::fill(first.begin(), first.end(), 2.0);
	std::fill(second.begin(), second.end(), 3.0);

	mcc::matrix<double, 3, 3> result = first + second;
	const auto sum = std::accumulate(result.begin(), result.end(), 0);
	ASSERT_EQ(sum, first.size() * 5);
}

TEST(MatrixTests, AddConstantToMatrix)
{
	mcc::matrix<double, 3, 3> mat(1.0);
	mcc::matrix<double, 3, 3> result = mat + 4.0;
	const auto sum = std::accumulate(result.begin(), result.end(), 0.0);
	ASSERT_EQ(sum, mat.size() * 5.0);
}
