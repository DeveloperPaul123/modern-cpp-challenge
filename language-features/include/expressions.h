#pragma once

#include <array>

namespace mcc
{
	template<typename T, std::size_t M, std::size_t N>
	class matrix;

	template<class T>
	struct is_array_or_expression : std::false_type {};

	template<class T>
	struct is_array_or_expression<T[]> : std::true_type {};

	template<class T, std::size_t N>
	struct is_array_or_expression<std::array<T, N>> : std::true_type {};

	template<class operand, class index>
	auto subscript(operand const& v, index const i);

	template<class callable, class... operands>
	class expression
	{
		std::tuple<operands const& ...> ops_;
		callable f_;

	public:
		using index = std::size_t;

		expression(callable functor, const operands&... ops): f_(functor), ops_(ops...){}
		auto operator[](index const& i) const
		{
			auto const call_at_index =
				[this, i](operands const& ... ops){ return f_(subscript(ops, i)...);	};
			return std::apply(call_at_index, ops_);
		}
	};

	template<class callable, class... operands>
	struct is_array_or_expression<expression<callable, operands...>> : std::true_type {};

	template<class T, std::size_t M, std::size_t N>
	struct is_array_or_expression<matrix<T, M, N>> : std::true_type {};

	template<class operand, class index>
	auto subscript(operand const& v, index const i)
	{
		if constexpr (is_array_or_expression<operand>::value)
		{
			return v[i];
		}
		else
		{
			return v;
		}
	}
}