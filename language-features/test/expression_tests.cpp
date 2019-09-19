#include <gtest/gtest.h>

#include <array>

#include "expressions.h"

TEST(ExpressionTests, TypeTraits)
{
	static constexpr bool is_array = mcc::is_array_or_expression<std::array<double, 3>>::value;
	ASSERT_TRUE(is_array);
}