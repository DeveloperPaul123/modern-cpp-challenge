#pragma once

#include <array>
#include <cassert>
#include "expressions.h"

namespace mcc
{
	template<typename T, std::size_t M, std::size_t N>
    class matrix
    {
    public:

#pragma region Type definitions
        using value_type = T;
        using size_type = std::size_t;
        using container_type = std::array<value_type, M*N>;
        using reference = typename container_type::reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        using iterator = typename container_type::iterator;
        using const_iterator = typename container_type::const_iterator;
        using reverse_iterator = typename container_type::reverse_iterator;
        using const_reverse_iterator = typename container_type::const_reverse_iterator;
#pragma endregion

        matrix();
        explicit matrix(const T& value);
        explicit matrix(std::array<value_type, M*N> &data);
        matrix(std::initializer_list<value_type> values);
	
		template<class Expression>
		matrix(const Expression& expr);

		value_type operator[](const size_type& index) const;

		template<typename Expression>
		auto operator=(const Expression& expression);

        T at(const std::size_t &row, const std::size_t &col);
        T* data();
        T* data() const;
        reference operator()(const std::size_t& row, const std::size_t &col);
        size_type columns() const;
        size_type rows() const;
		constexpr size_type size() const;

        iterator begin(); 
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

        void fill(const T& value);

        constexpr bool empty() const noexcept;

    private:
        std::size_t size_ = M * N;
        std::size_t rows_;
        std::size_t columns_;
        std::array<T, M*N> data_;
    };

    template <typename T, std::size_t M, std::size_t N>
    constexpr bool matrix<T, M, N>::empty() const noexcept
    {
        return M == 0 || N == 0;
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix() : rows_(M), columns_(N)
    {
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(const T& value) : rows_(M), columns_(N)
    {
        fill(value);
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(std::array<value_type, M * N>& data): rows_(M), columns_(N)
    {
        data_ = data;
    }

    template <typename T, std::size_t M, std::size_t N>
    matrix<T, M, N>::matrix(std::initializer_list<value_type> values) : rows_(M), columns_(N)
    {
        assert(values.size() == size_);
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::value_type matrix<T, M, N>::operator[](const size_type& index) const
    {
        return data_[index];
    }

    template <typename T, std::size_t M, std::size_t N>
    T matrix<T, M, N>::at(const std::size_t& row, const std::size_t& col)
    {
        // assumes data is ordered in row major order. 
        const auto index = row * columns_ + col;
        return data_.at(index);
    }

    template <typename T, std::size_t M, std::size_t N>
    T* matrix<T, M, N>::data()
    {
        return data_.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    T* matrix<T, M, N>::data() const
    {
        return data_.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reference matrix<T, M, N>::operator()(const std::size_t& row, const std::size_t& col)
    {
        return data_[row * columns_ + col];
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::size_type matrix<T, M, N>::columns() const
    {
        return columns_;
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::size_type matrix<T, M, N>::rows() const
    {
        return rows_;
    }

	template <typename T, std::size_t M, std::size_t N>
	constexpr typename matrix<T, M, N>::size_type matrix<T, M, N>::size() const
	{
		return size_;
	}

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::iterator matrix<T, M, N>::begin()
    {
        return data_.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::iterator matrix<T, M, N>::end()
    {
        return data_.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_iterator matrix<T, M, N>::begin() const
    {
        return data_.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_iterator matrix<T, M, N>::end() const
    {
        return data_.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reverse_iterator matrix<T, M, N>::rbegin()
    {
        return data_.rbegin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::reverse_iterator matrix<T, M, N>::rend()
    {
        return data_.rend();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_reverse_iterator matrix<T, M, N>::rbegin() const
    {
        return data_.rbegin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename matrix<T, M, N>::const_reverse_iterator matrix<T, M, N>::rend() const
    {
        return data_.rend();
    }


    template <typename T, std::size_t M, std::size_t N>
    void matrix<T, M, N>::fill(const T& value)
    {
        std::fill(data_.begin(), data_.end(), value);
    }

	template<typename T, std::size_t M, std::size_t N>
	template<class Expression>
	inline matrix<T, M, N>::matrix(const Expression& expr)
		: rows_(M), columns_(N), data_{}
	{
		for (size_type i = 0; i < size_; i++)
		{
			data_[i] = expr[i];
		}
	}

	template<typename T, std::size_t M, std::size_t N>
	template<typename Expression>
	inline auto matrix<T, M, N>::operator=(const Expression& expression)
	{
		for (auto i = 0; i < size_; ++i)
		{
			data_[i] = expression[i];
		}

		return *this;
	}

	template<class T>
	struct is_matrix : std::false_type {};

	template<class T, std::size_t M, std::size_t N>
	struct is_matrix<matrix<T, M, N>> : std::true_type {};

	template<class LHS, class RHS>
	auto operator+(LHS const& lhs, RHS const& rhs)
	{
		return expression(
			[](auto a, auto b) {return a + b; },
				lhs,
				rhs);
	}

	template<class LHS, class RHS>
	auto operator-(LHS const& lhs, RHS const& rhs)
	{
		return expression(
			[](auto a, auto b) {return a - b; },
			lhs,
			rhs
		);
	}
}
